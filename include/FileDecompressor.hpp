#ifndef FILEDECOMPRESSOR_H
#define FILEDECOMPRESSOR_H

#include "Hashtable.hpp"
#include "HuffmanTree.hpp"
#include "Dictionary.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <bitset>

const int BYTE_SIZE_DECOMPRESSOR = 8;

class FileDecompressor {
    private:
    /**
     * @brief Função que mostra quantos bytes ainda faltam para terminar de ler o
     * arquivo a partir da posição atual de leitura
     * @param 1: arquivo para leitura
     * @return Retorna um inteiro dizendo quantos bytes ainda faltam para terminar
     * de ler o arquivo.
    */
    static unsigned long long GetRemainingBytes(std::ifstream& file);

    /**
     * @brief Função que reconstrói uma árvore a partir das informações de um arquivo
     * binário que foi compactado pelo programa.
     * @param 1: Arquivo de Leitura | 2: Árvore de ruffman vazia
     * @related RebuildTree com mais parâmetros
    */
    static void RebuildTree(std::ifstream& file, HuffmanTree& tree);

    /**
     * @brief Função chamada pela RebuildTree para reconstruir a árvore de forma recursiva
     * @param 1: Arquivo para leitura
     * @param 2: Array de booleanos que representa os bytes da árvore contida no cabeçalho.
     * @param 3: Passar o index por referência para iterar sobre o array de booleanos
     * @param 4: Tamanho do array para saber quando sair da função
    */
    static Cell* RebuildTree(std::ifstream& file, bool arr[], unsigned& index, unsigned& size);

    /**
     * @brief Função que visa decodificar um arquivo binário dado como entrada que
     * foi codificado por esse programa.
     * @param 1: arquivo de saída para escrever o texto decodificado
     * @param 2: raiz da árvore que foi reconstruída
     * @param 3: arquivo binário de leitura
     * @param 4: buffer para escrever no arquivo
     * @param 5: quando escrevermos um caractere no arquivo temos que voltar para a raiz da árvore e
     * percorrer novamente.
    */
    static void DecodeFile(std::ofstream& output_file, Cell* root, std::ifstream& file, std::string& buffer, Cell* original_root);

    /**
     * @brief Apenas uma função intermediária usada para não precisar passar uma árvore
     * de huffman no main.
     * @param 1: Arquivo binário de leitura
     * @param 2: Arquivo texto de escrita
     * @param 3: Árvore reconstruída
    */
    static void Decompress(std::ifstream& file, std::ofstream& output_file, HuffmanTree& tree);

    FileDecompressor() = delete;
    public:
    
    /**
     * @brief Função que descompacta o arquivo.
     * @related: Decompress com mais 1 parâmetro.
     * @param 1: Nome do arquivo que quero descompactar
    */
    static void Decompress(std::string& INPUT_FILE, const std::string& OUTPUT_FILE);
};


#endif // !FILEDECOMPRESSOR_H