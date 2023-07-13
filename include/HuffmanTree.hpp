#ifndef HUFFMANTREE_H

#define HUFFMANTREE_H

#include "LinkedList.hpp"

class HuffmanTree {
    public:
        Cell* m_Root;

        void Clear(Cell* root);
        int TreeHeight(Cell* root);
        void PrintCell(Cell* root, const std::string& prefix, bool is_left);

    public:
        HuffmanTree();
        ~HuffmanTree();
        void Clear();
        int TreeHeight();
        void BuildTree(LinkedList* list);
        void PrintTree();
        void PrintTree(Cell* root, int depth);

    friend class Dictionary;

};

#endif // !HUFFMANTREE_H

