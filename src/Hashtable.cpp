#include "Hashtable.hpp"

Hashtable::Hashtable() {
    for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        this->m_Table[i] = 0;
    }
}

void Hashtable::InsertCharacter(const unsigned char& chr) {
    this->m_Table[chr]++;
}

void Hashtable::PrintTable() {
    for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        if (this->m_Table[i] > 0) {
            std::cout << static_cast<unsigned char>(i) << ' ' << this->m_Table[i] << '\n';
        }
    }
}

LinkedList Hashtable::ReturnOrderedList() {
    LinkedList ordered_list;

    for (int i = 0; i < NUMBER_OF_CHARACTERS;i++) {
        if (this->m_Table[i] > 0) {
            unsigned char chr = static_cast<unsigned char>(i);
            Cell* new_cell = new Cell(chr);
            new_cell->m_Freq = this->m_Table[i];
            ordered_list.OrderedInsert(new_cell);
        }
    }
    return ordered_list;
}