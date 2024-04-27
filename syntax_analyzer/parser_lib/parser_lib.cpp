#include "parser_lib.hpp"

FILE* rulesFile;
int anonymousCounter = 0;
int functionCounter = 0;
bool isFormal = false;
bool block_b = false;
int loopCounter;
std::stack<int> loopCounterStack;
std::stack<unsigned int> scope_offset_stack;


int alpha_yyerror(const char* yaccProvidedMessage) {
	fprintf(stderr, "\033[1;31m%s: '%s' in line: %d\033[0m\n",yaccProvidedMessage, alpha_yytext, alpha_yylineno);
	return 0;
}

void print_error(const char* msg) { printf("\033[1;31m%s '%s' in line: %d\033[0m\n", msg, alpha_yytext, alpha_yylineno); }

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
                assert(symTab_lookup(name, get_current_scope()));
                return lvalue_expr(symTab_lookup(name, get_current_scope()));
            }
        }
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
        if(symTab_lookup(name, get_current_scope()))
            print_error("error, redifinition of formal argument:");
        else if (is_libfunc(name))
            print_error("error, cannot override library functions:");
        else
            symTab_insert(name, alpha_yylineno, variable, formal, var_s, curr_scopespace(), curr_scope_offset());
    }
    else if(!symTab_lookup(name, get_current_scope()))
        symTab_insert(name, alpha_yylineno, variable, local, var_s, curr_scopespace(), curr_scope_offset());
}

void manage_idlist_comma_id(char* name) {
	if(isFormal){
        if(symTab_lookup(name, get_current_scope()))
            print_error("error, redifinition of formal argument:");
        else if (is_libfunc(name))
            print_error("error, cannot override library functions:");
    	else
            symTab_insert(name, alpha_yylineno, variable, formal,var_s, curr_scopespace(), curr_scope_offset());
    }
    else if(!symTab_lookup(name, get_current_scope()))
        symTab_insert(name, alpha_yylineno, variable, local, var_s, curr_scopespace(), curr_scope_offset());
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
    _emit(_funcstart, lvalue_expr(function), NULL, NULL);
    increase_scope();
    isFormal = true;
    scope_offset_stack.push(curr_scope_offset());
    enter_scopespace();
    reset_formal_arg_offset();
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
    _emit(_funcend,lvalue_expr(funcPrefix),NULL,NULL);
    assert(funcPrefix);
    return funcPrefix;  
}

expr* manage_member_item_lvalue_period_id(expr* lv, char* name) {
    lv = emit_if_table_item(lv);
    expr* ti = new_expr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = new_expr_const_string(name);
    return ti;
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
    if(lv->type = tableitem_e){
        _emit(_tablesetelem,lv,lv->index,_expr);
        assignExpr = emit_if_table_item(lv);
        assignExpr->type = assignexpr_e;
    }
    else {
        _emit(_assign, _expr, NULL, lv);
        assignExpr->sym = _newtemp();
        _emit(_assign, lv, NULL, assignExpr);
    }
    return assignExpr;
}

call* manage_methodcall(expr* elist, char* name){
    assert(elist); assert(name);
    call* methodCall = (call*)malloc(sizeof(call));
    methodCall->elist = elist;
    methodCall->method = 1;
    methodCall->name = strdup(name);
    return methodCall;  
}

expr* manage_call_funcdef(SymtabEntry* funcdef ,expr* elist){
    assert(funcdef); assert(elist);
    expr* call;
    expr* func = new_expr(programfunc_e);
    func->sym = funcdef;
    call = make_call(func, elist);
    return call;
}

expr* manage_call_lvalue_callsuffix(expr* lv, call* callsuffix) {
    assert(lv); assert(callsuffix);
    if(!(lv->sym == NULL)) lv->sym->uniontype = variable;


    lv = emit_if_table_item(lv);
    lv = emit_if_table_item(lv);
    if (callsuffix->method == 1){
        callsuffix->elist->next = lv;
        // get_last($callsuffix.elist)->next = lv; me
        lv = emit_if_table_item(manage_member_item_lvalue_period_id(lv, callsuffix->name));
    }
    return make_call(lv, callsuffix->elist);
}

call* manage_normcall(expr* elist){
    assert(elist);
    call* normcall = (call*)malloc(sizeof(call));
    normcall->elist = elist;
    normcall->method = 0;
    normcall->name = NULL;
    return normcall;
}


/*
    TODO: Lecture 10
    -Method call : fix make_call at icode.cpp
    -Make table
    -(funcdef)()
    -terms
    -reuse temps
*/



void init_library_func(){
    symTab_insert((char*)"print" , 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"input" ,0 , function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"objectmemberkeys", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"objectotalmembers",0 , function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"objectcopy", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"totalarguments", 0, function, libfunc, libraryfunc_s,curr_scopespace(), 0);
    symTab_insert((char*)"argument", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"typeof", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"strtonum", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"sqrt", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"cos", 0, function, libfunc, libraryfunc_s, curr_scopespace(), 0);
    symTab_insert((char*)"sin", 0, function,libfunc, libraryfunc_s, curr_scopespace(), 0);
}