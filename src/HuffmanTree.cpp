#include "HuffmanTree.hpp"

HuffmanTree::HuffmanTree() {
    this->m_Root = nullptr;
}

HuffmanTree::~HuffmanTree() {
    this->Clear();
    this->m_Root = nullptr;
}

void HuffmanTree::BuildTree(LinkedList* list) {
    Cell* first;
    Cell* second;
    Cell* new_cell;
    unsigned char middle_node_char = '+';
    while (list->m_Size > 1) {
        first = list->RemoveAtBeginning();
        second = list->RemoveAtBeginning();
        new_cell = new Cell(middle_node_char);
        new_cell->m_Freq = first->m_Freq + second->m_Freq;
        new_cell->m_Left = first;
        new_cell->m_Right = second;
        new_cell->m_Prox = nullptr;
        list->OrderedInsert(new_cell);   
    }
    this->m_Root = list->m_First->m_Prox;
    delete list->m_First;
}

void HuffmanTree::PrintTree(Cell* root, int depth) {
    if (root->m_Left == nullptr && root->m_Right == nullptr) {
        std::cout << '\t' << "Folha: " << root->m_Char << "\t Altura: " << depth << '\n';
    }
    else {
        std::cout << "Esquerda\n";
        PrintTree(root->m_Left, depth + 1);
        std::cout << "Direita\n";
        PrintTree(root->m_Right, depth + 1);
    }
}

void HuffmanTree::PrintTree() {
    if (this->m_Root == nullptr) {
        std::cout << "ERROR: Empty Tree\n";
        return;
    }
    this->PrintCell(this->m_Root, "", false);
}

void HuffmanTree::PrintCell(Cell* root, const std::string& prefix, bool is_left) {
    if (root == nullptr) return;

    std::cout << prefix;
    std::cout << (is_left? "├──" : "└──");
    std::cout << root->m_Char << std::endl;
    PrintCell(root->m_Left, prefix + (is_left ? "│   " : "    "), true);
    PrintCell(root->m_Right, prefix + (is_left ? "│   " : "    "), false);
}

void HuffmanTree::Clear(Cell* root) {
    if (root != nullptr) {
        Clear(root->m_Left);
        Clear(root->m_Right);
        delete root;
    }
}

void HuffmanTree::Clear() {
    Clear(this->m_Root);
    
    this->m_Root = nullptr;
}

int HuffmanTree::TreeHeight(Cell* root) {
    int left_height = 0, right_height = 0;
    if (root == nullptr) {
        return -1;
    }
    else {
        left_height = TreeHeight(root->m_Left) + 1;
        right_height = TreeHeight(root->m_Right) + 1;
        return std::max(left_height, right_height);
    }
}

int HuffmanTree::TreeHeight() {
    return TreeHeight(this->m_Root);
}