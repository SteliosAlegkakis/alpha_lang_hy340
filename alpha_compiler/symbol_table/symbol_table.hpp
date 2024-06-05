#include <map>
#include <list>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define GLOBAL_SCOPE 0

enum scopespace_t { programvar, functionlocal, formalarg };

enum symbol_t { var_s, programfunc_s, libraryfunc_s };

enum symbolType { global, local, formal, userfunc, libfunc };

enum unionType { variable, function };

typedef struct Variable {

    unsigned int scope;
    char*        name;
    unsigned int line;
    scopespace_t space;
    unsigned int offset;

    Variable(unsigned int _scope, char* _name, unsigned int _line, scopespace_t _space, unsigned int _offset) {
        scope = _scope;
        line = _line;
        name = strdup(_name);
        space = _space;
        offset = _offset;
    }

} Variable;

typedef struct Function {

    char* name;
    unsigned int scope;
    std::list<Variable*> args;
    unsigned int line;
    unsigned int iaddress;
    unsigned int taddress;
    unsigned int totalLocals;
    std::list<unsigned int> returnList;

    Function(unsigned int _scope, char* _name, unsigned int _line) {
        scope = _scope;
        line = _line;
        name = strdup(_name);
    }

} Function;

typedef struct SymtabEntry {

    bool isActive;
    
    enum unionType uniontype;

    union symbol{
        Function* function;
        Variable* variable;
    } symbol;

    enum symbolType symboltype;
    enum symbol_t   symbol_t;

    SymtabEntry(unsigned int _scope, char* _name, unsigned int _line, enum unionType _uniontype, enum symbolType _symboltype,enum symbol_t _symbol_t, scopespace_t _space, unsigned int _offset) {
        isActive = true;
        uniontype = _uniontype;
        symboltype = _symboltype;
        symbol_t = _symbol_t;
        if(uniontype == variable) 
            symbol.variable = new Variable(_scope, _name, _line, _space, _offset);
        if(uniontype == function)
            symbol.function = new Function(_scope, _name, _line);
    }

} SymtabEntry;

const char* symbolType_toString(int symbolType);

const char* unionType_toString(int union_type);

//inserts an entry with the given arguments to the symbolTable
void symTab_insert(char* name, unsigned int line, enum unionType uniontype, enum symbolType symboltype,enum symbol_t symbol_t, scopespace_t space, unsigned int offset );

//checks if a symbol with the given name exists in the symbolTable
//returns the first entry with given name if it exists, else returns NULL
SymtabEntry* symTab_lookup(char*name);

//checks if a symbol with the given name exists in the given scope in the symbolTable. 
//returns the entry if it exists, else returns NULL
SymtabEntry* symTab_lookup(char* name, unsigned int scope);

SymtabEntry* symTab_lookup_infunc(char* name);

//prints all the elements in the symbol table
void symTab_print();

//Hides all the symbols in the currentScope
void symTab_hide();

//increases the current scope
void increase_scope();

//decreases the current scope
void decrease_scope();

//returns current scope
unsigned int get_current_scope();