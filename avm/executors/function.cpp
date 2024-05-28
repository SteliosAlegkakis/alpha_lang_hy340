#include "../avm.hpp"
#include <cassert>
#include <string.h>

void execute_pusharg (instruction* instr) {
    avm_memcell* arg = avm_translate_operand(&instr->arg1, &ax);
    assert(arg);
    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

void execute_funcenter (instruction* instr) {
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == func->data.userfuncVal);
    
    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}

void execute_funcexit (instruction* instr) {
    unsigned oldTop = top;

    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while(++oldTop <= top)
        avm_memcellclear(&stack[oldTop]);
}

void execute_call (instruction* instr) {
    avm_memcell* func = avm_translate_operand(&instr->arg1, &ax);
    assert(func);
    avm_callsaveenvironment();
    switch(func->type) {

        case userfunc_m: {
            avm_callsaveenvironment();
            pc = func->data.userfuncVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc]->opcode == funcenter_v);
            break;
        }

        case string_m: avm_calllibfunc(func->data.strVal); break;
        case libfunc_m: avm_calllibfunc(func->data.libfuncVal); break;
        case table_m: avm_call_functor(func->data.tableVal); break;

        default: {
            avm_error((char*)"call: cannot bind %s to function!", typeStrings[func->type]);
            executionFinished = 1;
        }
    }
}