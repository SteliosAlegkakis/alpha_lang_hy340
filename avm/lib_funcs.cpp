#include "avm.hpp"
#include <cstring>
#include <math.h>

void libfunc_print (void) {
    unsigned n = avm_totalactuals();
    for(unsigned i = 0; i < n; i++) {
        char* s = avm_tostring(avm_getactual(i));
        printf("%s",s);
        free(s);
    }
    avm_memcellclear(&retval);
    retval.type = nil_m;
}

void libfunc_typeof (void) {
    unsigned n = avm_totalactuals();
    if(n != 1) {
        avm_error((char*)"one argument (not %d) expected in 'typeof'!", n);
    } else {
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void libfunc_totalarguments (void) {
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);
    if(p_topsp == top + AVM_NUMACTUALS_OFFSET + avm_totalactuals()) {
        printf("not in a function call! p_topsp: %d top: %d\n", p_topsp, top);
        retval.type = nil_m;
    } else {
        printf("in function call! p_topsp: %d top: %d\n", p_topsp, top);
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_argument (void) {
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    unsigned n = avm_totalactuals();
    avm_memcellclear(&retval);

    if(p_topsp == top + AVM_NUMACTUALS_OFFSET + avm_totalactuals()) {
        retval.type = nil_m;
    }
    else if(n != 1) {
        avm_error((char*)"one argument (not %d) expected in 'argument'!", n);
    } else {
        unsigned i = avm_getactual(0)->data.numVal;
        if(i < 0 || i >= avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET)) {
            avm_error((char*)"invalid argument index in 'argument'!");
        } else {
            avm_assign(&retval, &stack[p_topsp + AVM_NUMACTUALS_OFFSET + i + 1]);
        }
    }
}

void libfunc_input (void) {}

void libfunc_objectmemberkeys (void) {}

void libfunc_objecttotalmembers (void) {}

void libfunc_objectcopy (void) {}

void libfunc_strtonum (void) {
    unsigned total = avm_totalactuals();
    if(total != 1) avm_error((char*)"one argument (not %d) expected in 'strtonum'!", total);
    avm_memcell* arg = avm_getactual(0);
    if(arg->type != string_m) avm_error((char*)"strtonum: argument is not a string!");
    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = atof(arg->data.strVal);
}

void libfunc_sqrt (void) {
    unsigned total = avm_totalactuals();
    if(total != 1){
        avm_error((char*)"one argument (not %d) expected in 'typeof'!", total);
    }
    avm_memcell* arg = avm_getactual(0);
    if(arg->type != number_m) avm_error((char*)"sqrt: argument is not a number!");
    avm_memcellclear(&retval);
    if(arg->data.numVal < 0) retval.type = nil_m;
    else{
        retval.type = number_m;
        retval.data.numVal = sqrt(arg->data.numVal);
    }
}

void libfunc_cos (void) {
    unsigned total = avm_totalactuals();
    if(total != 1) avm_error((char*)"one argument (not %d) expected in 'cos'!", total);
    avm_memcell* arg = avm_getactual(0);
    if(arg->type != number_m) avm_error((char*)"cos: argument is not a number!");
    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = cos(arg->data.numVal);
}

void libfunc_sin (void) {
    unsigned total = avm_totalactuals();
    if(total != 1) avm_error((char*)"one argument (not %d) expected in 'sin'!", total);
    avm_memcell* arg = avm_getactual(0);
    if(arg->type != number_m) avm_error((char*)"sin: argument is not a number!");
    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = sin(arg->data.numVal);
}

library_func_t avm_getlibraryfunc (char* id) {
    if(!strcmp(id, "print")) return libfunc_print;
    if(!strcmp(id, "typeof")) return libfunc_typeof;
    if(!strcmp(id, "totalarguments")) return libfunc_totalarguments;
    if(!strcmp(id, "argument")) return libfunc_argument;
    if(!strcmp(id, "input")) return libfunc_input;
    if(!strcmp(id, "objectmemberkeys")) return libfunc_objectmemberkeys;
    if(!strcmp(id, "objecttotalmembers")) return libfunc_objecttotalmembers;
    if(!strcmp(id, "objectcopy")) return libfunc_objectcopy;
    if(!strcmp(id, "strtonum")) return libfunc_strtonum;
    if(!strcmp(id, "sqrt")) return libfunc_sqrt;
    if(!strcmp(id, "cos")) return libfunc_cos;
    if(!strcmp(id, "sin")) return libfunc_sin;
    return (library_func_t) 0;
}