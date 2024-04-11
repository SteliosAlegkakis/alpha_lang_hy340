#include "symbol_table.hpp"
#include <cassert>

struct CharPtrComparator {
    bool operator()(const char* lhs, const char* rhs) const {
        return strcmp(lhs, rhs) < 0;
    }
};

unsigned int currentScope = 0;
std::multimap<const char*, SymtabEntry*, CharPtrComparator> symbolTable;

const char* symbolType_toString(int symbolType) {
    if(symbolType == 0) return "global variable";
    else if(symbolType == 1) return "local variable";
    else if(symbolType == 2) return "formal argument";
    else if(symbolType == 3) return "user function";
    else if(symbolType == 4) return "library function";
    else if(symbolType == 5) return "temporary variable";
    exit(EXIT_FAILURE);
}

const char* unionType_toString(int union_type) {
    if(union_type == 0) return "variable";
    else if(union_type == 1)return "function";
    exit(EXIT_FAILURE);
}

void symTab_insert(char* name, unsigned int line, enum unionType uniontype, enum symbolType symboltype) {
    if(uniontype == variable) {
        if(currentScope == 0) symboltype = global;
    }
    SymtabEntry* entry = new SymtabEntry(currentScope, name, line, uniontype, symboltype);
    symbolTable.insert({name,entry});
    printf("name: '%s' line: %d scope: %d symbol type: '%s'\n", name, line, currentScope, symbolType_toString(symboltype));
}

SymtabEntry* symTab_lookup(char* name) {
    auto entrys = symbolTable.equal_range(name);
    for(auto entry = entrys.first; entry != entrys.second; ++entry) {
        if(entry->second->isActive) return entry->second;
    }
    return NULL;
}

SymtabEntry* symTab_lookup(char* name, unsigned int scope) {

    auto entrys = symbolTable.equal_range(name);
    // assert(entrys.first != symbolTable.end() && entrys.second != symbolTable.end());
    for(auto entry = entrys.first; entry != entrys.second; ++entry){

        if(entry->second->uniontype == function && entry->second->isActive) { 
            if(entry->second->symbol.function->scope == scope)
                return entry->second;
        }
        
        if(entry->second->uniontype == variable && entry->second->isActive){
            if(entry->second->symbol.variable->scope == scope) {
                return entry->second;
            }
        }

    }

    return NULL;
}

SymtabEntry* symTab_lookup_infunc(char* name) {
    SymtabEntry* result = nullptr;
    for(int scope = currentScope - 1; scope > 0; scope--) {
        if(result = symTab_lookup(name, scope)) 
            return result;
    }
    return result;
}

void symTab_hide() {
    if(currentScope == 0) return;
    for(auto& entry : symbolTable) {
        if(entry.second->uniontype == variable) 
            if(entry.second->symbol.variable->scope == currentScope)
                entry.second->isActive = false;
        else{
            if(entry.second->symbol.function->scope == currentScope)
                entry.second->isActive = false;
        }
    }
}

void increase_scope() { currentScope++; }

void decrease_scope() { currentScope--; }

unsigned int get_current_scope() { return currentScope; }

void symTab_print() {
    for(const auto& entry : symbolTable) {
        if(entry.second->uniontype == function) {
            printf("name: %s isActive: %d scope: %d line: %d symbolType: %s\n",entry.second->symbol.function->name,entry.second->isActive,entry.second->symbol.function->scope,entry.second->symbol.function->line,symbolType_toString(entry.second->symboltype));
        }
        else {
            printf("name: %s isActive: %d scope: %d line: %d symbolType: %s\n",entry.second->symbol.variable->name,entry.second->isActive,entry.second->symbol.variable->scope,entry.second->symbol.variable->line,symbolType_toString(entry.second->symboltype));
        }
    }
}

void init_library_func(){
    symTab_insert((char*)"print" , 0, function, libfunc);
    symTab_insert((char*)"input" ,0 , function, libfunc);
    symTab_insert((char*)"objectmemberkeys", 0, function, libfunc);
    symTab_insert((char*)"objectotalmembers",0 , function, libfunc);
    symTab_insert((char*)"objectcopy", 0, function, libfunc);
    symTab_insert((char*)"totalarguments", 0, function, libfunc);
    symTab_insert((char*)"argument", 0, function, libfunc);
    symTab_insert((char*)"typeof", 0, function, libfunc);
    symTab_insert((char*)"strtonum", 0, function, libfunc);
    symTab_insert((char*)"sqrt", 0, function, libfunc);
    symTab_insert((char*)"cos", 0, function, libfunc);
    symTab_insert((char*)"sin", 0, function,libfunc);
}