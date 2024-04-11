#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
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

enum scopespace_t { programvar, functionlocal, formalarg };

enum symbol_t { var_s, programfunc_s, libraryfunc_s };

enum expr_t {
    var_e, tableitem_e, arithexpr_e, boolexpr_e, assignexpr_e, 
    newtable_e, constnum_e, constbool_e, conststring_e, nil_e, 
    libraryfunc_e, programfunc_e
};

struct symbol {
    symbol_t     type;
    char*        name;
    scopespace_t space;
    unsigned int offset;
    unsigned int scope;
    unsigned int line;
};

struct expr {
    expr_t        type;
    symbol*       sym;
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

scopespace_t curr_scopespace(void);
unsigned curr_scope_offset(void);
void in_curr_scope_offset(void);
void enter_scopespace(void);
void exit_scopespace(void);
void _expand(void);
void _emit(iopcode op,expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line);
char* _newtempname(void);
void _resettemp(void);
SymtabEntry* _newtemp(void);