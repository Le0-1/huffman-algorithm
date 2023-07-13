#include "Cell.hpp"

Cell::Cell() {
    this->m_Freq = 0;
    this->m_Prox = nullptr;
    this->m_Left = nullptr;
    this->m_Right = nullptr;
}

Cell::Cell(unsigned char& chr) {
    this->m_Char = chr;
    this->m_Freq = 0;
    this->m_Prox = nullptr;
    this->m_Left = nullptr;
    this->m_Right = nullptr;
}