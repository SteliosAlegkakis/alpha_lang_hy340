#include "symbol_table.hpp"

unsigned int currentScope = 0;
std::multimap<const char*, SymtabEntry*> symbolTable;

bool lookup_check(const char* name){
    auto entries = symbolTable.equal_range(name);
    if(entries.first == entries.second){
        std::cerr<<"Error: Undefined symbol '"<< name << "'." << std::endl;
        return false;
    }
    return true;
}


void symTab_insert(char* name, unsigned int line, enum unionType uniontype, enum symbolType symboltype) {
    if(!check_insert(name,currentScope,uniontype)){
        return;
    }
    SymtabEntry* entry = new SymtabEntry(currentScope, name, line, uniontype, symboltype);
    symbolTable.insert({name,entry});
}

SymtabEntry* symTab_lookup(char* name) {
    auto entrys = symbolTable.equal_range(name);
    if(!lookup_check(name)){
        return nullptr;
    }
    for(auto&entry = entrys.first; entry != entrys.second; ++entry) {
        if(entry->second->isActive) return entry->second;
    }
    return NULL;
}

SymtabEntry* symTab_lookup(char* name, unsigned int scope) {

    auto entrys = symbolTable.equal_range(name);

    for(auto entry = entrys.first; entry != entrys.second; ++entry){

        if(entry->second->uniontype == function && entry->second->isActive) 
            if(entry->second->symbol.function->scope == scope)
                return entry->second;
        
        if(entry->second->uniontype == variable && entry->second->isActive) 
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

void increase_scope() { currentScope++; }

void decrease_scope() { currentScope--; }

unsigned int get_current_scope() { return currentScope; }

void library_func(char* name ,symbolType lib_func, unsigned int line){
    symTab_insert(name,line,function,lib_func);
}

void init_library_func(){
    library_func("print",libfunc,0);
    library_func("input", libfunc,0);
    library_func("objectmemberkeys",libfunc,0);
    library_func("objecttotalmembers",libfunc,0);
    library_func("objectcopy",libfunc,0);
    library_func("totalarguments",libfunc,0);
    library_func("argument",libfunc,0);
    library_func("typeof", libfunc,0);
    library_func("strtonum",libfunc,0);
    library_func("sqrt",libfunc,0);
    library_func("cos",libfunc,0);
    library_func("sin",libfunc,0);
}

bool check_insert(char* name,unsigned int scope, enum unionType uni_type){
    auto entries = symbolTable.equal_range(name);
    for(auto entry = entries.first; entry != entries.second; ++entry){
        if(entry->second->symbol.function->scope == scope ||
           entry->second->symbol.function->scope == scope){
            std::cerr << "Error: Symbol ' "<< name << " ' redifinition in the same scope."<<std::endl;
            return false;
           }
    }
    return true;
}

int main(){return 0;}