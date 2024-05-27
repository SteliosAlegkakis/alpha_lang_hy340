#include "avm.hpp"
#include <cstring>

void libfunc_print (void) {}
void libfunc_typeof (void) {}
void libfunc_totalarguments (void) {}
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