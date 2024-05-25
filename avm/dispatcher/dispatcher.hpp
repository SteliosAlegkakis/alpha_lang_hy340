#include <iostream>
#include "../avm.hpp"


#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v

avm_memcell ax, bx, cx, retval;
extern unsigned top, topsp;
extern unsigned char executionFinished = 0;
extern unsigned  pc = 0;
extern unsigned int currLine = 0;
extern unsigned codeSize = code.size();

typedef void (*execute_func_t) (instruction*);

void execute_assign (instruction* instr);
void execute_add (instruction* instr);
void execute_sub (instruction* instr);
void execute_mul (instruction* instr);
void execute_div (instruction* instr);
void execute_mod (instruction* instr);

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

