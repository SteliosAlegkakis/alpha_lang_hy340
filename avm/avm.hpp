#include "avm_structs.hpp"
#include <vector>

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v
#define AVM_ENDING_PC codeSize
#define AVM_NUMACTUALS_OFFSET 4
#define AVM_SAVEDPC_OFFSET 3
#define AVM_SAVEDTOP_OFFSET 2
#define AVM_SAVEDTOPSP_OFFSET 1

extern avm_memcell stack[AVM_STACKSIZE];
extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern std::vector<instruction*> code;

extern unsigned  pc;
extern unsigned int codeSize;
extern unsigned char executionFinished;
extern unsigned currLine;

extern const char* typeStrings[];

extern unsigned totalActuals;

void avm_memcellclear(avm_memcell* m);
avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

avm_table* avm_tablenew(void);
void avm_tabledestroy(avm_table* t);
avm_memcell* avm_tablegetelem(avm_table* t, avm_memcell* key);
void avm_tablesetelem(avm_table* t, avm_memcell* key, avm_memcell* value);
void avm_tableincref_counter(avm_table* t);
void avm_tabledecref_counter(avm_table* t);
void avm_tablebuckets_init(avm_table_bucket** p);
void avm_tablebuckets_destroy(avm_table_bucket** p);

void avm_assign(avm_memcell* lv, avm_memcell* rv);

void avm_dec_top (void);
void avm_push_envvalue (unsigned val);
unsigned avm_get_envvalue (unsigned i);
void avm_callsaveenvironment (void);
void avm_push_table_arg(avm_table* t);
void avm_call_functor(avm_table* t);
typedef void (*library_func_t) (void);
library_func_t avm_getlibraryfunc (char* id);
void avm_calllibfunc (char* id);

double      consts_getnumber(unsigned int index);
char*       consts_getstring(unsigned int index);
char*       libfuncs_getused(unsigned int index);
userfunc*   userfuncs_getfunc(unsigned int index);

userfunc* avm_getfuncinfo(unsigned address);

void avm_warning(char* format, ...);
void avm_error(char* format, ...);
char* avm_tostring(avm_memcell* m);