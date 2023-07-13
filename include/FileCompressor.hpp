#ifndef FILECOMPRESSOR_H
#define FILECOMPRESSOR_H

#include "Dictionary.hpp"
#include "Hashtable.hpp"
#include "HuffmanTree.hpp"
#include "Cell.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <bitset>

const int BYTE_SIZE_COMPRESSOR = 8;

class FileCompressor {
    private:

    /**
     * @brief Função que passa o que está no buffer para o arquivo
     * @param file : Arquivo de escrita | Buffer : string do buffer
    */
    static void WriteBufferInFile(std::ofstream& file, std::string& buffer);

    /**
     * @brief Função que esvazia o que sobrou do buffer.
     * @details Ela esvazia o buffer depois de terminar a escrita no arquivo binário e 
     * pega um inteiro por referência para atualizar ele em relação a quantos zeros a mais
     * foram escritos no byte final do arquivo binário.
     * @return void
    */
    static void EmptyBufferWithZeroCount(std::ofstream& file, std::string& buffer, int& zero_count);

    /**
     * @brief Função que esvazia o buffer mas agora com o parâmetro header_size de tamanho do cabeçalho.
     * @details Essa função difere da outra pois essa visa escrever no arquivo binário,
     *  nos 3 primeiros bytes, o tamanho de bytes que o cabeçalho usou.
     *  Por isso passo um inteiro que fala o tamanho do cabeçalho.
    */
    static void EmptyBufferWithHeader(std::ofstream& file, std::string& buffer, int& header_size);


    /**
     * @brief Função que lê o arquivo e cria a árvore de huffman, o dicionário 
     * e preenche a tabela hash.
     * @return void
    */
    static void ReadFromFile(const std::string& FILENAME, Hashtable& table, HuffmanTree& tree, 
        Dictionary& dictionary);

    /**
     * @brief Função que escreve as informações da árvore no arquivo binário.
     * @details Também escreve 3 bytes no "cabeçalho do arquivo" para dizer quantos
     * bytes o cabeçalho tem.
     * @return void
     * @related WriteTreeInFileRecursive
    */
    static void WriteTreeInFile(std::ofstream& file, Cell* root);

    /**
     * @brief Função que escreve recursivamente as informações da árvore no arquivo. 
    */
    static void WriteTreeInFileRecursive(std::ofstream& FILENAME, Cell* root, std::string& 
        buffer, int& header_size);

    FileCompressor() = delete;
    public:

    /**
     * @brief Função que irá comprimir um arquivo txt
     * @param 1: Nome do arquivo a ser comprimido.
     * @return arquivo binário com os dados da compressão
    */
    static void Compress(const std::string& INPUT_FILE, const std::string& OUTPUT_FILE);
    

    
};


#endif //!FILECOMPRESSOR_H