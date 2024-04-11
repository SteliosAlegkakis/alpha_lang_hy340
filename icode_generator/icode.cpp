#include "icode.hpp"

unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;
quad*    quads = (quad*) 0;
unsigned total = 0;
unsigned int currQuad = 0;
int tmpcounter = 0;

extern int alpha_yylineno;

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

void _emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line) {
    
    if(currQuad == total) 
        _expand();
    
    quad* newQuad = quads + currQuad++;
    newQuad->op = op;
    newQuad->arg1 = arg1;
    newQuad->arg2 = arg2;
    newQuad->result = result;
    newQuad->label = label;
    newQuad->line = line;
}

scopespace_t curr_scopespace(void) {
    if(scopeSpaceCounter == 1) return programvar;
    else if(scopeSpaceCounter % 2 == 0) return formalarg;
    else return functionlocal;
}

unsigned curr_scope_offset(void) {
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
        return new SymtabEntry(get_current_scope(), name, alpha_yylineno, variable, temporary);
    return sym;
}
