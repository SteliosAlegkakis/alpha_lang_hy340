#include <iostream>
#include "avm.hpp"
#include <cstring>
#include <assert.h>
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
avm_memcell stack[AVM_STACKSIZE];

void memclear_string(avm_memcell* m) {
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell* m) {
    assert(m->data.tableVal);
    avm_tabledecref_counter(m->data.tableVal);
}

typedef void (*memclear_func_t)(avm_memcell*);

memclear_func_t memclearFuncs[] = {
    0, memclear_string, 0, memclear_table, 0, 0, 0, 0
};

static void avm_initstack(void) {
    for (unsigned i = 0; i < AVM_STACKSIZE; ++i) {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void avm_tablebuckets_destroy(avm_table_bucket** p) {
    for(unsigned int i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p){
        for(avm_table_bucket* b = *p; b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket*) 0;
    }
}

void avm_memcellclear(avm_memcell* m) {
    if(m->type != undef_m) {
        memclear_func_t f = memclearFuncs[m->type];
        if(f) {
            (*f)(m);
        }
        m->type = undef_m;
    }
}

avm_table* avm_tablenew(void) {
    avm_table* t = (avm_table*)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_tablebuckets_init(t->strIndexed);
    avm_tablebuckets_init(t->numIndexed);
    return t;
}

void avm_tabledestroy(avm_table* t) {
    avm_tablebuckets_destroy(t->strIndexed);
    avm_tablebuckets_destroy(t->numIndexed);
    free(t);
}

avm_memcell* avm_tablegetelem(avm_table* t) {
    unsigned i;
    for (i = 0; i < AVM_TABLE_HASHSIZE; ++i) {
        for (avm_table_bucket* p = t->strIndexed[i]; p; p = p->next) {
            if (p->key.type == string_m) {
                return &p->value;
            }
        }
        for (avm_table_bucket* p = t->numIndexed[i]; p; p = p->next) {
            if (p->key.type == number_m) {
                return &p->value;
            }
        }
    }
    return NULL;
}

void avm_tablesetelem(avm_table* t, avm_memcell* key, avm_memcell* value) {
    unsigned i = 0;
    if (key->type == number_m) {
        i = (unsigned)key->data.numVal % AVM_TABLE_HASHSIZE;
    } else if (key->type == string_m) {
        i = (unsigned)key->data.strVal[0] % AVM_TABLE_HASHSIZE;
    } else {
        std::cerr << "Error: Key is not a number or a string." << std::endl;
        exit(EXIT_FAILURE);
    }
    avm_table_bucket* p = new avm_table_bucket;
    p->key = *key;
    p->value = *value;
    p->next = t->numIndexed[i];
    t->numIndexed[i] = p;
    ++t->total;
}

void avm_tableincref_counter(avm_table* t){
    ++t->refCounter;
}

void avm_tabledecref_counter(avm_table* t){
    assert(t->refCounter > 0);
    if(!--t->refCounter)
        avm_tabledestroy(t);
}

void avm_tablebuckets_init(avm_table_bucket** p){
    for(unsigned int i = 0; i < AVM_TABLE_HASHSIZE; ++i)
        p[i] = (avm_table_bucket*) 0;
}