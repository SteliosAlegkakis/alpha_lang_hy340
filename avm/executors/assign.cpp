#include "../avm.hpp"
#include <cassert>
#include <cstring>

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

void execute_assign(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
    avm_memcell* rv = avm_translate_operand(&instr->result, &ax);
    // assert(&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval);
    assert(lv);
    assert(rv);
    avm_assign(lv, rv);
}