#include <string>
#define AVM_TABLE_HASHSIZE 211
#define AVM_STACKENV_SIZE 4
#define AVM_STACKSIZE 4096

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

struct userfunc {
    unsigned address;
    unsigned localSize;
    char*    id;
};

enum avm_memcell_t {
    number_m = 0,
    string_m = 1,
    bool_m = 2,
    table_m = 3,
    userfunc_m = 4,
    libfunc_m = 5,
    nil_m = 6,
    undef_m = 7
};

struct avm_memcell {
    enum avm_memcell_t type;
    union {
        double numVal;
        char* strVal;
        unsigned char boolVal;
        struct avm_table* tableVal;
        unsigned userfuncVal;
        char* libfuncVal;
    } data;
};

struct avm_table_bucket{
    avm_memcell         key;
    avm_memcell         value;
    avm_table_bucket*   next;
};

struct avm_table{
    unsigned int        refCounter;
    avm_table_bucket*   strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket*   numIndexed[AVM_TABLE_HASHSIZE];
    unsigned int        total; 
};