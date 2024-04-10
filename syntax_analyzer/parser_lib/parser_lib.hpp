#include "../symbol_table/symbol_table.hpp"
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

int alpha_yyerror(const char* yaccProvidedMessage);
int alpha_yylex(void);
char* make_anonymous_func();
bool is_libfunc(char* id);
void print_error(const char* msg);