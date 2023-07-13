#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>

#include "LinkedList.hpp"

const int NUMBER_OF_CHARACTERS = 128;

class Hashtable {
    private:
        unsigned long long m_Table[NUMBER_OF_CHARACTERS];
    public:
        Hashtable();
        void InsertCharacter(const unsigned char& chr);
        LinkedList ReturnOrderedList();
        void PrintTable();
};

#endif