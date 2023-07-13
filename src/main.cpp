#include "Hashtable.hpp"
#include "HuffmanTree.hpp"
#include "Dictionary.hpp"
#include "FileCompressor.hpp"
#include "FileDecompressor.hpp"

#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>

int main(int argc, char** argv) {

    std::string INPUT_FILE;
    std::string OUTPUT_FILE;

    if (argc == 4) {
        if (std::string(argv[1]) == "-c") {
            INPUT_FILE = argv[2];
            OUTPUT_FILE = argv[3];
            FileCompressor::Compress(INPUT_FILE, OUTPUT_FILE);
        }
        else if (std::string(argv[1]) == "-d") {
            INPUT_FILE = argv[2];
            OUTPUT_FILE = argv[3];
            FileDecompressor::Decompress(INPUT_FILE, OUTPUT_FILE);
        }
    }
    else {
        std::cout << "ERRO: Foram passados menos ou mais parâmetros na linha de comando\n";
    }



    return 0;
}
