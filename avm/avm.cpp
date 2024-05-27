#include <iostream>
#include "avm.hpp"
#include <cstring>
#include <assert.h>
#include <stdarg.h>
#include <_mingw_stdarg.h>

#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))

std::vector<userfunc*> userFuncs;
std::vector<double> numbers;
std::vector<char*> strings;
std::vector<char*> libFuncs;
std::vector<instruction*> code;

avm_memcell stack[AVM_STACKSIZE];

avm_memcell ax,bx,cx;
avm_memcell retval;
unsigned top, topsp;

unsigned char executionFinished = 0;
unsigned  pc = 0;
unsigned int codeSize;
unsigned currLine = 0;

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

avm_memcell* avm_tablegetelem(avm_table* t, avm_memcell* key) {
    if(key->type == number_m) {
        unsigned i = (unsigned)key->data.numVal % AVM_TABLE_HASHSIZE;
        for(avm_table_bucket* b = t->numIndexed[i]; b; b = b->next) {
            if(b->key.data.numVal == key->data.numVal) {
                return &b->value;
            }
        }
    } else if(key->type == string_m) {
        unsigned i = (unsigned)key->data.strVal[0] % AVM_TABLE_HASHSIZE;
        for(avm_table_bucket* b = t->strIndexed[i]; b; b = b->next) {
            if(strcmp(b->key.data.strVal, key->data.strVal) == 0) {
                return &b->value;
            }
        }
    } else {
        std::cerr << "Error: Key is not a number or a string." << std::endl;
        exit(EXIT_FAILURE);
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

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg) {
    switch (arg->type) {
        case global_a: return &stack[AVM_STACKSIZE - 1 - arg->val];
        case local_a: return &stack[topsp - arg->val];
        case formal_a: return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
        case retval_a: return &retval;
        case number_a: {
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        }
        case string_a: {
            reg->type = string_m;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        }
        case bool_a: {
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }
        case nil_a: {
            reg->type = nil_m;
            return reg;
        }
        case userfunc_a: {
            reg->type = userfunc_m;
            reg->data.userfuncVal = arg->val;
            reg->data.userfuncVal = userfuncs_getfunc(arg->val)->address;
            return reg;
        }
        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.libfuncVal = strdup(libfuncs_getused(arg->val));
            return reg;
        }
        default: assert(0);
    }
    return NULL;
}

void avm_warning(char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "\033[1;33m");
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, " line: %d\n\033[0m", currLine);
}

void avm_error(char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "\033[1;31m");
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, " line: %d\n\033[0m", currLine);
    exit(EXIT_FAILURE);
}

char* typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};

char* avm_tostring(avm_memcell* m) {
  assert(m->type >= 0 && m->type <= undef_m);
  return (*tostringFuncs[m->type])(m);
}

double      consts_getnumber(unsigned int index) { return numbers[index]; }
char*       consts_getstring(unsigned int index) { return strings[index]; }
char*       libfuncs_getused(unsigned int index) { return libFuncs[index]; }
userfunc*   userfuncs_getfunc(unsigned int index) { return userFuncs[index]; }

extern void load_binary(char* filename);
extern void execute_cycle();

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    avm_initstack();
    load_binary(argv[1]);
    codeSize = code.size();

    while(!executionFinished) execute_cycle();
    return 0;
}