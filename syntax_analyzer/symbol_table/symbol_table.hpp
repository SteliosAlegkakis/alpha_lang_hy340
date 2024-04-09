#include <map>
#include <list>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define GLOBAL_SCOPE 0

typedef struct Variable {

    unsigned int scope;
    char* name;
    unsigned int line;

    Variable(unsigned int _scope, char* _name, unsigned int _line) {
        scope = _scope;
        line = _line;
        name = strdup(_name);
    }

} Variable;

typedef struct Function {

    char* name;
    unsigned int scope;
    std::list<Variable*> args;
    unsigned int line;

    Function(unsigned int _scope, char* _name, unsigned int _line) {
        scope = _scope;
        line = _line;
        name = strdup(_name);
    }

} Function;

enum symbolType { global, local, formal, userfunc, libfunc };

enum unionType { variable, function };

typedef struct SymtabEntry {

    bool isActive;

    enum unionType uniontype;

    union symbol{
        Function* function;
        Variable* variable;
    } symbol;

    enum symbolType symboltype;

    SymtabEntry(unsigned int _scope, char* _name, unsigned int _line, enum unionType _uniontype, enum symbolType _symboltype) {
        isActive = true;
        uniontype = _uniontype;
        symboltype = _symboltype;
        if(uniontype == variable) 
            symbol.variable = new Variable(_scope, _name, _line);
        if(uniontype == function)
            symbol.function = new Function(_scope, _name, _line);
    }

} SymtabEntry;

const char* symbolType_toString(int symbolType);

const char* unionType_toString(int union_type);

//inserts an entry with the given arguments to the symbolTable
void symTab_insert(char* name, unsigned int line, enum unionType uniontype, enum symbolType symboltype);

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

//puts all the library functions in the symbol table
void init_library_func();