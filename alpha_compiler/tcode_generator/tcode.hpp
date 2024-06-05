enum vmopcode {
    assign_v, add_v, sub_v, mul_v, div_v, mod_v, 
    jeq_v, jne_v, jge_v, jgt_v, jlt_v, jle_v,
    pusharg_v, funcenter_v, funcexit_v, call_v, newtable_v, 
    tablegetelem_v, tablesetelem_v, jump_v, nop_v
};

enum vmarg_t{
    label_a = 0, 
    global_a = 1, 
    formal_a = 2, 
    local_a = 3, 
    number_a = 4, 
    string_a = 5, 
    bool_a = 6, 
    nil_a = 7, 
    userfunc_a = 8, 
    libfunc_a = 9, 
    retval_a = 10
};

struct vmarg {
    enum vmarg_t type;
    unsigned val;
};

struct instruction {
    enum vmopcode opcode;
    struct vmarg  result;
    struct vmarg  arg1;
    struct vmarg  arg2;
    unsigned      srcLine;
};

void tcode_generate(void);
void tcode_print_instructions(void);
void tcode_generate_binary(char* filename);

