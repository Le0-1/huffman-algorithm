#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Cell.hpp"

#include <iostream>

class LinkedList {
    private:
        int m_Size;
        Cell* m_First;
        Cell* m_Last;
        
        void Clear();

    public:
        LinkedList();
        void Destructor();
        Cell* RemoveAtBeginning();
        void OrderedInsert(Cell* node);
        Cell* FindCellWithCharacter(unsigned char& chr);
        void PrintElements();
        bool IsEmpty();

    friend class Hashtable;
    friend class HuffmanTree;
};

#endif // !LINKEDLIST_H
