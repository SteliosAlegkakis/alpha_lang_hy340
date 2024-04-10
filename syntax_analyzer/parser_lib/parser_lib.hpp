tern#include "../symbol_table/symbol_table.hpp"
#include <stack>

extern int alpha_yylineno;
extern char* alpha_yytext;
extern FILE* alpha_yyin;

extern FILE* rulesFile;
extern bool isFormal;
extern int loopCounter;
extern std::stack<int> loopCounterStack;
extern int functionCounter;
extern SymtabEntry* lookup_tmp;
extern bool block_b;

int alpha_yyerror(const char* yaccProvidedMessage);
int alpha_yylex(void);
char* make_anonymous_func();
bool is_libfunc(char* id);
void print_error(const char* msg);

SymtabEntry* manage_lvalue_id(char *name);
SymtabEntry* manage_lvalue_local_id(char *name);
SymtabEntry* manage_lvalue_global_id(char *name);

void manage_idlist_id(char *name);
void manage_idlist_comma_id(char* name);
