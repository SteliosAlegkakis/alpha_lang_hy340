#include "avm.hpp"
#include <cstring>
#include <math.h>

void libfunc_print (void) {
    for(unsigned i = 0; i < avm_totalactuals(); i++) {
        char* s = avm_tostring(avm_getactual(i));
        printf("%s",s);
        free(s);
    }
    avm_memcellclear(&retval);
    retval.type = nil_m;
}

void libfunc_typeof (void) {
    if(avm_totalactuals() < 1) {
        avm_error((char*)"1 argument expected in 'typeof' %d found!", avm_totalactuals());
    } else if(avm_totalactuals() > 1) {
        avm_warning((char*)"1 argument expected in 'typeof' %d found!", avm_totalactuals());
    }
    
    avm_memcellclear(&retval);
    retval.type = string_m;
    retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
}

void libfunc_totalarguments (void) {
    if(avm_totalactuals()) {
        avm_warning((char*)"0 arguments expected in 'totalarguments' %d found!", avm_totalactuals());
    } 

    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if(p_topsp == top + AVM_NUMACTUALS_OFFSET + avm_totalactuals()) {
        retval.type = nil_m;
    } else {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_argument (void) {
    if(avm_totalactuals() < 1) {
        avm_error((char*)"1 argument expected in 'argument' %d found!", avm_totalactuals());
    } else if(avm_totalactuals() > 1) {
        avm_warning((char*)"1 argument expected in 'argument' %d found!", avm_totalactuals());
    }

    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if(p_topsp == top + AVM_NUMACTUALS_OFFSET + avm_totalactuals()) {
        retval.type = nil_m;
    } else {
        unsigned i = avm_getactual(0)->data.numVal;
        if(i < 0 || i >= avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET)) {
            avm_error((char*)"invalid argument index (%d) in 'argument'!", i);
        } else {
            avm_assign(&retval, &stack[p_topsp + AVM_NUMACTUALS_OFFSET + i + 1]);
        }
    }
}

void libfunc_input (void) {
    if(avm_totalactuals()) {
        avm_warning((char*)"0 arguments expected in 'input' %d found!", avm_totalactuals());
    }

    size_t size = 32;
    size_t len = 0;
    char* input = (char*)malloc(size * sizeof(char));

    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) {
        if(len >= size) {
            size *= 2;
            input = (char*)realloc(input, size * sizeof(char));
        }
        input[len++] = (char)ch;
    }
    input[len] = '\0';
    

    if(atof(input)) {
        retval.type = number_m;
        retval.data.numVal = atof(input);
    } else if(strcmp(input, "true") == 0) {
        retval.type = bool_m;
        retval.data.boolVal = 1;
    } else if(strcmp(input, "false") == 0) {
        retval.type = bool_m;
        retval.data.boolVal = 0;
    } else if(strcmp(input, "nil") == 0) {
        retval.type = nil_m;
    } else {
        bool quotes = false;
        if(input[0] == '\"' && input[strlen(input) - 1] == '\"') {
            input++;
            input[strlen(input) - 1] = '\0';
            quotes = true;
        }
        retval.type = string_m;
        retval.data.strVal = strdup(input);
        if(quotes) {
            input--;
            input[strlen(input) + 1] = '\0';
            input[0] = '\"';
            input[strlen(input)] = '\"';
        }
    }

    free(input);
}

void libfunc_objectmemberkeys (void) {}

void libfunc_objecttotalmembers (void) {
    if(avm_totalactuals() < 1) {
        avm_error((char*)"1 argument expected in 'objecttotalmembers' %d found!", avm_totalactuals());
    } else if(avm_totalactuals() > 1) {
        avm_warning((char*)"1 argument expected in 'objecttotalmembers' %d found!", avm_totalactuals());
    }

    avm_memcell* arg = avm_getactual(0);
    if(arg->type != table_m) avm_error((char*)"argument is not a table in 'objecttotalmembers'!");
    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = arg->data.tableVal->total;
}

void libfunc_objectcopy (void) {}

void libfunc_strtonum (void) {
    if(avm_totalactuals() < 1) {
        avm_error((char*)"1 argument expected in 'strtonum' %d found!", avm_totalactuals());
    } else if(avm_totalactuals() > 1) {
        avm_warning((char*)"1 argument expected in 'strtonum' %d found!", avm_totalactuals());
    }

    avm_memcell* arg = avm_getactual(0);
    if(arg->type != string_m) avm_error((char*)"argument is not a string in 'strtonum'!");
    avm_memcellclear(&retval);
    if(atof(arg->data.strVal)) { 
        retval.type = number_m;
        retval.data.numVal = atof(arg->data.strVal);
    }
    else retval.type = nil_m;

}

void libfunc_sqrt (void) {
    if(avm_totalactuals() < 1){
        avm_warning((char*)"1 argument expected in 'typeof' %d found!", avm_totalactuals());
    } else if(avm_totalactuals() > 1) {
        avm_warning((char*)"1 argument expected in 'typeof' %d found!", avm_totalactuals());
    }

    avm_memcell* arg = avm_getactual(0);
    if(arg->type != number_m) avm_error((char*)"argument is not a number in 'sqrt'!");
    avm_memcellclear(&retval);
    if(arg->data.numVal < 0) retval.type = nil_m;
    else{
        retval.type = number_m;
        retval.data.numVal = sqrt(arg->data.numVal);
    }
}

void libfunc_cos (void) {
    if(avm_totalactuals() < 1) {
        avm_warning((char*)"1 argument expected in 'cos' %d found!", avm_totalactuals());
    } else if(avm_totalactuals() > 1) {
        avm_warning((char*)"1 argument expected in 'cos' %d found!", avm_totalactuals());
    }

    avm_memcell* arg = avm_getactual(0);
    if(arg->type != number_m) avm_error((char*)"argument is not a number in 'cos'!");
    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = cos(arg->data.numVal);
}

void libfunc_sin (void) {
    if(avm_totalactuals() < 1) { 
        avm_warning((char*)"1 argument expected in 'sin' %d found!", avm_totalactuals());
    } else if (avm_totalactuals() > 1) {
        avm_warning((char*)"1 argument expected in 'sin' %d found!", avm_totalactuals());
    }

    avm_memcell* arg = avm_getactual(0);
    if(arg->type != number_m) avm_error((char*)"argument is not a number in 'sin'!");
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
