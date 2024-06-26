#include <vector>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "avm_structs.hpp"

extern std::vector<double> numbers;
extern std::vector<char*> strings;
extern std::vector<char*> libFuncs;
extern std::vector<userfunc*> userFuncs;
extern std::vector<instruction*> code;
unsigned int totalGlobals = 0;

std::vector<unsigned int> addresses;
std::vector<unsigned int> locals;
std::vector<char*> names;
std::vector<vmopcode> opcodes;
std::vector<vmarg> results;
std::vector<vmarg> arg1s;
std::vector<vmarg> arg2s;
std::vector<unsigned> srcLines;

void construct_vectors() {
    for(size_t i = 0; i < names.size(); i++) {
        userfunc* userFunc = new userfunc;
        userFunc->address = addresses[i];
        userFunc->localSize = locals[i];
        userFunc->id = strdup(names[i]);
        userFuncs.push_back(userFunc);
    }
    for(size_t i = 0; i < opcodes.size(); i++) {
        instruction* instr = new instruction;
        instr->opcode = opcodes[i];
        instr->result = results[i];
        instr->arg1 = arg1s[i];
        instr->arg2 = arg2s[i];
        instr->srcLine = srcLines[i];
        code.push_back(instr);
    }
}

void load_binary(char* filename) {
    std::ifstream in;
    int magicNumber;
    int expectedMagicNumber = 340200501;
    in.open(filename, std::ios::binary);
    in.read(reinterpret_cast<char*>(&magicNumber), sizeof(magicNumber));
    if (magicNumber != expectedMagicNumber) {
        std::cerr << "Error: Magic number does not match." << std::endl;
        exit(EXIT_FAILURE);
    }

    in.read(reinterpret_cast<char*>(&totalGlobals), sizeof(totalGlobals));

    size_t size;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    numbers.resize(size);   
    in.read(reinterpret_cast<char*>(numbers.data()), size * sizeof(double));

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    strings.resize(size);
    strings.clear();
    for (size_t i = 0; i < size; ++i) {
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        char* buffer = new char[length+1];
        in.read(buffer, length);
        buffer[length] = '\0';
        strings.push_back(buffer);
    }

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    libFuncs.resize(size);
    libFuncs.clear();
    for (size_t i = 0; i < size; ++i) {
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        char* buffer = new char[length+1];
        in.read(buffer, length);
        buffer[length] = '\0';
        libFuncs.push_back(buffer);
    }

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    addresses.resize(size);
    locals.resize(size);
    names.resize(size);
    in.read(reinterpret_cast<char*>(addresses.data()), size * sizeof(unsigned int));
    in.read(reinterpret_cast<char*>(locals.data()), size * sizeof(unsigned int));
    names.clear();
    for (size_t i = 0; i < size; ++i) {
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        char* buffer = new char[length+1];
        in.read(buffer, length);
        buffer[length] = '\0';
        names.push_back(buffer);
    }

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    opcodes.resize(size);
    results.resize(size);
    arg1s.resize(size);
    arg2s.resize(size);
    srcLines.resize(size);
    in.read(reinterpret_cast<char*>(opcodes.data()), size * sizeof(vmopcode));
    in.read(reinterpret_cast<char*>(results.data()), size * sizeof(vmarg));
    in.read(reinterpret_cast<char*>(arg1s.data()), size * sizeof(vmarg));
    in.read(reinterpret_cast<char*>(arg2s.data()), size * sizeof(vmarg));
    in.read(reinterpret_cast<char*>(srcLines.data()), size * sizeof(unsigned));

    in.close();

    construct_vectors();
}