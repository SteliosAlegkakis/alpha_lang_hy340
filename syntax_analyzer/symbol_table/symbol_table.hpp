#include <map>
#include <list>
#include <vector>
#include <stdio.h>

using namespace std;

int current_scope = 0;

enum variableType {global, local, functionArg};

typedef struct Variable {
    int scope;
    char* id;
    enum variableType type;
    int line;
} Variable;

enum functionType {userFunction, libraryFunction};

typedef struct Function {
    int scope;
    char* id;
    list<Variable*> args;
    enum functionType type;
    int line;
} Function;

enum symbolType { globalVar, localVar, argumentVar, userFunc, libFunc };

enum unionType { variable, function };

typedef struct SymtabEntry {

    bool isActive = true;

    enum unionType type;

    union symbol{
        Function* function;
        Variable* variable;
    } symbol;

    enum symbolType symbolType;

} SymtabEntry;

map<char*, SymtabEntry> symbolTable;

void symTab_insert(char* id, SymtabEntry value);
int symTab_lookup(char* id, int scope);
void symTab_hide(int scope);