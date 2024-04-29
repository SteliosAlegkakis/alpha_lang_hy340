#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include "../symbol_table/symbol_table.hpp"
using namespace std;
#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(struct quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(struct quad) + CURR_SIZE)

enum iopcode {
    _assign, _add, _sub, _mul, _div, _mod, _uminus, 
    _and, _or, _not, _if_eq, _if_noteq, _if_lesseq, 
    _if_greatereq, _if_less, _if_greater, _call, _param, 
    _ret, _getretval, _funcstart, _funcend, _tablecreate, 
    _tablegetelem, _tablesetelem, _jump
};

enum expr_t {
    var_e, 
    tableitem_e, 

    libraryfunc_e, 
    programfunc_e,
    
    arithexpr_e, 
    boolexpr_e, 
    assignexpr_e, 
    newtable_e,
    
    constnum_e, 
    constbool_e, 
    conststring_e, 

    nil_e
};

struct expr {
    expr_t        type;
    SymtabEntry*  sym;
    expr*         index;
    double        numConst;
    unsigned char boolConst;
    char*         strConst;
    unsigned int  libraryFunc;
    struct expr*  next;
};


struct quad {
    iopcode  op;
    expr*    result;
    expr*    arg1;
    expr*    arg2;
    unsigned label;
    unsigned line;
};

struct call {
    expr*         elist;
    unsigned char method;
    char*         name;
};

struct stmt {};


scopespace_t curr_scopespace(void);
unsigned curr_scope_offset(void);
void in_curr_scope_offset(void);
void enter_scopespace(void);
void exit_scopespace(void);
void _expand(void);
void _emit(iopcode op, expr* arg1, expr* arg2, expr* result);
char* _newtempname(void);
void _resettemp(void);
SymtabEntry* _newtemp(void);
void reset_formal_arg_offset(void);
void reset_function_locals_offset(void);
void restore_curr_scope_offset(unsigned n);
unsigned int next_quad_label(void);
void patch_label(unsigned quad_No, unsigned label);
expr* lvalue_expr(SymtabEntry* sym);
expr* new_expr(expr_t _t);
expr* new_expr_const_string(char* s);
expr* new_expr_const_num(double _i);
expr* new_expr_const_bool(unsigned int _b);
expr* emit_if_table_item(expr* e);
expr* make_call(expr* _lv, expr* _elist);
void comperror();
unsigned int is_temp_name(char* s);
unsigned int is_temp_expr(expr* e);
char* iopcode_tostring(iopcode op);
char* expr_tostring(expr* e);
