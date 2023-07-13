#ifndef CELL_H
#define CELL_H


class Cell {
    private:
        Cell* m_Prox;
        Cell* m_Left;
        Cell* m_Right;
        unsigned char m_Char;
        int m_Freq;
    public:
        Cell();
        Cell(unsigned char& chr);

    friend class LinkedList;
    friend class Hashtable;
    friend class HuffmanTree;
    friend class Dictionary;
    friend class Parser;
    friend class FileCompressor;
    friend class FileDecompressor;
};


#endif // !CELL_H