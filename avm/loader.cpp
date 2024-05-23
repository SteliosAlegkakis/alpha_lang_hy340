#include <vector>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "avm_structs.hpp"

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
    std::vector<double> numbers(size);
    in.read(reinterpret_cast<char*>(numbers.data()), size * sizeof(double));

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<std::string> strings;
    strings.clear();
    for (size_t i = 0; i < size; ++i) {
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        std::vector<char> buffer(length);
        in.read(buffer.data(), length);
        strings.emplace_back(buffer.data(), length);
    }

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<std::string> libFuncs(size);
    libFuncs.clear();
    for (size_t i = 0; i < size; ++i) {
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        std::vector<char> buffer(length);
        in.read(buffer.data(), length);
        libFuncs.emplace_back(buffer.data(), length);
    }

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<unsigned int> addresses(size);
    std::vector<unsigned int> locals(size);
    std::vector<std::string> names(size);
    in.read(reinterpret_cast<char*>(addresses.data()), size * sizeof(unsigned int));
    in.read(reinterpret_cast<char*>(locals.data()), size * sizeof(unsigned int));
    names.clear();
    for (size_t i = 0; i < size; ++i) {
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        std::vector<char> buffer(length);
        in.read(buffer.data(), length);
        names.emplace_back(buffer.data(), length);
    }

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<vmopcode> opcodes(size);
    std::vector<vmarg> results(size);
    std::vector<vmarg> arg1s(size);
    std::vector<vmarg> arg2s(size);
    std::vector<unsigned> srcLines(size);
    in.read(reinterpret_cast<char*>(opcodes.data()), size * sizeof(vmopcode));
    in.read(reinterpret_cast<char*>(results.data()), size * sizeof(vmarg));
    in.read(reinterpret_cast<char*>(arg1s.data()), size * sizeof(vmarg));
    in.read(reinterpret_cast<char*>(arg2s.data()), size * sizeof(vmarg));
    in.read(reinterpret_cast<char*>(srcLines.data()), size * sizeof(unsigned));

    in.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }
    load_binary(argv[1]);
    return 0;
}