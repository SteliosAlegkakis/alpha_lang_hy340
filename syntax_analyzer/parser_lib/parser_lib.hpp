#include "../symbol_table/symbol_table.hpp"

extern int alpha_yylineno;
extern char* alpha_yytext;
extern FILE* alpha_yyin;

int alpha_yyerror(const char* yaccProvidedMessage);
int alpha_yylex(void);
char* make_anonymous_func();
bool is_libfunc(char* id);
void print_error(const char* msg);