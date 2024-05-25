#include "avm_structs.hpp"
#include <vector>

extern avm_memcell stack[AVM_STACKSIZE];
extern std::vector<instruction*> code;
extern std::vector<char*> names;
extern std::vector<userfunc> userFuncs;
extern std::vector<double> numbers;
extern std::vector<char*> strings;
extern std::vector<char*> libFuncs;

void avm_memcellclear(avm_memcell* m);
avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

avm_table* avm_tablenew(void);
void avm_tabledestroy(avm_table* t);
avm_memcell* avm_tablegetelem(avm_table* t);
void avm_tablesetelem(avm_table* t, avm_memcell* key, avm_memcell* value);
void avm_tableincref_counter(avm_table* t);
void avm_tabledecref_counter(avm_table* t);
void avm_tablebuckets_init(avm_table_bucket** p);
void avm_table_bucket_destroy(avm_table_bucket** p);

double      consts_getnumber(unsigned int index);
char*       consts_getstring(unsigned int index);
char*       libfuncs_getused(unsigned int index);
userfunc*   userfuncs_getfunc(unsigned int index);

void avm_warning(char* format, ...);
void avm_error(char* format, ...);
void avm_assign(avm_memcell* lv, avm_memcell* rv);
