#include "../avm.hpp"
#include <cassert>
#include <cstring>

void execute_assign(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
    avm_memcell* rv = avm_translate_operand(&instr->result, &ax);
    // assert(&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval);
    assert(lv);
    assert(rv);
    avm_assign(lv, rv);
}