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

expr* manage_member_item_lvalue_lsquare_expr_rsquare(expr* lv, expr* _expr);

expr* manage_assignment(expr* lv, expr* _expr);

call* manage_methodcall(expr* elist, char* name);
expr* manage_call_funcdef(SymtabEntry* funcdef ,expr* elist);
expr* manage_call_lvalue_callsuffix(expr* lv, call* callsuffix);
call* manage_normcall(expr* elist);

expr* manage_arithmetic_operation(iopcode op, expr* arg1, expr* arg2);
expr* manage_relative_operation(iopcode op, expr* arg1, expr* arg2);
expr* manage_bool_operation(iopcode op, expr* arg1, expr* arg2);

expr* manage_uminus_expr(expr* _expr);
expr* manage_not_expr(expr* _expr);
expr* manage_plusplus_lvalue(expr* lv);
expr* manage_minusminus_lvalue(expr* lv);
expr* manage_lvalue_plusplus(expr* lv);
expr* manage_lvalue_minusminus(expr* lv);

expr* manage_objectdef_elist(expr* elist);
expr* manage_objectdef_indexed(expr* indexed);

expr* manage_elist(expr* _expr, expr* elist);
expr* manage_indexed(expr* indexedelem, expr* indexed);
expr* manage_indexedelem(expr* index, expr* value);

expr* manage_primary_funcdef(SymtabEntry* funcdef);

void manage_return_expr(expr* _expr);
void manage_return();

stmt_t* manage_statements(stmt_t* _stmts, stmt_t* _stmt);
stmt_t* manage_break();
stmt_t* manage_continue();

unsigned int manage_ifprefix(expr* _expr);
unsigned int manage_else();
void manage_if_else(unsigned int _if, unsigned int _else);

unsigned int manage_whilecond(expr* _expr);
stmt_t* manage_whilestmt(unsigned int whilestart, unsigned int whilecond, stmt_t* _stmt);

//puts all the library functions in the symbol table
void init_library_func();
