#include "icode.hpp"
unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;
quad*    quads = (quad*) 0;
unsigned total = 0;
unsigned int currQuad = 0;
int tmpcounter = 0;
FILE* quadsFile;
extern int alpha_yylineno;

void print_quads() {
    if(!quadsFile) quadsFile = fopen("quads.txt", "w");

    quad _quad;
    for(int i = 0; i < currQuad; i++){
        _quad = quads[i];
        char* op_str = iopcode_tostring(_quad.op);
        fprintf(quadsFile, "%d: %s ", i+1, op_str); free(op_str);
        if(_quad.arg1) { char* arg1_str = expr_tostring(_quad.arg1); fprintf(quadsFile, "%s ", arg1_str); free(arg1_str); }
        if(_quad.arg2) { char* arg2_str = expr_tostring(_quad.arg2); fprintf(quadsFile, "%s ", arg2_str); free(arg2_str); }
        if(_quad.result) { char* result_str = expr_tostring(_quad.result); fprintf(quadsFile, "%s ", result_str); free(result_str); }
        if(_quad.op == _if_eq || _quad.op == _jump || _quad.op == _if_noteq || _quad.op == _if_greater || _quad.op == _if_greatereq || _quad.op == _if_less || _quad.op == _if_lesseq)
            fprintf(quadsFile,"%u ",_quad.label+1);
        fprintf(quadsFile, "[line %u]\n", _quad.line);
    }
    
}

void _expand(void) {
    assert(total == currQuad);
    quad* p = (quad*) malloc (NEW_SIZE);
    if(quads){
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
    
}

void _emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned int label) {
    
    if(currQuad == total) 
        _expand();
    
    quad* newQuad = quads + currQuad++;
    newQuad->op = op;
    newQuad->arg1 = arg1;
    newQuad->arg2 = arg2;
    newQuad->result = result;
    newQuad->label = label;
    newQuad->line = alpha_yylineno; 
}

scopespace_t curr_scopespace(void) {
    if(scopeSpaceCounter == 1) return programvar;
    else if(scopeSpaceCounter % 2 == 0) return formalarg;
    else return functionlocal;
}

unsigned int curr_scope_offset(void) {
    switch(curr_scopespace()) {
        case programvar: return programVarOffset;
        case functionlocal: return functionLocalOffset;
        case formalarg: return formalArgOffset;
        default: assert(0);
    }
    return 1;
}

void in_curr_scope_offset(void) {
    switch(curr_scopespace()) {
        case programvar: ++programVarOffset; break;
        case functionlocal: ++functionLocalOffset; break;
        case formalarg: ++formalArgOffset; break;
        default: assert(0);
    }
}

void enter_scopespace(void) {
    ++scopeSpaceCounter;
}   

void exit_scopespace(void) {
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

char* _newtempname(void) {
    char* tmp = (char*)"_t";
	int  length = strlen(tmp) + snprintf(NULL, 0, "%d", tmpcounter) + 1;
	char* result = (char*)malloc(length);

	if(result) {
		sprintf(result, "%s%d", tmp, tmpcounter++); 
		return result;
	}
	else {
		printf("Out of memmory\n"); 
		exit(EXIT_FAILURE);
	}
}

void _resettemp(void) {
    tmpcounter = 0;
}

SymtabEntry* _newtemp(void) {
    char* name = _newtempname();
    SymtabEntry* sym = symTab_lookup(name, get_current_scope());
    if (sym == NULL)
        return new SymtabEntry(get_current_scope(), name, alpha_yylineno, variable, local, var_s, curr_scopespace(), curr_scope_offset());
    return sym;
}

void reset_formal_arg_offset(void){
    formalArgOffset = 0;
}

void reset_function_locals_offset(void){
    functionLocalOffset = 0;
}

void restore_curr_scope_offset(unsigned n){
    switch(curr_scopespace()){
        case programvar:
            programVarOffset = n;
            break;
        case functionlocal:
            functionLocalOffset = n;
            break;
        case formalarg:
            formalArgOffset = n;
            break;
        default:
            assert(0);
    }
}

unsigned int next_quad_label(void){
    return currQuad;
}

void patch_label(unsigned quad_No, unsigned _label){
    assert(quad_No < currQuad);
    assert(!quads[quad_No].label);
    quads[quad_No].label = _label;
}

expr* lvalue_expr(SymtabEntry* _sym){
    assert(_sym);
    expr* e = (expr*) malloc (sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->next = (expr*) 0;
    e->sym = _sym;

    switch (_sym->symbol_t)
    {
    case var_s:
        e->type = var_e;
        break;
    case programfunc_s:
        e->type = programfunc_e;
        break;
    case libraryfunc_s:
        e->type = libraryfunc_e;
        break;
    default:
        assert(0);
    }

    return e;
}

expr* new_expr(expr_t _t){
    expr* _e = (expr*) malloc(sizeof(expr));
    memset(_e, 0 ,sizeof(expr));
    _e->type = _t;
    return _e; 
}

expr* new_expr_const_string(char* _s){
    expr* e = new_expr(conststring_e);
    e->strConst = strdup(_s);
    return e;
}

expr* emit_if_table_item(expr* e){
    if(e->type != tableitem_e){
        return e;
    }else{
        expr* _result = new_expr(var_e);
        _result->sym = _newtemp();
        _emit(_tablegetelem,e,e->index,_result,0);
        return _result;
    }
}

expr* member_item(expr* lv, char* name){
    lv = emit_if_table_item(lv);
    expr* item = new_expr(tableitem_e);
    item->sym = lv->sym;
    item->index = new_expr_const_string(name);
    return item;
}

expr* reverseList(expr* elist) {
    struct expr* prev = NULL;
    struct expr* current = elist;
    struct expr* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;      
        current = next;
    }
    elist = prev;
    return elist;
}

expr* make_call(expr* _lv, expr* _elist){
    assert(_lv);
   
    _elist = reverseList(_elist);
    expr* func = emit_if_table_item(_lv);
    while (_elist) {
        _emit(_param, _elist, NULL, NULL,0);
        _elist = _elist->next;
    }
    _emit(_call,func,NULL,NULL,0);
    expr* result = new_expr(var_e);
    result->sym = _newtemp();
    _emit(_getretval, NULL, NULL, result,0);
    return result;
}

expr* new_expr_const_num(double _i){
    expr* e1 = new_expr(constnum_e);
    e1->numConst = _i; 
    return e1;
}

unsigned int is_temp_name(char* s){
    return *s == '_';
}

unsigned int is_temp_expr(expr* e){
    return e->sym && is_temp_name(e->sym->symbol.variable->name);
}

expr* new_expr_const_bool(unsigned int _b){
    expr* e = new_expr(constbool_e);
    e->boolConst = !!_b;
    return e;
}

void comperror(const char* format, const char* context){
    char buffer[256];
    std::snprintf(buffer, sizeof(buffer), format, context);
    printf("\033[1;31m%s in line: %d\033[0m\n", buffer, alpha_yylineno);
}

bool check_arith(expr* e,const char* context){
    if(e->type == constbool_e || e->type == conststring_e || e->type == nil_e || e->type == newtable_e || e->type == programfunc_e || e->type == libraryfunc_e || e->type == boolexpr_e) {
        comperror("error, illegal expression used in %s",context);
        return false;
    }   
    return true;
}

char* iopcode_tostring(iopcode op) {
    switch (op) {
        case _assign: return strdup("assign");
        case _add: return strdup("add");
        case _sub: return strdup("sub");
        case _mul: return strdup("mul");
        case _div: return strdup("div");
        case _mod: return strdup("mod");
        case _uminus: return strdup("uminus");
        case _and: return strdup("and");
        case _or: return strdup("or");
        case _not: return strdup("not");
        case _if_eq: return strdup("if_eq");
        case _if_noteq: return strdup("if_noteq");
        case _if_lesseq: return strdup("if_lesseq");
        case _if_greatereq: return strdup("if_greatereq");
        case _if_less: return strdup("if_less");
        case _if_greater: return strdup("if_greater");
        case _call: return strdup("call");
        case _param: return strdup("param");
        case _ret: return strdup("ret");
        case _getretval: return strdup("getretval");
        case _funcstart: return strdup("funcstart");
        case _funcend: return strdup("funcend");
        case _tablecreate: return strdup("tablecreate");
        case _tablegetelem: return strdup("tablegetelem");
        case _tablesetelem: return strdup("tablesetelem");
        case _jump: return strdup("jump");
        default: assert(0);
    }
    return NULL;
}

char* expr_tostring(expr* e) {
    switch (e->type) {
        case var_e: 
            return strdup(e->sym->symbol.variable->name);
        case tableitem_e:
            return strdup(e->sym->uniontype == function?e->sym->symbol.function->name:e->sym->symbol.variable->name); break;
        case libraryfunc_e:
            return strdup(e->sym->symbol.function->name);
        case programfunc_e:
            return strdup(e->sym->symbol.function->name);
        case arithexpr_e:
            return strdup(e->sym->uniontype == function?e->sym->symbol.function->name:e->sym->symbol.variable->name); break;
        case boolexpr_e:
            return strdup(e->sym->uniontype == function?e->sym->symbol.function->name:e->sym->symbol.variable->name); break;
        case assignexpr_e:
            return strdup(e->sym->uniontype == function?e->sym->symbol.function->name:e->sym->symbol.variable->name); break;
        case newtable_e:
            return strdup(e->sym->uniontype == function?e->sym->symbol.function->name:e->sym->symbol.variable->name); break;
        case constnum_e: {
            char* str_num = (char*)malloc(sizeof(char) * 32);
            if(e->numConst == (int)e->numConst)
                sprintf(str_num, "%d", (int)e->numConst);
            else if(e->numConst == (double)e->numConst)
                sprintf(str_num, "%.1f", e->numConst);
            return str_num;
        }
        case constbool_e:
            return strdup(e->boolConst?"true":"false");
        case conststring_e:
            return strdup(e->strConst);
        case nil_e:
            return strdup("nil");
        default: assert(0);    
    }
    return NULL;
}

stmt_t* new_stmt(){
    stmt_t* s = (stmt_t*) malloc(sizeof(stmt_t));
    make_stmt(s);
    return s;
}

void make_stmt(stmt_t* s){
    s->breakList = s->contList = 0;
}

int new_list(int i){
    quads[i].label = 0;
    return i;
}

int merge_list(int l1, int l2){
    if(!l1){return l2;}
    else if(!l2) { return l1; }
    else{
        int i = l1;
        while(quads[i].label){
            i = quads[i].label;
        }
        quads[i].label = l2;
        return l1;
    }
}

void patch_list(int list, int label){
    while(list){
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}
