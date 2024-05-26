#include "../avm.hpp"
#include <cassert>

void execute_assign(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
    avm_memcell* rv = avm_translate_operand(&instr->result, &ax);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv);
    avm_assign(lv, rv);
}