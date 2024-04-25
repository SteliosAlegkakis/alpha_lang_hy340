#include "../../icode_generator/icode.hpp"
#include <stack>

extern int alpha_yylineno;
extern char* alpha_yytext;
extern FILE* alpha_yyin;

extern FILE* rulesFile;
extern bool isFormal;
extern int loopCounter;
extern std::stack<int> loopCounterStack;
extern int functionCounter;
extern bool block_b;

int alpha_yyerror(const char* yaccProvidedMessage);
int alpha_yylex(void);
char* make_anonymous_func();
bool is_libfunc(char* id);
void print_error(const char* msg);

expr* manage_lvalue_id(char *name);
expr* manage_lvalue_local_id(char *name);
expr* manage_lvalue_global_id(char *name);

void manage_idlist_id(char *name);
void manage_idlist_comma_id(char* name);

char* manage_funcname_named(char* name);
char* manage_funcname_anonymous();
SymtabEntry* manage_funcprefix(char* functionName);
void manage_funcargs();
unsigned int manage_funcbody();
SymtabEntry* manage_funcdef(SymtabEntry* funcPrefix, unsigned int funcbody);

//puts all the library functions in the symbol table
void init_library_func();
