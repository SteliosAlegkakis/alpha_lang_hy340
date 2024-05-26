#include <cassert>
#include "dispatcher.hpp"
#include <cstring>

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

double add_impl(double x, double y) {return x + y;}
double sub_impl(double x, double y) {return x - y;}
double mul_impl(double x, double y) {return x * y;}
double div_impl(double x, double y) {return x / y;}
double mod_impl(double x, double y) {return ((unsigned)x) % ((unsigned)y);}

typedef double (*arithmetic_func_t)(double x, double y);

arithmetic_func_t arithmeticFuncs[] = {
   add_impl,
   sub_impl,
   mul_impl,
   div_impl,
   mod_impl
};


void execute_assign(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    avm_memcell* rv = avm_translate_operand(&instr->arg1, &ax);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv);
    avm_assign(lv, rv);
}

void avm_assign(avm_memcell* lv, avm_memcell* rv) {
    if (lv == rv) {
        return;
    }
    if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal) {
        return;
    }
    if (rv->type == undef_m) {
        avm_warning("assigning from 'undef' content!");
    }
    
    avm_memcellclear(lv);

    memcpy(lv, rv, sizeof(avm_memcell));

    if (lv->type == string_m) {
        lv->data.strVal = strdup(rv->data.strVal);
    } else if (lv->type == table_m) {
        avm_tableincref_counter(lv->data.tableVal);
    }
}

void execute_arithmetic(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv1 && rv2);
    if (rv1->type != number_m || rv2->type != number_m) {
        avm_error("not a number in arithmetic!");
        executionFinished = 1;
    } else {
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}