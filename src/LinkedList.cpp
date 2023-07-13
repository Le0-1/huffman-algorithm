#include "LinkedList.hpp"

LinkedList::LinkedList() {
    this->m_First = new Cell;
    this->m_Last = this->m_First;
    this->m_Size = 0; 
}

void LinkedList::Destructor() {
    this->Clear();
    delete this->m_First;
}

Cell* LinkedList::RemoveAtBeginning() {
    Cell* aux = nullptr;
    if (this->m_Size == 0) {
        return aux;
    }
    aux = this->m_First->m_Prox;
    this->m_First->m_Prox = aux->m_Prox;
    this->m_Size--;
    if (this->m_First->m_Prox == nullptr) {
        this->m_Last = this->m_First;
    }
    return aux;
}

void LinkedList::Clear() {

    if (this->m_Size == 0) {
        return;
    }

    Cell* aux;
    aux = this->m_First->m_Prox;

    while (aux != nullptr) {
        this->m_First->m_Prox = this->m_First->m_Prox->m_Prox;
        delete aux;
        aux = this->m_First->m_Prox;
    }
    
    this->m_Last = this->m_First;
    this->m_Size = 0;
}

Cell* LinkedList::FindCellWithCharacter(unsigned char& chr) {
    Cell* p;
    p = this->m_First->m_Prox;

    while (p != nullptr) {
        if (p->m_Char == chr) {
            return p;
        }
        p = p->m_Prox;
    }
    return nullptr;
}

void LinkedList::PrintElements() {

    if (this->m_Size == 0) {
        return;
    }

    Cell* p;

    p = this->m_First->m_Prox;

    while (p != nullptr) {
        std::cout << p->m_Char << "|" << p->m_Freq << '\n';
        p = p->m_Prox;
    }
    p = nullptr;
    delete p;
}

void LinkedList::OrderedInsert(Cell* node) {
    Cell* aux;

    if (this->m_Size == 0 || node->m_Freq < this->m_First->m_Prox->m_Freq) {
        node->m_Prox = this->m_First->m_Prox;
        this->m_First->m_Prox = node;
        if (node->m_Prox == nullptr) {
            this->m_Last = node;
        }
    }

    else if (node->m_Freq > this->m_Last->m_Freq) {
        this->m_Last->m_Prox = node;
        this->m_Last = node;
    }
    else {
        aux = this->m_First;
        while (aux->m_Prox != nullptr && aux->m_Prox->m_Freq < node->m_Freq) {
            aux = aux->m_Prox;
        }
        node->m_Prox = aux->m_Prox;
        aux->m_Prox = node;
    }
    this->m_Size++;
}

bool LinkedList::IsEmpty() {
    if (this->m_Size == 0) return true;
    else return false;
}