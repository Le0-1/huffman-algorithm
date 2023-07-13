#ifndef DICTIONARY_H
#define DICTIONARY_H


#include <string.h>
#include <cstring>

const int DICTIONARY_LINES = 256;

#include "HuffmanTree.hpp"


class Dictionary {
    public:
        char** m_Dictionary;

        void AllocateMemoryForDictionary(int& number_of_collums);
        void BuildDictionary(std::string path, Cell* root, int& number_of_collums);
    
    public:
        Dictionary();
        ~Dictionary();
        void BuildDictionary(int& number_of_collums, HuffmanTree* tree);
        void PrintDictionary();
        void Clear();

    friend class Parser;
};

#endif // !DICTIONARY_H
