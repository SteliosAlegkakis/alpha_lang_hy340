#include "parser_lib.hpp"
#include <math.h>

FILE* rulesFile;
int anonymousCounter = 0;
int functionCounter = 0;
bool isFormal = false;
bool block_b = false;
int loopCounter = 0;
std::vector<std::vector<int>> breakList;
std::vector<std::vector<int>> contList;
std::stack<int> loopCounterStack;
std::stack<unsigned int> scope_offset_stack;
bool error = false;
std::vector<char*> formals;

bool formals_contains(char* name) {
    for(auto it = formals.begin(); it != formals.end(); ++it) {
        if(!strcmp(*it, name)) return true;
    }
    return false;
}

int alpha_yyerror(const char* yaccProvidedMessage) {
	fprintf(stderr, "\033[1;31m%s: '%s' in line: %d\033[0m\n",yaccProvidedMessage, alpha_yytext, alpha_yylineno);
    error = true;
	return 0;
}

void print_error(const char* msg) { printf("\033[1;31m%s '%s' in line: %d\033[0m\n", msg, alpha_yytext, alpha_yylineno); error = true;}

bool is_libfunc(char* id) {
	if(!strcmp(id,"print")) return true;
	if(!strcmp(id,"input")) return true;
	if(!strcmp(id,"objectmemberkeys")) return true;
	if(!strcmp(id,"objectotalmember")) return true;
	if(!strcmp(id,"objectcopy")) return true;
	if(!strcmp(id,"totalarguments"))return true;
	if(!strcmp(id,"argument")) return true;
	if(!strcmp(id,"typeof")) return true;
	if(!strcmp(id,"strtonum")) return true;
	if(!strcmp(id,"sqrt")) return true;
	if(!strcmp(id,"cos")) return true;
	if(!strcmp(id,"sin")) return true;
	return false;
}

char* make_anonymous_func() {

	char* func = (char*)"_anonymousFunc";
	int  length = strlen(func) + snprintf(NULL, 0, "%d", anonymousCounter) + 1;
	char* result = (char*)malloc(length);

	if(result) {
		sprintf(result, "%s%d", func, anonymousCounter++); 
		return result;
	}
	else {
		printf("Out of memmory\n"); 
		exit(EXIT_FAILURE);
	}

}

expr* manage_lvalue_id(char *name) {
	if(functionCounter){
        if(symTab_lookup(name, get_current_scope())){
        assert(symTab_lookup(name,get_current_scope()));
            return lvalue_expr(symTab_lookup(name, get_current_scope()));
        }
        else if(symTab_lookup_infunc(name)){
            if(symTab_lookup_infunc(name)->uniontype == variable) {
                print_error("error, cannot acces identifier: ");
                exit(EXIT_FAILURE);
            }
        }
        else if(symTab_lookup(name, GLOBAL_SCOPE)) {
            assert(symTab_lookup(name, GLOBAL_SCOPE));
            return lvalue_expr(symTab_lookup(name, GLOBAL_SCOPE));
        }
        else {
            if(!is_libfunc(name)){
                symTab_insert(name, alpha_yylineno, variable, local, var_s, curr_scopespace(), curr_scope_offset());
                in_curr_scope_offset();
                assert(symTab_lookup(name, get_current_scope()));
                return lvalue_expr(symTab_lookup(name, get_current_scope()));
            }
        }
    }
    else if(symTab_lookup(name, get_current_scope())) {
        return lvalue_expr(symTab_lookup(name, get_current_scope()));
    }
    else if(!symTab_lookup(name)) {
        symTab_insert(name, alpha_yylineno, variable, local, var_s, curr_scopespace(), curr_scope_offset());
        in_curr_scope_offset();
        assert(symTab_lookup(name, get_current_scope()));
        return lvalue_expr(symTab_lookup(name, get_current_scope()));
    }
    return lvalue_expr(symTab_lookup(name));
}

expr* manage_lvalue_local_id(char* name) {
	if(!symTab_lookup(name, get_current_scope())){
        if(!is_libfunc(name)){
        	symTab_insert(name, alpha_yylineno, variable, local,var_s, curr_scopespace(), curr_scope_offset());
            in_curr_scope_offset();
            assert(symTab_lookup(name, get_current_scope()));
            return lvalue_expr(symTab_lookup(name, get_current_scope()));
        }
        else {
            print_error("error, cannot overide library functions:");
			exit(EXIT_FAILURE);
		}	
    }
    else {
        assert(symTab_lookup(name, get_current_scope()));
        return lvalue_expr(symTab_lookup(name, get_current_scope()));
    }
}

expr* manage_lvalue_global_id(char* name) {
	if(!symTab_lookup(name, GLOBAL_SCOPE)) {
            print_error("error, could not find global identifier:");
            exit(EXIT_FAILURE);
    }
	else {
        assert(symTab_lookup(name, GLOBAL_SCOPE));
        return lvalue_expr(symTab_lookup(name, GLOBAL_SCOPE));
    }
}

void manage_idlist_id(char* name) {
	if(isFormal){
        if(formals_contains(name))
            print_error("error, redifinition of formal argument:");
        else if (is_libfunc(name))
            print_error("error, cannot override library functions:");
        else {
            symTab_insert(name, alpha_yylineno, variable, formal, var_s, curr_scopespace(), curr_scope_offset());
            in_curr_scope_offset();
            formals.push_back(name);
        }
    }
    else if(!symTab_lookup(name, get_current_scope())) {
        symTab_insert(name, alpha_yylineno, variable, local, var_s, curr_scopespace(), curr_scope_offset());
        in_curr_scope_offset();
    }
}

void manage_idlist_comma_id(char* name) {
	if(isFormal){
        if(formals_contains(name))
            print_error("error, redifinition of formal argument:");
        else if (is_libfunc(name))
            print_error("error, cannot override library functions:");
    	else {
            symTab_insert(name, alpha_yylineno, variable, formal,var_s, curr_scopespace(), curr_scope_offset());
            in_curr_scope_offset();
            formals.push_back(name);
        }
    }
    else if(!symTab_lookup(name, get_current_scope())) {
        symTab_insert(name, alpha_yylineno, variable, local, var_s, curr_scopespace(), curr_scope_offset());
        in_curr_scope_offset();
    }
}

char* manage_funcname_named(char* name) {
    functionCounter++;
    if(!symTab_lookup(name, get_current_scope())) {
        if(is_libfunc(name)) print_error("error, cannot override library functions:");
        else symTab_insert(name, alpha_yylineno, function, userfunc,programfunc_s, curr_scopespace(), curr_scope_offset());
    }
	else print_error("error, redefinition of identifier:");
    return strdup(name);
}

char* manage_funcname_anonymous() {
    functionCounter++; 
    char* function_name = make_anonymous_func();
    symTab_insert(function_name, alpha_yylineno, function, userfunc, programfunc_s, curr_scopespace(), curr_scope_offset());
    return strdup(function_name);
}

SymtabEntry* manage_funcprefix(char* functionName) {
    assert(functionName);
    SymtabEntry* function = symTab_lookup(functionName, get_current_scope());
    if(!function) {
        print_error("error, cannot override library functions:");
        exit(EXIT_FAILURE);
    }
    function->symbol.function->iaddress = next_quad_label();
    _emit(_funcstart, lvalue_expr(function), NULL, NULL ,0);
    increase_scope();
    isFormal = true;
    scope_offset_stack.push(curr_scope_offset());
    enter_scopespace();
    reset_formal_arg_offset();
    formals.clear();
    return function;
}

void manage_funcargs() {
    decrease_scope(); 
    isFormal = false; 
    loopCounterStack.push(loopCounter); 
    loopCounter=0;
    enter_scopespace();
    reset_function_locals_offset();
}

unsigned int manage_funcbody() {
    functionCounter--; 
    loopCounter = loopCounterStack.top(); 
    loopCounterStack.pop();
    unsigned int currScopeOffset = curr_scope_offset();
    exit_scopespace();
    return currScopeOffset;
}

SymtabEntry* manage_funcdef(SymtabEntry* funcPrefix, unsigned int funcBody){
    assert(funcPrefix);
    exit_scopespace();
    funcPrefix->symbol.function->totalLocals = funcBody;
    if(!scope_offset_stack.empty()) scope_offset_stack.pop();
    int offset;
    if(!scope_offset_stack.empty()) offset = scope_offset_stack.top();
    restore_curr_scope_offset(offset);
    _emit(_funcend,lvalue_expr(funcPrefix),NULL,NULL, 0);
    assert(funcPrefix);
    return funcPrefix;  
}

expr* manage_member_item_lvalue_lsquare_expr_rsquare(expr* lv, expr* _expr) {
    lv = emit_if_table_item(lv);
    expr* ti = new_expr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = _expr;
    return ti;
}

expr* manage_assignment(expr* lv, expr* _expr){
    assert(lv); assert(_expr);
    if(lv->sym->uniontype == function) 
        print_error("error, function id used as lvalue");

    expr* assignExpr = new_expr(assignexpr_e);
    if(lv->type == tableitem_e){
        _emit(_tablesetelem,lv,lv->index,_expr ,0);
        assignExpr = emit_if_table_item(lv);
        assignExpr->type = assignexpr_e;
    }
    else {
        _emit(_assign, lv, NULL, _expr, 0);
        assignExpr->sym = _newtemp();
        _emit(_assign, assignExpr, NULL, lv, 0);
    }
    return assignExpr;
}

call* manage_methodcall(expr* elist, char* name){
    assert(name);
    call* methodCall = (call*)malloc(sizeof(call));
    methodCall->elist = elist;
    methodCall->method = 1;
    methodCall->name = strdup(name);
    return methodCall;  
}

expr* manage_call_funcdef(SymtabEntry* funcdef ,expr* elist){
    assert(funcdef);
    expr* call;
    expr* func = new_expr(programfunc_e);
    func->sym = funcdef;
    call = make_call(func, elist);
    return call;
}

expr* manage_call_lvalue_callsuffix(expr* lv, call* callsuffix) {
    assert(lv); assert(callsuffix);

    lv = emit_if_table_item(lv);
    if (callsuffix->method == 1) {
        expr* table = lv;
        expr* elist = callsuffix->elist;
        while(elist) elist = elist->next;
        elist = lv;
        lv = emit_if_table_item(member_item(lv, callsuffix->name));
        _emit(_param, table, NULL, NULL, 0);
    }
    return make_call(lv, callsuffix->elist);
}

call* manage_normcall(expr* elist){
    call* normcall = (call*)malloc(sizeof(call));
    normcall->elist = elist;
    normcall->method = 0;
    normcall->name = NULL;
    return normcall;
}

expr* manage_arithmetic_operation(iopcode op, expr* arg1, expr* arg2) {
    assert(arg1); assert(arg2);
    
    if(!check_arith(arg1, "arithemtic operation") || !check_arith(arg2, "arithemtic operation")) {
        exit(EXIT_FAILURE);
    }

    if(arg1->type == constnum_e && arg2->type == constnum_e){
        double result;
        switch(op){
            case _add: result = arg1->numConst + arg2->numConst; break;
            case _sub: result = arg1->numConst - arg2->numConst; break;
            case _mul: result = arg1->numConst * arg2->numConst; break;
            case _div: result = arg1->numConst / arg2->numConst; break;
            case _mod: {
                if(arg2->numConst == 0) {
                    print_error("error, division by zero");
                    exit(EXIT_FAILURE);
                }
                result = fmod(arg1->numConst, arg2->numConst); 
                break;
            }
            default: assert(0);
        }
        return new_expr_const_num(result);
    }

    expr* result = new_expr(arithexpr_e);
    result->sym = is_temp_expr(arg1)? arg1->sym : is_temp_expr(arg2)? arg2->sym: _newtemp();
    _emit(op, arg1, arg2, result, 0);

    return result;
}

expr* manage_relative_operation(iopcode op, expr* arg1, expr* arg2) {
    assert(arg1); assert(arg2);

    if(arg1->type == constnum_e && arg2->type == constnum_e) {
        switch(op) {
            case _if_eq: return new_expr_const_bool(arg1->numConst == arg2->numConst);
            case _if_noteq: return new_expr_const_bool(arg1->numConst != arg2->numConst);
            case _if_lesseq: return new_expr_const_bool(arg1->numConst <= arg2->numConst);
            case _if_greatereq: return new_expr_const_bool(arg1->numConst >= arg2->numConst);
            case _if_less: return new_expr_const_bool(arg1->numConst < arg2->numConst);
            case _if_greater: return new_expr_const_bool(arg1->numConst > arg2->numConst);
            default: assert(0);
        }
    }

    if(op == _if_eq || op == _if_noteq) {

        if((arg1->type == nil_e && arg2->type == tableitem_e) || (arg1->type == tableitem_e && arg2->type == nil_e)){
            switch (op) {
                case _if_eq:     return new_expr_const_bool(0);
                case _if_noteq:  return new_expr_const_bool(1);
                default: ;
            }
        }

        if(arg1->type == arg2->type) {
            if(op == _if_eq) {
                switch(arg2->type) {
                    case constnum_e: return new_expr_const_bool(arg1->numConst == arg2->numConst);
                    case constbool_e: return new_expr_const_bool(arg1->boolConst == arg2->boolConst);
                    case conststring_e: return new_expr_const_bool(!strcmp(arg1->strConst, arg2->strConst));
                    case programfunc_e: return new_expr_const_bool(arg1->sym == arg2->sym);
                    case libraryfunc_e: return new_expr_const_bool(arg1->sym == arg2->sym);
                    case nil_e: return new_expr_const_bool(1);
                    default: ;
                }   
            } 
            else {
                switch(arg2->type) {
                    case constnum_e: return new_expr_const_bool(arg1->numConst != arg2->numConst);
                    case constbool_e: return new_expr_const_bool(arg1->boolConst != arg2->boolConst);
                    case conststring_e: return new_expr_const_bool(strcmp(arg1->strConst, arg2->strConst));
                    case programfunc_e: return new_expr_const_bool(arg1->sym != arg2->sym);
                    case libraryfunc_e: return new_expr_const_bool(arg1->sym != arg2->sym);
                    case nil_e: return new_expr_const_bool(0);
                    default: ;
                }
            }
            
        }
    }

    if(arg1->type == nil_e && !(op == _if_eq || op == _if_noteq)) {
        print_error("error, expression 1 is of type nil and connot be used in relative operation");
        exit(EXIT_FAILURE);
    }

    if(arg2->type == nil_e && !(op == _if_eq || op == _if_noteq)) {
        print_error("error, expression 2 is of type nil and connot be used in relative operation");
        exit(EXIT_FAILURE);
    }

    expr* result = new_expr(boolexpr_e);
    // result->sym = is_temp_expr(arg1)? arg1->sym: is_temp_expr(arg2)? arg2->sym: _newtemp();
    result->sym = _newtemp();
    _emit(op, arg1, arg2, NULL , next_quad_label() + 3);
    _emit(_assign, result, NULL, new_expr_const_bool(0), 0);
    _emit(_jump, NULL, NULL, NULL, next_quad_label() + 2);
    _emit(_assign, result, NULL, new_expr_const_bool(1), 0);
    
    return result;
}

expr* manage_bool_operation(iopcode op, expr* arg1, expr* arg2) {
    assert(arg1); assert(arg2);
    expr* result = new_expr(boolexpr_e);
    // result->sym = is_temp_expr(arg1)? arg1->sym: is_temp_expr(arg2)? arg2->sym: _newtemp();
    result->sym = _newtemp();
    _emit(op, arg1, arg2, result, 0);
    return result;
}

expr* manage_uminus_expr(expr* _expr) {
    assert(_expr);
    check_arith(_expr, "unary minus");
    expr* term = new_expr(arithexpr_e);
    term->sym = is_temp_expr(_expr)? _expr->sym : _newtemp();
    _emit(_uminus, NULL, _expr, term, 0);
    return term;
}

expr* manage_not_expr(expr* _expr) {
    assert(_expr);
    expr* term = new_expr(boolexpr_e);
    term->sym = is_temp_expr(_expr)? _expr->sym : _newtemp();
    _emit(_not, term, NULL, _expr, 0);
    return term;
}

expr* manage_plusplus_lvalue(expr* lv) {
    assert(lv);
    if(lv->sym->uniontype == function) print_error("error, function id used as lvalue"); 
    check_arith(lv,"++lvvalue");
    expr* term = new_expr(var_e);
    term->sym = _newtemp();
    if(lv->type == tableitem_e){
        term = emit_if_table_item(lv);
        _emit(_add, term, new_expr_const_num(1),term, 0);
        _emit(_tablesetelem, lv,lv->index,term, 0);
    }else{
        _emit(_add,lv,new_expr_const_num(1), lv, 0);
        expr* _term = new_expr(arithexpr_e);
        _term->sym = _newtemp();
        _emit(_assign,_term,NULL,lv,0);
    }
    return term;
}

expr* manage_minusminus_lvalue(expr* lv) {
    assert(lv);
    if(lv->sym->uniontype == function) print_error("error, function id used as lvalue");
    check_arith(lv, "--lvalue");
    expr* term = new_expr(var_e);
    term->sym = _newtemp();
    if(lv->type == tableitem_e){
        term = emit_if_table_item(lv);
        _emit(_sub,term,new_expr_const_num(1),term,0);
        _emit(_tablesetelem,lv,lv->index,term,0);
    }else{
        _emit(_sub,lv,new_expr_const_num(1),lv,0);
        expr* _term = new_expr(arithexpr_e);
        _term->sym = _newtemp();
        _emit(_assign,_term,NULL,lv,0);
    }
    return term;
}

expr* manage_lvalue_plusplus(expr* lv) {
    assert(lv);
    if(lv->sym->uniontype == function) print_error("error, function id used as lvalue");
    check_arith(lv, "lvalue++");
    expr* term = new_expr(var_e);
    term->sym = _newtemp();
    if(lv->type == tableitem_e){
        expr* val = emit_if_table_item(lv);
        _emit(_assign,val,NULL,term,0);
        _emit(_add,val,new_expr_const_num(1),val,0);
        _emit(_tablesetelem,lv,lv->index,val,0);
    }else{
        _emit(_assign,term,NULL,lv,0);
        _emit(_add,lv,new_expr_const_num(1),lv,0);

    }

    return term;
}

expr* manage_lvalue_minusminus(expr* lv) {
    assert(lv);
    if(lv->sym->uniontype == function) print_error("error, function id used as lvalue");
   check_arith(lv,"lvalue--");
   expr* term = new_expr(var_e);
   term->sym = _newtemp();
   if(lv->type == tableitem_e){
    expr* val = emit_if_table_item(lv);
    _emit(_assign,val,NULL,term,0);
    _emit(_sub,val,new_expr_const_num(1),val,0);
    _emit(_tablesetelem,lv,lv->index,val,0);
   }else{
    _emit(_assign,term,NULL,lv,0);
    _emit(_sub,lv,new_expr_const_num(1),lv,0);
   }
    return term;
}

expr* manage_objectdef_elist(expr* elist) {
    expr* object = new_expr(newtable_e);
    object->sym = _newtemp();
    _emit(_tablecreate, NULL, NULL, object,0);
    for(int i = 0; elist; elist = elist->next) {
        if(!elist) break;
         _emit(_tablesetelem, object, new_expr_const_num(i++), elist,0);
    }

    return object;
}

expr* manage_objectdef_indexed(expr* indexed) {
    expr* object = new_expr(newtable_e);
    object->sym = _newtemp();
    _emit(_tablecreate, NULL, NULL, object,0);
    for(; indexed; indexed = indexed->next) {
        if(!indexed) break;
        _emit(_tablesetelem, object, indexed->index, indexed,0);
    }

    return object;
}

expr* manage_elist(expr* _expr, expr* elist) {
    _expr->next = elist;
    return _expr;
}

expr* manage_indexed(expr* indexedelem, expr* indexed) {
    indexedelem->next = indexed;
    return indexedelem;
}

expr* manage_indexedelem(expr* index, expr* value) {
    value->index = index;
    return value;
}

expr* manage_primary_funcdef(SymtabEntry* funcdef) {
    expr* func = new_expr(programfunc_e);
    func->sym = funcdef;
    return func;
}

void manage_return_expr(expr* _expr){
    if(!functionCounter) print_error("error, cannot use return outside of function");
    _emit(_ret,NULL,NULL,_expr,0);
	return;

}

void manage_return(){
     if(!functionCounter) print_error("error, cannot use return outside of function");
    _emit(_ret,NULL,NULL,NULL,0);
	return;
}

stmt_t* manage_statements(stmt_t* _stmts, stmt_t* _stmt){
    stmt_t* s = new_stmt();
    s->breakList = merge_list(_stmts->breakList, _stmt->breakList);
    s->contList = merge_list(_stmts->contList, _stmt->contList); 
    return s;
}

stmt_t* manage_break(){
    stmt_t* _break = (stmt_t*) malloc (sizeof(stmt_t));
    if(!loopCounter) print_error("error, cannot use break outside of loop:");
    make_stmt(_break);
    if(loopCounter) breakList[loopCounter-1].push_back(next_quad_label());
    _emit(_jump,NULL,NULL,NULL,0);
    return _break;
}

stmt_t* manage_continue(){
    stmt_t* _continue = (stmt_t*) malloc (sizeof(stmt_t));
    if(!loopCounter) print_error("error, cannot use continue outside of loop:");
    make_stmt(_continue);
    if(loopCounter) contList[loopCounter-1].push_back(next_quad_label());
    _emit(_jump,NULL,NULL,NULL,0);
    return _continue;
}

unsigned manage_ifprefix(expr* _expr){
    assert(_expr);
    _emit(_if_eq,_expr,new_expr_const_bool(1),NULL,next_quad_label()+2);
    unsigned ifprefix = next_quad_label();
    _emit(_jump,NULL,NULL,NULL,0);
    return ifprefix;
}

unsigned int manage_else(){
    unsigned int _elseprefix = next_quad_label();
    _emit(_jump,NULL,NULL,0,0);
    return _elseprefix;
}

void manage_if_else(unsigned int _if, unsigned int _else){
    patch_label(_if, _else + 1);
    patch_label(_else, next_quad_label());
}

unsigned int manage_whilecond(expr* _expr) {
    _emit(_if_eq, _expr, new_expr_const_bool(1),0,next_quad_label()+2);
    unsigned int whilecond = next_quad_label();
    _emit(_jump, NULL, NULL, NULL, 0);
    return whilecond;
}

stmt_t* manage_whilestmt(unsigned int whilestart, unsigned int whilecond, stmt_t* _stmt) {
    assert(_stmt);
    _emit(_jump, NULL, NULL, NULL,whilestart);
    patch_label(whilecond, next_quad_label());
    patch_list(breakList[loopCounter], next_quad_label());
    patch_list(contList[loopCounter], whilestart);
    breakList.pop_back();
    contList.pop_back();
    return _stmt;
}

unsigned int manage_N_rule() {
    unsigned int N_rule = next_quad_label();
    _emit(_jump, NULL, NULL, NULL, 0);
    return N_rule;
}

forprefix* manage_forprefix(unsigned int M_rule, expr* _expr) {
    forprefix* _forprefix = (forprefix*)malloc(sizeof(forprefix));
    _forprefix->test = M_rule;
    _forprefix->enter = next_quad_label();
    _emit(_if_eq, _expr, new_expr_const_bool(1), NULL,0);
    return _forprefix;
}

stmt_t* manage_forstmt(forprefix* _forprefix, unsigned int N1, unsigned int N2, stmt_t* loopstmt, unsigned int N3) {
    patch_label(_forprefix->enter, N2 + 1);
    patch_label(N1, next_quad_label());
    patch_label(N2, _forprefix->test);
    patch_label(N3, N1 + 1);
    patch_list(breakList[loopCounter], next_quad_label());
    patch_list(contList[loopCounter], N1 + 1);
    breakList.pop_back();
    contList.pop_back();
    return loopstmt;
}

void init_library_func(){
    symTab_insert((char*)"print" , 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"input" ,0 , function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"objectmemberkeys", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"objecttotalmembers",0 , function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"objectcopy", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"totalarguments", 0, function, libfunc, libraryfunc_s,curr_scopespace(), 0);
    symTab_insert((char*)"argument", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"typeof", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"strtonum", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"sqrt", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"cos", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"sin", 0, function,libfunc, libraryfunc_s, curr_scopespace(), 0);
}
