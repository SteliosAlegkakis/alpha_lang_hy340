#include "symbol_table.hpp"
#include <string>
#include <iostream>

using namespace std;

void symTab_insert(char* id, SymtabEntry entry) {
    if(entry.type == variable) {
        entry.symbol.variable->id = id ;
        entry.symbol.variable->scope = current_scope;
    }
    else {
        entry.symbol.function->id = id ;
        entry.symbol.function->scope = current_scope;
    }
    symbolTable[id] = entry;
}

int symTab_lookup(char* id, int scope) {
    return symbolTable.find(id) != symbolTable.end();
}

void symTab_hide(int scope) {}
   

int main() {
    char* id = "x";
    SymtabEntry entry1;
    entry1.type = variable;
    Variable var = { current_scope, id, global, 1};
    // entry1.symbol.variable = &var;
    entry1.symbol.variable = &var;
    symTab_insert(id, entry1);

    printf("%d\n",symTab_lookup(id,1));
}


/*namespace std {
    template<>
    struct hash<SymTabKey> {
        std::size_t operator()(const SymTabKey& k) const {
            return hash<std::string>()(k.id) ^ hash<int>()(k.scope);
        }
    };
}*/
