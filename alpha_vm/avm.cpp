#include <iostream>
#include "avm.hpp"
#include <cstring>
#include <assert.h>
#include <stdarg.h>
//#include <_mingw_stdarg.h>

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

const char* typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};

unsigned totalActuals = 0;

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

extern unsigned int totalGlobals;
static void avm_initstack(void) {
    for (unsigned i = 0; i < AVM_STACKSIZE; ++i) {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
    top = topsp = AVM_STACKSIZE - 1 - totalGlobals;
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

void avm_assign(avm_memcell* lv, avm_memcell* rv) {
    if (lv == rv) {
        return;
    }
    if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal) {
        return;
    }
    if (rv->type == undef_m) {
        avm_warning((char*)"assigning from 'undef' content!");
    }
    
    avm_memcellclear(lv);

    memcpy(lv, rv, sizeof(avm_memcell));
    if (lv->type == string_m) {
        lv->data.strVal = strdup(rv->data.strVal);
    } else if (lv->type == table_m) {
        avm_tableincref_counter(lv->data.tableVal);
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
    avm_table_bucket* p = new avm_table_bucket;
    unsigned i = 0;
    if (key->type == number_m) {
        i = (unsigned)key->data.numVal % AVM_TABLE_HASHSIZE;
        p->next = t->numIndexed[i];
        t->numIndexed[i] = p;
    } else if (key->type == string_m) {
        i = (unsigned)key->data.strVal[0] % AVM_TABLE_HASHSIZE;
        p->next = t->strIndexed[i];
        t->strIndexed[i] = p;
    } else {
        avm_error((char*)"Error: Key is not a number or a string.");
    }
    p->key = *key;
    p->value = *value;
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

void avm_dec_top (void) {
    if (!top) {
        avm_error((char*)"stack overflow");
        executionFinished = 1;
    } else {
        --top;
    }
}

void avm_push_envvalue (unsigned val) {
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

unsigned avm_get_envvalue (unsigned i) {
    assert(stack[i].type == number_m);
    unsigned val = (unsigned) stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double) val));
    return val;
}

void avm_callsaveenvironment (void) {
    avm_push_envvalue(totalActuals);
    assert(code[pc]->opcode == call_v);
    avm_push_envvalue(pc + 1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}

void avm_push_table_arg(avm_table* t) {
    stack[top].type = table_m;
    avm_tableincref_counter(stack[top].data.tableVal = t);
    ++totalActuals;
    avm_dec_top();
}

void avm_call_functor(avm_table* t) {
    cx.type = string_m;
    cx.data.strVal = (char*)"()";
    avm_memcell* f = avm_tablegetelem(t, &cx);
    if(!f)
        avm_error((char*)"in calling table: no '()' element found!");
    else if(f->type == table_m) {
        avm_call_functor(f->data.tableVal);
    } else if(f->type == userfunc_m) {
        avm_push_table_arg(t);
        avm_callsaveenvironment();
        pc = f->data.userfuncVal;
        assert(pc < AVM_ENDING_PC);
        assert(code[pc]->opcode == funcenter_v);
    }
    else {
        avm_error((char*)"in calling table: illegal '()' element value!");
    }

}

unsigned avm_totalactuals(void) {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i) {
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

typedef void (*library_func_t) (void);

extern library_func_t avm_getlibraryfunc (char* id);

extern void execute_funcexit (instruction* instr);

void avm_calllibfunc (char* id) {
    library_func_t f = avm_getlibraryfunc(id);
    if(!f) {
        avm_error((char*)"unsupported lib func '%s' called!", id);
    } else {
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!executionFinished)
            execute_funcexit((instruction*) 0);
    }

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
    fprintf(stderr, "\nWarning: ");
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, " line: %d\n\033[0m", currLine);
}

void avm_error(char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "\033[1;31m");
    fprintf(stderr, "\nError: ");
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, " line: %d\n\033[0m", currLine);
    executionFinished = 1;
}

typedef char* (*tostring_func_t)(avm_memcell*);

char* number_tostring(avm_memcell* m) {
    char* str = (char*)malloc(100);
    sprintf(str, "%.2f", m->data.numVal);
    return str;
}

char* string_tostring(avm_memcell* m) {
    return strdup(m->data.strVal);
}

char* bool_tostring(avm_memcell* m) {
    return strdup(m->data.boolVal ? "true" : "false");
}

char* table_tostring(avm_memcell* m) {
    if (m->type == table_m) {
        avm_table* table = m->data.tableVal;
        unsigned indexOld = 212;
        std::cout << "[";
        for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; i++) {
            avm_table_bucket* bucket = table->strIndexed[i];
            while (bucket) {
                if (indexOld == i) break;
                indexOld = i;
                avm_memcell* key = &bucket->key;
                avm_memcell* value = &bucket->value;
                std::cout << " {" << avm_tostring(key) << ":" << avm_tostring(value) << "},";
                bucket = bucket->next;
            }
            avm_table_bucket* bucket2 = table->numIndexed[i];
            while (bucket2) {
                if(indexOld == i) break;
                indexOld = i;
                avm_memcell* key = &bucket2->key;
                avm_memcell* value = &bucket2->value;
                std::cout << " " << avm_tostring(value) << ",";
                bucket2 = bucket2->next;
            }
        }
        std::cout << "]";
    }
    return strdup("");
}

char* userfunc_tostring(avm_memcell* m) {
    char* str = (char*)malloc(100);
    sprintf(str, "userfunc %d", m->data.userfuncVal);
    return str;
}

char* libfunc_tostring(avm_memcell* m) {
    return strdup(m->data.libfuncVal);
}

char* nil_tostring(avm_memcell* m) {
    return strdup("nil");
}

char* undef_tostring(avm_memcell* m) {
    return strdup("undef");
}

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};

char* avm_tostring(avm_memcell* m) {
  assert(m->type >= 0 && m->type <= undef_m);
  return (*tostringFuncs[m->type])(m);
}

double      consts_getnumber(unsigned int index) { return numbers[index]; }
char*       consts_getstring(unsigned int index) { return strings[index]; }
char*       libfuncs_getused(unsigned int index) { return libFuncs[index]; }
userfunc*   userfuncs_getfunc(unsigned int index) { return userFuncs[index]; }

userfunc* avm_getfuncinfo(unsigned address) {
    for(unsigned i = 0; i < userFuncs.size(); ++i) {
        if(userFuncs[i]->address == address) {
            return userFuncs[i];
        }
    }
    return NULL;
}

extern void load_binary(char* filename);
extern void execute_cycle();

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    load_binary(argv[1]);
    avm_initstack();
    codeSize = code.size();

    while(!executionFinished) execute_cycle();
    return 0;
}