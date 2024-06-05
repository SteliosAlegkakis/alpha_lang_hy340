#include "./executors/executors.hpp"
#include <vector>
#include <cassert>

typedef void (*execute_func_t) (instruction*);
execute_func_t executeFuncs[] = {
    execute_assign, 
    execute_add, 
    execute_sub, 
    execute_mul, 
    execute_div, 
    execute_mod,
    execute_jeq,
    execute_jne,
    execute_jge,
    execute_jgt,
    execute_jlt,
    execute_jle,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_call,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_jump,
    execute_nop
};

void execute_cycle() {
    if (executionFinished) {
        return;
    }
    else if (pc == AVM_ENDING_PC) {
        executionFinished = true;
        return;
    }
    else {
        assert(pc < AVM_ENDING_PC);
        instruction* instr = code[pc];
        assert(instr->opcode >=0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        if (instr->srcLine) {
            currLine = instr->srcLine;
        }
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if (pc == oldPC) {
            ++pc;
        }
    }
}

