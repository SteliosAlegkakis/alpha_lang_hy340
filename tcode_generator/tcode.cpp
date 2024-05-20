#include "../avm/avm_structs.hpp"
#include "../icode_generator/icode.hpp"
#include "tcode.hpp"
#include <list>
#include <vector>
#include <stack>

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
    make_operand(q->result, &instr.result);
    make_operand(q->arg1, &instr.arg1);
    make_operand(q->arg2, &instr.arg2);
    q->taddress = next_instruction_label();
    tcode_emit(&instr);
}

void generate_add(quad* q) { generate(add_v, q); }
void generate_sub(quad* q) { generate(sub_v, q); }
void generate_mul(quad* q) { generate(mul_v, q); }
void generate_div(quad* q) { generate(div_v, q); }
void generate_mod(quad* q) { generate(mod_v, q); }

void generate_new_table(quad* q) { generate(newtable_v,q); }
void generate_tableget_elem(quad* q){ generate(tablegetelem_v, q); }
void generate_tables_elem(quad* q) { generate(tablesetelem_v, q); }

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
    make_operand(q->arg1, &instr.arg1);
    make_operand(q->arg2, &instr.arg2);
    
    instr.result.type = label_a;
    if(q->label < next_quad_label()){
        instr.result.val = quads[q->label].taddress;
    }
    else{
        add_incomplete_jump(curr_instr, q->label);
    }
    
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
    make_operand(q->arg1, &instr.arg1);
    make_bool_operand(&instr.arg2, 0);
    instr.result.type = label_a;
    instr.result.val = next_instruction_label() + 3;
    tcode_emit(&instr);
    
    instr.opcode = assign_v;
    make_bool_operand(&instr.arg1, 0);
    // reset_operand(&instr.arg2);
    make_operand(q->result, &instr.result);
    tcode_emit(&instr);
    
    instr.opcode = jump_v;
    // reset_operand(&instr.arg1);
    // reset_operand(&instr.arg2);
    instr.result.type = label_a;
    instr.result.val = next_instruction_label() + 2;
    tcode_emit(&instr);

    instr.opcode = assign_v;
    make_bool_operand(&instr.arg1, 1);
    // reset_operand(&instr.arg2);
    make_operand(q->result, &instr.result);
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
    make_bool_operand(&t.arg1, 0);
    // reset_operand(&t.arg2);   
    make_operand(q->result,&t.result);
    tcode_emit(&t);
    
    t.opcode = jump_v;
    //reset_operand(&t.arg1);
    //reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = next_instruction_label() + 2;
    tcode_emit(&t);
    
    t.opcode = assign_v;
    make_bool_operand(&t.arg1, 1);
    //reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
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
    make_bool_operand(&t.arg1, 1);
    // reset_operand(&t.arg2);   
    make_operand(q->result,&t.result);
    tcode_emit(&t);
    
    t.opcode = jump_v;
    //reset_operand(&t.arg1);
    //reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = next_instruction_label() + 2;
    tcode_emit(&t);
    
    t.opcode = assign_v;
    make_bool_operand(&t.arg1, 0);
    //reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    tcode_emit(&t);
}

// void generate_param(quad* q) {
//     q->taddress = next_instruction_label();
//     instruction t;
//     t.opcode = 
// }

void generate_call(quad* q){
    q->taddress = next_instruction_label();
    instruction t;
    t.opcode = call_v;
    make_operand(q->arg1, &t.arg1);
    tcode_emit(&t);
}

void generate_get_ret_val(quad* q){
    q->taddress = next_instruction_label();
    instruction t;
    t.opcode = assign_v;
    make_operand(q->result, &t.result);
    make_ret_val_operand(&t.arg1);
    tcode_emit(&t);
}

void generate_func_start(quad* q){
    SymtabEntry* f = q->arg1->sym;
    f->symbol.function->taddress = next_instruction_label();
    q->taddress = next_instruction_label();
    userfuncs_newfunc(f);
    funcStack.push(f);
    instruction t;
    t.opcode = funcenter_v;
    make_operand(q->result, &t.result);
}

void generate_return(quad* q) {
    q->taddress = next_instruction_label();
    instruction t;
    t.opcode = assign_v;
    make_ret_val_operand(&t.result);
    make_operand(q->result, &t.arg1);
    tcode_emit(&t);
    
    SymtabEntry* f = funcStack.top();
    
}
