#include "../avm.hpp"
#include <assert.h>
#include <string.h>

typedef unsigned char (*tobool_func_t) (avm_memcell*);

unsigned char number_tobool (avm_memcell* m) { return m->data.numVal != 0; }
unsigned char string_tobool (avm_memcell* m) { return m->data.strVal[0] != 0; }
unsigned char bool_tobool (avm_memcell* m) { return m->data.boolVal; }
unsigned char table_tobool (avm_memcell* m) { return 1; }
unsigned char userfunc_tobool (avm_memcell* m) { return 1; }
unsigned char libfunc_tobool (avm_memcell* m) { return 1; }
unsigned char nil_tobool (avm_memcell* m) { return 0; }
unsigned char undef_tobool (avm_memcell* m) { return 0; }

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

unsigned char avm_tobool (avm_memcell* m) {
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

void execute_jeq (instruction* instr) {
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if(rv2->type == undef_m) {
        avm_error((char*)"arg2 is undef in '=='!");
    } 
    else if (rv1->type == undef_m) {
        avm_error((char*)"arg1 is undef in '=='!");
    }
    else if(rv1->type == nil_m || rv2->type == nil_m) {
        result = rv1->type == nil_m && rv2->type == nil_m;
    } else if(rv1->type == bool_m || rv2->type == bool_m) {
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    } else if(rv1->type != rv2->type) {
        avm_error((char*)"%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else {
        switch(rv1->type) {
            case number_m:
                result = rv1->data.numVal == rv2->data.numVal;
                break;
            case string_m:
                result = !strcmp(rv1->data.strVal, rv2->data.strVal);
                break;
            case table_m:
                result = rv1->data.tableVal == rv2->data.tableVal;
                break;
            case userfunc_m:
                result = rv1->data.userfuncVal == rv2->data.userfuncVal;
                break;
            case libfunc_m:
                result = !strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
                break;
            default:
                assert(0);
        }
    }

    if(!executionFinished && result) {
        pc = instr->result.val;
    }
}

void execute_jne (instruction* instr) {
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m) {
        avm_error((char*)"undef involved in '!='!");
    } else if(rv1->type == nil_m || rv2->type == nil_m) {
        result = rv1->type != nil_m || rv2->type != nil_m;
    } else if(rv1->type == bool_m || rv2->type == bool_m) {
        result = (avm_tobool(rv1) != avm_tobool(rv2));
    } else if(rv1->type != rv2->type) {
        avm_error((char*)"%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else {
        switch(rv1->type) {
            case number_m:
                result = rv1->data.numVal != rv2->data.numVal;
                break;
            case string_m:
                result = strcmp(rv1->data.strVal, rv2->data.strVal);
                break;
            case table_m:
                result = rv1->data.tableVal != rv2->data.tableVal;
                break;
            case userfunc_m:
                result = rv1->data.userfuncVal != rv2->data.userfuncVal;
                break;
            case libfunc_m:
                result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
                break;
            default:
                assert(0);
        }
    }

    if(!executionFinished && result) {
        pc = instr->result.val;
    }
}

void execute_jge (instruction* instr) {
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m) {
        avm_error((char*)"undef involved in '>='!");
    } else if(rv1->type == nil_m || rv2->type == nil_m) {
        avm_error((char*)"nil involved in '>='!");
    } else if(rv1->type == bool_m || rv2->type == bool_m) {
        avm_error((char*)"bool involved in '>='!");
    } else if(rv1->type != rv2->type) {
        avm_error((char*)"%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else {
        switch(rv1->type) {
            case number_m:
                result = rv1->data.numVal >= rv2->data.numVal;
                break;
            case string_m:
                result = strcmp(rv1->data.strVal, rv2->data.strVal) >= 0;
                break;
            case table_m:
                result = rv1->data.tableVal >= rv2->data.tableVal;
                break;
            case userfunc_m:
                result = rv1->data.userfuncVal >= rv2->data.userfuncVal;
                break;
            case libfunc_m:
                result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal) >= 0;
                break;
            default:
                assert(0);
        }
    }

    if(!executionFinished && result) {
        pc = instr->result.val;
    }
}

void execute_jgt (instruction* instr) {
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m) {
        avm_error((char*)"undef involved in '>'!");
    } else if(rv1->type == nil_m || rv2->type == nil_m) {
        avm_error((char*)"nil involved in '>'!");
    } else if(rv1->type == bool_m || rv2->type == bool_m) {
        avm_error((char*)"bool involved in '>'!");
    } else if(rv1->type != rv2->type) {
        avm_error((char*)"%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else {
        switch(rv1->type) {
            case number_m:
                result = rv1->data.numVal > rv2->data.numVal;
                break;
            case string_m:
                result = strcmp(rv1->data.strVal, rv2->data.strVal) > 0;
                break;
            case table_m:
                result = rv1->data.tableVal > rv2->data.tableVal;
                break;
            case userfunc_m:
                result = rv1->data.userfuncVal > rv2->data.userfuncVal;
                break;
            case libfunc_m:
                result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal) > 0;
                break;
            default:
                assert(0);
        }
    }

    if(!executionFinished && result) {
        pc = instr->result.val;
    }
}

void execute_jlt (instruction* instr) {
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m) {
        avm_error((char*)"undef involved in '<'!");
    } else if(rv1->type == nil_m || rv2->type == nil_m) {
        avm_error((char*)"nil involved in '<'!");
    } else if(rv1->type == bool_m || rv2->type == bool_m) {
        avm_error((char*)"bool involved in '<'!");
    } else if(rv1->type != rv2->type) {
        avm_error((char*)"%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else {
        switch(rv1->type) {
            case number_m:
                result = rv1->data.numVal < rv2->data.numVal;
                break;
            case string_m:
                result = strcmp(rv1->data.strVal, rv2->data.strVal) < 0;
                break;
            case table_m:
                result = rv1->data.tableVal < rv2->data.tableVal;
                break;
            case userfunc_m:
                result = rv1->data.userfuncVal < rv2->data.userfuncVal;
                break;
            case libfunc_m:
                result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal) < 0;
                break;
            default:
                assert(0);
        }
    }

    if(!executionFinished && result) {
        pc = instr->result.val;
    }
}

void execute_jle (instruction* instr) {
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m) {
        avm_error((char*)"undef involved in '<='!");
    } else if(rv1->type == nil_m || rv2->type == nil_m) {
        avm_error((char*)"nil involved in '<='!");
    } else if(rv1->type == bool_m || rv2->type == bool_m) {
        avm_error((char*)"bool involved in '<='!");
    } else if(rv1->type != rv2->type) {
        avm_error((char*)"%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else {
        switch(rv1->type) {
            case number_m:
                result = rv1->data.numVal <= rv2->data.numVal;
                break;
            case string_m:
                result = strcmp(rv1->data.strVal, rv2->data.strVal) <= 0;
                break;
            case table_m:
                result = rv1->data.tableVal <= rv2->data.tableVal;
                break;
            case userfunc_m:
                result = rv1->data.userfuncVal <= rv2->data.userfuncVal;
                break;
            case libfunc_m:
                result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal) <= 0;
                break;
            default:
                assert(0);
        }
    }

    if(!executionFinished && result) {
        pc = instr->result.val;
    }
}

void execute_jump (instruction* instr) {
    pc = instr->result.val;
}

void execute_nop (instruction* instr) {}