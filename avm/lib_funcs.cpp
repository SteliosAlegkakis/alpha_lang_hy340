#include "avm.hpp"
#include <cstring>

void libfunc_print (void) {
    unsigned n = avm_totalactuals();
    for(unsigned i = 0; i < n; i++) {
        char* s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
    avm_memcellclear(&retval);
}
void libfunc_typeof (void) {
    unsigned n = avm_totalactuals();
    if(n != 1) {
        avm_error("one argument (not %d) expected in 'typeof'!", n);
    } else {
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}
void libfunc_totalarguments (void) {
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
    avm_memcellclear(&retval);
    if(!p_topsp) {
        avm_error("'totalarguments' called outside a function!");
        retval.type = nil_m;
    } else {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}
void libfunc_argument (void) {}
void libfunc_input (void) {}
void libfunc_objectmemberkeys (void) {}
void libfunc_objecttotalmembers (void) {}
void libfunc_objectcopy (void) {}
void libfunc_strtonum (void) {}
void libfunc_sqrt (void) {}
void libfunc_cos (void) {}
void libfunc_sin (void) {}

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