#include <vector>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "avm_structs.hpp"

std::vector<double> numbers;
std::vector<char*> strings;
std::vector<char*> libFuncs;
std::vector<unsigned int> addresses;
std::vector<unsigned int> locals;
std::vector<char*> names;
std::vector<userfunc> userFuncs;
std::vector<instruction*> code;
std::vector<vmopcode> opcodes;
std::vector<vmarg> results;
std::vector<vmarg> arg1s;
std::vector<vmarg> arg2s;
std::vector<unsigned> srcLines;

void construct_vectors() {
    for(size_t i = 0; i < names.size(); i++) {
        userfunc userFunc;
        userFunc.address = addresses[i];
        userFunc.localSize = locals[i];
        userFunc.id = strdup(names[i]);
        userFuncs.push_back(userFunc);
    }
    for(size_t i = 0; i < opcodes.size(); i++) {
        instruction* instr;
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }
    load_binary(argv[1]);
    return 0;
}