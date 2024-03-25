#include "symbol_table.hpp"

void symTab_insert(char* name, unsigned int line, enum unionType uniontype, enum symbolType symboltype) {
    SymtabEntry* entry = new SymtabEntry(currentScope, name, line, uniontype, symboltype);
    symbolTable.insert({name,entry});
}

SymtabEntry* symTab_lookup(char* name) {
    auto entrys = symbolTable.equal_range(name);
    return entrys.first->second;
}

SymtabEntry* symTab_lookup(char* name, unsigned int scope) {

    auto entrys = symbolTable.equal_range(name);

    for(auto entry = entrys.first; entry != entrys.second; ++entry){

        if(entry->second->uniontype == function) 
            if(entry->second->symbol.function->scope == scope)
                return entry->second;
        
        if(entry->second->uniontype == variable) 
            if(entry->second->symbol.variable->scope == scope)
                return entry->second;

    }

    return NULL;
}

void symTab_hide() {
    for(const auto& entry : symbolTable) {
        if(entry.second->uniontype == variable) 
            if(entry.second->symbol.variable->scope == currentScope)
                entry.second->isActive = false;
        else{
            if(entry.second->symbol.function->scope == currentScope)
                entry.second->isActive = false;
        }
    }
}

void symTab_print() {
    for(const auto& entry : symbolTable) {
        if(entry.second->uniontype == function) {
            printf("name: %s isActive: %d scope: %d line: %d symbolType: %d\n",entry.second->symbol.function->name,entry.second->isActive,entry.second->symbol.function->scope,entry.second->symbol.function->line,entry.second->symboltype);
        }
        else {
            printf("name: %s isActive: %d scope: %d line: %d symbolType: %d\n",entry.second->symbol.variable->name,entry.second->isActive,entry.second->symbol.variable->scope,entry.second->symbol.variable->line,entry.second->symboltype);
        }
    }
}
