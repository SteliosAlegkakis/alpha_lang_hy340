#include "parser_lib.hpp"

FILE* rulesFile;
int anonymousCounter = 0;
int functionCounter = 0;
bool isFormal = false;
int loopCounter;
std::stack<int> loopCounterStack;
SymtabEntry* lookup_tmp;

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

SymtabEntry* manage_lvalue_id(char *name) {
	// if(functionCounter){
    //   if(symTab_lookup_infunc($1)) print_error("error, cannot acces identifier: ");
    //   else if(symTab_lookup($1, GLOBAL_SCOPE)) {
    //     lookup_tmp = symTab_lookup($1, GLOBAL_SCOPE);
    //     $$ = lookup_tmp;
	//   }
    //   else {
	//     if(!is_libfunc($1)){
    //       symTab_insert($1, alpha_yylineno, variable, local);
    //       lookup_tmp = symTab_lookup($1, get_current_scope());
    //       $$ = lookup_tmp;
    //     }
    //   }
    // }
    if(!symTab_lookup(name)) {
        symTab_insert(name, alpha_yylineno, variable, local);
        return symTab_lookup(name, get_current_scope());
    }
    else{
        return symTab_lookup(name);
    }
}

SymtabEntry* manage_lvalue_local_id(char* name) {
	if(!symTab_lookup(name, get_current_scope())){
        if(!is_libfunc(name)){
        	symTab_insert(name, alpha_yylineno, variable, local);
            return symTab_lookup(name, get_current_scope());
        }
        else {
            print_error("error, cannot overide library functions:");
			exit(EXIT_FAILURE);
		}	
    }
    else 
		return symTab_lookup(name, get_current_scope());
}

SymtabEntry* manage_lvalue_global_id(char* name) {
	if(!symTab_lookup(name, GLOBAL_SCOPE)) {
            print_error("error, could not find global identifier:");
            exit(EXIT_FAILURE);
    }
	else
        return symTab_lookup(name, GLOBAL_SCOPE);
}

void manage_idlist_id(char* name) {
	if(isFormal){
        if(symTab_lookup(name, get_current_scope()))
            print_error("error, redifinition of formal argument:");
        else if (is_libfunc(name))
            print_error("error, cannot override library functions:");
        else
            symTab_insert(name, alpha_yylineno, variable, formal);
    }
    else if(!symTab_lookup(name, get_current_scope()))
        symTab_insert(name, alpha_yylineno, variable, local);
}

void manage_idlist_comma_id(char* name) {
	if(isFormal){
        if(symTab_lookup(name, get_current_scope()))
            print_error("error, redifinition of formal argument:");
        else if (is_libfunc(name))
            print_error("error, cannot override library functions:");
    	else
            symTab_insert(name, alpha_yylineno, variable, formal);
    }
    else if(!symTab_lookup(name, get_current_scope()))
        symTab_insert(name, alpha_yylineno, variable, local);
}