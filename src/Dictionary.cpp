#include "Dictionary.hpp"

Dictionary::Dictionary() {
    this->m_Dictionary = new char*[DICTIONARY_LINES];
}

Dictionary::~Dictionary() {
    this->Clear();
}

void Dictionary::AllocateMemoryForDictionary(int& number_of_collums) {
    for (int i = 0; i < DICTIONARY_LINES; i++) {
        m_Dictionary[i] = new char[number_of_collums + 1];

        //'memset' preenche os espaços de memória com um caractere nulo, o zero. ASCII 0 = '\0'
        std::memset(m_Dictionary[i], 0, number_of_collums + 1);
    }
}

void Dictionary::BuildDictionary(int& number_of_collums, HuffmanTree* tree) {
    AllocateMemoryForDictionary(number_of_collums);
    std::string chr = "";

    BuildDictionary(chr, tree->m_Root, number_of_collums);
}

void Dictionary::BuildDictionary(std::string path, Cell* root, int& number_of_collums) {
    std::string left, right;

    if (root->m_Left == nullptr && root->m_Right == nullptr) {
        std::strcpy(m_Dictionary[root->m_Char], path.c_str());
    }
    else {
        left = path + "0";
        right = path + "1";

        BuildDictionary(left, root->m_Left, number_of_collums);
        BuildDictionary(right, root->m_Right, number_of_collums);
    }
}

void Dictionary::PrintDictionary() {
    for (int i = 0; i < DICTIONARY_LINES; i++) {
        if (strlen(this->m_Dictionary[i]) > 0) {
            std::cout << static_cast<unsigned char>(i) << ": "<< this->m_Dictionary[i] << '\n';
        }
    }
}

void Dictionary::Clear() {
    for (int i = 0; i < DICTIONARY_LINES; i++) {
        delete[] this->m_Dictionary[i];
    }
    delete[] this->m_Dictionary;
}