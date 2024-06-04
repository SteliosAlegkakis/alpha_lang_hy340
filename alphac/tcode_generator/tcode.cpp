#include "../icode_generator/icode.hpp"
#include "tcode.hpp"
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>

struct incomplete_jump{
    unsigned         instrNo;
    unsigned         iaddress;
};

FILE* instr_file;
unsigned ij_total = 0;
std::list<incomplete_jump*> incomplete_jumps;
std::vector<char*> strings;
std::vector<double> numbers;
std::vector<char*> libfuncs;
std::vector<SymtabEntry*> userfuncs;
std::stack <SymtabEntry*> funcStack;

instruction* instructions = (instruction*) 0;
unsigned total_instructions = 0;
unsigned curr_instr = 0;

extern quad* quads;
extern unsigned total;
unsigned int currProcessedQuad = 0;

unsigned const_newstring (char* s) { strings.push_back(s); return strings.size()-1; }
unsigned const_newnumber (double n) { numbers.push_back(n); return numbers.size()-1; }
unsigned libfuncs_newused (char* s) { libfuncs.push_back(s); return libfuncs.size()-1; }
unsigned userfuncs_newfunc (SymtabEntry* sym) { userfuncs.push_back(sym); return userfuncs.size()-1; }

void make_operand (expr* e, vmarg* arg) {
    switch(e->type) {
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case assignexpr_e:
        case newtable_e: {
            assert(e->sym);
            arg->val = e->sym->symbol.variable->offset;
            
            switch(e->sym->symbol.variable->space) {
                case programvar: arg->type = global_a; break;
                case functionlocal: arg->type = local_a; break;
                case formalarg: arg->type = formal_a; break;
                default: assert(0);
            }
            break;
        }
        case constbool_e: {
            arg->val = e->boolConst;
            arg->type = bool_a;
            break;
        }
        case conststring_e: {
            arg->val = const_newstring(e->strConst);
            arg->type = string_a;
            break;
        }
        case constnum_e: {
            arg->val = const_newnumber(e->numConst);
            arg->type = number_a;
            break;
        }
        case nil_e: {
            arg->type = nil_a;
            break;
        }
        case programfunc_e: {
            arg->val = userfuncs_newfunc(e->sym);
            arg->type = userfunc_a;
            break;
        }
        case libraryfunc_e: {
            arg->val = libfuncs_newused(e->sym->symbol.function->name);
            arg->type = libfunc_a;
            break;
        }
        default: assert(0);
    }
}

void reset_operand (vmarg* arg) {
    arg = (vmarg*)0;
}

void make_number_operand(vmarg* arg, double val){
    arg->val = const_newnumber(val);
    arg->type = number_a;
}

void make_bool_operand(vmarg* arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}

void make_ret_val_operand(vmarg* arg){
    arg->type = retval_a;
}

void add_incomplete_jump (unsigned _instrNo, unsigned _iaddress){
    incomplete_jump* jump = (incomplete_jump*)malloc(sizeof(incomplete_jump));
    jump->instrNo = _instrNo;
    jump->iaddress = _iaddress;
    incomplete_jumps.push_back(jump);
}

unsigned next_instruction_label(){
    return curr_instr;
}

void patch_incomplete_jumps(){
    for (std::list<incomplete_jump*>::iterator it = incomplete_jumps.begin(); it != incomplete_jumps.end(); it++){
        instructions[(*it)->instrNo].result.type = label_a;
        if ((*it)->iaddress == next_quad_label()){
            instructions[(*it)->instrNo].result.val = next_instruction_label();
        }
        else{
            instructions[(*it)->instrNo].result.val = quads[(*it)->iaddress].taddress;
        }
    }
}

void tcode_emit(instruction* instr){
    if (curr_instr == total_instructions){
        total_instructions += EXPAND_SIZE;
        instructions = (instruction*)realloc(instructions, total_instructions * sizeof(instruction));
    }
    instructions[curr_instr++] = *instr;
}

void generate(vmopcode op, quad* q){
    instruction instr;
    instr.opcode = op;
    instr.srcLine = q->line;
    if(q->result) make_operand(q->result, &instr.result);
    if(q->arg1) make_operand(q->arg1, &instr.arg1);
    if(q->arg2) make_operand(q->arg2, &instr.arg2);
    q->taddress = next_instruction_label();
    tcode_emit(&instr);
}

void generate_add(quad* q) { generate(add_v, q); }
void generate_sub(quad* q) { generate(sub_v, q); }
void generate_mul(quad* q) { generate(mul_v, q); }
void generate_div(quad* q) { generate(div_v, q); }
void generate_mod(quad* q) { generate(mod_v, q); }
void generate_uminus(quad* q) { 
    q->arg1 = new_expr_const_num(-1);
    generate(mul_v, q);
 }

void generate_new_table(quad* q) { generate(newtable_v,q); }
void generate_table_get_elem(quad* q){ generate(tablegetelem_v, q); }
void generate_table_set_elem(quad* q) { generate(tablesetelem_v, q); }

void generate_assign(quad* q) { generate(assign_v, q); }

void generate_nop(){
    instruction* t;
    t->opcode = nop_v;
    tcode_emit(t);
}

void generate_relational(vmopcode op, quad* q){
    instruction instr;
    instr.opcode = op;
    instr.srcLine = q->line;
    if(q->arg1) make_operand(q->arg1, &instr.arg1);
    if(q->arg2) make_operand(q->arg2, &instr.arg2);
    
    instr.result.type = label_a;
    if(q->label < currProcessedQuad){
        instr.result.val = quads[q->label].taddress;
    }
    else{
        add_incomplete_jump(next_instruction_label(), q->label);
    }
    q->taddress = next_instruction_label();
    tcode_emit(&instr);
}

void generate_jump(quad* q) { generate_relational(jump_v, q); }
void generate_jeq(quad* q) { generate_relational(jeq_v, q); }
void generate_jne(quad* q) { generate_relational(jne_v, q); }
void generate_jle(quad* q) { generate_relational(jle_v, q); }
void generate_jge(quad* q) { generate_relational(jge_v, q); }
void generate_jlt(quad* q) { generate_relational(jlt_v, q); }
void generate_jgt(quad* q) { generate_relational(jgt_v, q); }

void generate_not(quad* q){
    q->taddress = next_instruction_label();
    instruction instr;
    
    instr.opcode = jeq_v;
    make_operand(q->result, &instr.arg1);
    make_bool_operand(&instr.arg2, 0);
    instr.result.type = label_a;
    instr.result.val = next_instruction_label() + 3;
    tcode_emit(&instr);
    
    instr.opcode = assign_v;
    make_bool_operand(&instr.result, 0);
    reset_operand(&instr.arg2);
    make_operand(q->arg1, &instr.arg1);
    tcode_emit(&instr);
    
    instr.opcode = jump_v;
    reset_operand(&instr.arg1);
    reset_operand(&instr.arg2);
    instr.result.type = label_a;
    instr.result.val = next_instruction_label() + 2;
    tcode_emit(&instr);

    instr.opcode = assign_v;
    make_bool_operand(&instr.result, 1);
    reset_operand(&instr.arg2);
    make_operand(q->arg1, &instr.arg1);
    tcode_emit(&instr);
    
}

void generate_or(quad* q){
    q->taddress = next_instruction_label();
    instruction t;
    
    t.opcode = jeq_v;
    make_operand(q->arg1, &t.arg1);
    make_bool_operand(&t.arg2, 1);
    t.result.type = label_a;
    t.result.val = next_instruction_label() + 4;
    tcode_emit(&t);
    
    make_operand(q->arg2, &t.arg1);
    t.result.val = next_instruction_label() + 3;
    tcode_emit(&t);
    
    t.opcode = assign_v;
    make_bool_operand(&t.result, 0);
    reset_operand(&t.arg2);   
    make_operand(q->result,&t.arg1);
    tcode_emit(&t);
    
    t.opcode = jump_v;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = next_instruction_label() + 2;
    tcode_emit(&t);
    
    t.opcode = assign_v;
    make_bool_operand(&t.result, 1);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.arg1);
    tcode_emit(&t);
}

void generate_and(quad* q) {
    q->taddress = next_instruction_label();
    instruction t;

    t.opcode = jeq_v;
    make_operand(q->arg1, &t.arg1);
    make_bool_operand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = next_instruction_label() + 4;
    tcode_emit(&t);
    
    make_operand(q->arg2, &t.arg1);
    t.result.val = next_instruction_label() + 3;
    tcode_emit(&t);

    t.opcode = assign_v;
    make_bool_operand(&t.result, 1);
    reset_operand(&t.arg2);   
    make_operand(q->result,&t.arg1);
    tcode_emit(&t);
    
    t.opcode = jump_v;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = next_instruction_label() + 2;
    tcode_emit(&t);
    
    t.opcode = assign_v;
    make_bool_operand(&t.result, 0);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.arg1);
    tcode_emit(&t);
}

void generate_param(quad* q) {
    q->taddress = next_instruction_label();
    instruction t;
    t.srcLine = q->line;
    t.opcode = pusharg_v;
    make_operand(q->arg1, &t.arg1);
    tcode_emit(&t);
}

void generate_call(quad* q){
    q->taddress = next_instruction_label();
    instruction t;
    t.srcLine = q->line;
    t.opcode = call_v;
    make_operand(q->arg1, &t.arg1);
    tcode_emit(&t);
}

void generate_get_ret_val(quad* q){
    q->taddress = next_instruction_label();
    instruction t;
    t.srcLine = q->line;
    t.opcode = assign_v;
    make_operand(q->result, &t.arg1);
    make_ret_val_operand(&t.result);
    tcode_emit(&t);
}

void generate_func_start(quad* q){
    SymtabEntry* f = q->arg1->sym;
    f->symbol.function->taddress = next_instruction_label() + 1;
    q->taddress = next_instruction_label();
    userfuncs_newfunc(f);
    funcStack.push(f);
    f->symbol.function->returnList.push_back(next_instruction_label());
    instruction t;
    t.srcLine = q->line;
    t.opcode = jump_v;
    t.result.type = label_a;
    tcode_emit(&t);
    reset_operand(&t.result);
    t.opcode = funcenter_v;
    make_operand(q->arg1, &t.result);
    tcode_emit(&t);
}

void back_patch(std::list<unsigned int> list){
    for (std::list<unsigned int>::iterator it = list.begin(); it != list.end(); ++it)
        instructions[*it].result.val = next_instruction_label();

    if(!list.empty()){
        instructions[list.front()].result.val = next_instruction_label() + 1;
    }
}

void generate_return(quad* q) {
    q->taddress = next_instruction_label();
    instruction t;
    if(q->result) {
        t.srcLine = q->line;
        t.opcode = assign_v;
        make_operand(q->result, &t.result);
        make_ret_val_operand(&t.arg1);
        tcode_emit(&t);
    }
    
    SymtabEntry* f = funcStack.top();
    f->symbol.function->returnList.push_back(next_instruction_label());
    t.srcLine = q->line;
    t.opcode = jump_v;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    tcode_emit(&t);
}

void generate_func_end(quad* q) {
    SymtabEntry* f = funcStack.top();
    funcStack.pop();
    back_patch(f->symbol.function->returnList);
    q->taddress = next_instruction_label();
    instruction t;
    t.srcLine = q->line;
    t.opcode = funcexit_v;
    make_operand(q->arg1, &t.result);
    tcode_emit(&t);
}

char* opcode_to_string(vmopcode op) {
    switch(op) {
        case assign_v: return (char*)"ASSIGN";
        case add_v: return (char*)"ADD";
        case sub_v: return (char*)"SUB";
        case mul_v: return (char*)"MUL";
        case div_v: return (char*)"DIV";
        case mod_v: return (char*)"MOD";
        case jeq_v: return (char*)"JEQ";
        case jne_v: return (char*)"JNE";
        case jle_v: return (char*)"JLE";
        case jge_v: return (char*)"JGE";
        case jlt_v: return (char*)"JLT";
        case jgt_v: return (char*)"JGT";
        case pusharg_v: return (char*)"PUSHARG";
        case funcenter_v: return (char*)"FUNCENTER";
        case funcexit_v: return (char*)"FUNCEXIT";
        case call_v: return (char*)"CALL";
        case newtable_v: return (char*)"NEWTABLE";
        case tablegetelem_v: return (char*)"TABLEGETELEM";
        case tablesetelem_v: return (char*)"TABLESETELEM";
        case jump_v: return (char*)"JUMP";
        case nop_v: return (char*)"NOP";
        default: assert(0);
    }
    return (char*)"";
}

void print_arg(vmarg arg) {
    switch(arg.type) {
        case label_a: fprintf(instr_file, "(label_a: %d) ", arg.val + 1); break;
        case global_a: fprintf(instr_file, "(global_a: %d) ", arg.val); break;
        case formal_a: fprintf(instr_file, "(formal_a: %d) ", arg.val); break;
        case local_a: fprintf(instr_file, "local(%d) ", arg.val); break;
        case number_a: fprintf(instr_file, "(number_a: %d) ", arg.val); break;
        case string_a: fprintf(instr_file, "(string_a %d)", arg.val); break;
        case bool_a: fprintf(instr_file, "(bool_a: %d) ", arg.val); break;
        case nil_a: fprintf(instr_file, "nil_a "); break;
        case userfunc_a: fprintf(instr_file, "(userfunc_a: %d)", arg.val); break;
        case libfunc_a: fprintf(instr_file, "(libfunc_a: %d) ", arg.val); break;
        case retval_a: fprintf(instr_file, "(retval_a )"); break;
        default: ;
    }
}

void tcode_print_instructions() {
    instr_file = fopen("instructions.txt", "w");
    for(unsigned i = 0; i < curr_instr; i++) {
        fprintf(instr_file,"%d: ", i + 1);
        fprintf(instr_file,"%s ", opcode_to_string(instructions[i].opcode));
        switch(instructions[i].opcode) {
            case assign_v:
                print_arg(instructions[i].result);
                print_arg(instructions[i].arg1);
                break;
            case pusharg_v:
                print_arg(instructions[i].arg1);
                break;
            case funcenter_v:
                print_arg(instructions[i].result);
                break;
            case funcexit_v:
                print_arg(instructions[i].result);
                break;
            case call_v:
                print_arg(instructions[i].arg1);
                break;
            case newtable_v:
                print_arg(instructions[i].result);
                break;
            case jump_v:
                print_arg(instructions[i].result);
                break;
            default:
                print_arg(instructions[i].arg1);
                print_arg(instructions[i].arg2);
                print_arg(instructions[i].result);
                break;
        }
        fprintf(instr_file," [line: %d]\n", instructions[i].srcLine);
    }
    fclose(instr_file);
} 

typedef void (*generate_func_t)(quad*);

generate_func_t generators[] = {
    generate_assign,            generate_add,            generate_sub,       generate_mul, 
    generate_div,               generate_mod,            generate_uminus,    generate_and, 
    generate_or,                generate_not,            generate_jeq,       generate_jne, 
    generate_jle,               generate_jge,            generate_jlt,       generate_jgt, 
    generate_call,              generate_param,          generate_return,    generate_get_ret_val, 
    generate_func_start,        generate_func_end,       generate_new_table, generate_table_get_elem, 
    generate_table_set_elem,    generate_jump
};

void read_binary(char* filename);

void tcode_generate(){
    for (unsigned i = 0; i < next_quad_label(); i++) {
        (*generators[quads[i].op])(quads + i);
        currProcessedQuad++;
    }

    patch_incomplete_jumps();
}

extern unsigned int totalGlobals;
void tcode_generate_binary_vectors(char* filename) {
    std::ofstream bin;
    bin.open(filename, std::ios::binary);

    //print magic number
    unsigned int magicNumber = 340200501;
    bin.write(reinterpret_cast<const char*>(&magicNumber), sizeof(magicNumber));
    
    //print total globals
    bin.write(reinterpret_cast<const char*>(&totalGlobals), sizeof(totalGlobals));

    //print numbers
    size_t numbersSize = numbers.size();
    bin.write(reinterpret_cast<const char*>(&numbersSize), sizeof(numbersSize));
    bin.write(reinterpret_cast<const char*>(numbers.data()), numbersSize * sizeof(double));
    
    //print strings
    size_t stringSize = strings.size();
    bin.write(reinterpret_cast<const char*>(&stringSize), sizeof(stringSize));
    for (const auto& str : strings) {
        size_t length = std::strlen(str);
        bin.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Write string length
        bin.write(str, length);
    }

    //print libfuncs
    size_t libfuncsSize = libfuncs.size();
    bin.write(reinterpret_cast<const char*>(&libfuncsSize), sizeof(libfuncsSize));
    for (const auto& libfunc : libfuncs) {
        size_t length = std::strlen(libfunc);
        bin.write(reinterpret_cast<const char*>(&length), sizeof(length));
        bin.write(libfunc, length);
    }

    //print userfuncs
    size_t userfuncsSize = userfuncs.size();
    bin.write(reinterpret_cast<const char*>(&userfuncsSize), sizeof(userfuncsSize));
    std::vector<unsigned> ufAddresses;
    std::vector<unsigned> ufLocals;
    std::vector<char*> ufNames;
    for(int i = 0; i < userfuncsSize; i++) {
        ufAddresses.push_back(userfuncs[i]->symbol.function->taddress);
        ufLocals.push_back(userfuncs[i]->symbol.function->totalLocals);
        ufNames.push_back(userfuncs[i]->symbol.function->name);    
    }
    bin.write(reinterpret_cast<const char*>(ufAddresses.data()), userfuncsSize * sizeof(unsigned int));
    bin.write(reinterpret_cast<const char*>(ufLocals.data()), userfuncsSize * sizeof(unsigned int));
    for(int i = 0; i < userfuncsSize; i++) {
        size_t length = std::strlen(ufNames[i]);
        bin.write(reinterpret_cast<const char*>(&length), sizeof(length));
        bin.write(ufNames[i], length);
    }
    
    bin.close();
}

void tcode_generate_binary_instructions(char* filename) {
    std::ofstream bin;
    bin.open(filename, std::ios::binary | std::ios::app);
    size_t total = curr_instr;
    bin.write(reinterpret_cast<const char*>(&total), sizeof(total));
    std::vector<vmopcode> opcodes;
    std::vector<vmarg> results;
    std::vector<vmarg> arg1s;
    std::vector<vmarg> arg2s;
    std::vector<unsigned> srcLines;
    for(int i = 0; i < curr_instr; i++) {
        opcodes.push_back(instructions[i].opcode);
        results.push_back(instructions[i].result);
        arg1s.push_back(instructions[i].arg1);
        arg2s.push_back(instructions[i].arg2);
        srcLines.push_back(instructions[i].srcLine);
    }
    bin.write(reinterpret_cast<const char*>(opcodes.data()), total * sizeof(vmopcode));
    bin.write(reinterpret_cast<const char*>(results.data()), total * sizeof(vmarg));
    bin.write(reinterpret_cast<const char*>(arg1s.data()), total * sizeof(vmarg));
    bin.write(reinterpret_cast<const char*>(arg2s.data()), total * sizeof(vmarg));
    bin.write(reinterpret_cast<const char*>(srcLines.data()), total * sizeof(unsigned));
    bin.close();
}

void tcode_generate_binary(char* filename) {
    tcode_generate_binary_vectors(filename);
    tcode_generate_binary_instructions(filename);
}