#include <iostream>
#include "../avm.hpp"

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

typedef void (*execute_func_t) (instruction*);



void execute_assign (instruction* instr);
void execute_arithmetic (instruction* instr);

void execute_jeq (instruction* instr);
void execute_jne (instruction* instr);
void execute_jge (instruction* instr);
void execute_jgt (instruction* instr);
void execute_jlt (instruction* instr);
void execute_jle (instruction* instr);

void execute_pusharg (instruction* instr);
void execute_funcenter (instruction* instr);
void execute_funcexit (instruction* instr);
void execute_call (instruction* instr);

void execute_newtable (instruction* instr);
void execute_tablegetelem (instruction* instr);
void execute_tablesetelem (instruction* instr);

void execute_jump (instruction* instr);
void execute_nop (instruction* instr);
