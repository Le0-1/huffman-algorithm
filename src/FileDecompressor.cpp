#include "FileDecompressor.hpp"


unsigned long long FileDecompressor::GetRemainingBytes(std::ifstream& file) {
    //Pega a posição que estamos na leitura do arquivo
    unsigned long long current_position = file.tellg();

    //Move o ponteiro de leitura para o final
    file.seekg(0, std::ios::end);

    //Pega a posição final do arquivo de leitura
    unsigned long long end_position = file.tellg();

    //Move de volta para a posição que estava
    file.seekg(current_position);

    //Calcula os bytes que sobram para leitura do arquivo.
    unsigned long long remaining_bytes = end_position - current_position;
    return remaining_bytes;
}

void FileDecompressor::RebuildTree(std::ifstream& file, HuffmanTree& tree) {
    //Primeiro devemos converter os bytes armazenados nos 3 primeiros bytes para um
    //inteiro para saber qual o tamanho que a árvore ocupa no cabeçalho, tirando esses
    //3 primeiros bytes.
    unsigned char first_3bytes[3];
    file.read(reinterpret_cast<char*>(&first_3bytes), 3);

    int header_size = static_cast<int>(first_3bytes[0]) + 
                      static_cast<int>(first_3bytes[1]) + 
                      static_cast<int>(first_3bytes[2]);

    //Cria um vetor com booleanos para representar o código em bits da árvore
    unsigned array_size = header_size * BYTE_SIZE_DECOMPRESSOR;
    bool array_of_bits[array_size];

    //Cria um array de char para ler todos os bytes que representam a árvore.
    //Tem que lembrar que o 4°byte é reservado, então pulamos para o próximo byte.
    file.seekg(4);
    unsigned char tree_bytes[header_size];
    file.read(reinterpret_cast<char*>(tree_bytes), header_size);


    //Converte todos os bytes que representam a árvore para uma string que concatena tudo.
    std::string tree_bytes_in_string = "";
    for (int i = 0; i < header_size; i++) {
        std::bitset<BYTE_SIZE_DECOMPRESSOR> byte(tree_bytes[i]);
        tree_bytes_in_string+= byte.to_string();
    }

    for (unsigned i = 0; i < tree_bytes_in_string.size(); i++) {
        tree_bytes_in_string[i] == '0' ? array_of_bits[i] = 0 : array_of_bits[i] = 1;  
    }

    //Cria a variável index para passar para a função recursiva de reconstruir a árvore.
    unsigned index = 0;
    //Reconstrói a árvore pela raiz
    tree.m_Root = RebuildTree(file, array_of_bits, index, array_size);
}


Cell* FileDecompressor::RebuildTree(std::ifstream& file, bool arr[], unsigned& index, unsigned& size) {
    if (arr[index] == 0) {
        unsigned char internal_node_char = '+';
        Cell* internal_node = new Cell(internal_node_char);
        index++;
        internal_node->m_Left = RebuildTree(file, arr, index, size);
        internal_node->m_Right = RebuildTree(file, arr, index, size);
        return internal_node;
    }
    else {
        index++;
        std::string string_aux = "";
        for (int i = 0; i < BYTE_SIZE_DECOMPRESSOR; i++) {
            arr[index + i] == 0 ?  string_aux+='0' : string_aux+='1';
        }
        std::bitset<BYTE_SIZE_DECOMPRESSOR> char_bits(string_aux);
        unsigned char character = char_bits.to_ulong();
        Cell* leaf_node = new Cell(character);
        index+= BYTE_SIZE_DECOMPRESSOR;
        if (index >= size) {
            return nullptr;
        }
        return leaf_node;
    }
}

void FileDecompressor::DecodeFile(std::ofstream& output_file, Cell* node, std::ifstream& file, std::string& buffer, Cell* original_root) {

    //Essa parte é necessária para pegar quantos zeros foram colocados no final do arquivo
    //Para isso tenho que salvar a posição atual e mover o ponteiro para o quarto byte, nesse caso, o índice é 3.
    std::streampos current_position = file.tellg();
    file.seekg(3);
    int fourth_byte_zeros = 0;
    file.read(reinterpret_cast<char*>(&fourth_byte_zeros), 1);
    int zero_count = fourth_byte_zeros;

    //Retorna para a posição em que se começa a ler o arquivo em si, ou seja, logo
    //após as informações em bytes da árvore.
    file.seekg(current_position);

    unsigned long long remaining_bytes = FileDecompressor::GetRemainingBytes(file);

    for (unsigned long long i = 0; i < remaining_bytes; i++) {
        unsigned char bits;
        file.read(reinterpret_cast<char*>(&bits), 1);
        std::bitset<BYTE_SIZE_DECOMPRESSOR> byte(bits);
        std::string byte_string = byte.to_string();

        for (int j = 0; j < BYTE_SIZE_DECOMPRESSOR; j++) {
            char bit = byte_string[j];
            bit == '0' ? node = node->m_Left : node = node->m_Right;

            if ((i == remaining_bytes - 1) && (j == (BYTE_SIZE_DECOMPRESSOR - zero_count))) {
                break;
            }
            if (node->m_Left == nullptr && node->m_Right == nullptr && node != nullptr) {
                //Tenho que parar quando eu souber que começou os zeros a mais no último byte.
                output_file.write(reinterpret_cast<char*>(&node->m_Char), 1);
                node = original_root;
            }
        }
    }
}

void FileDecompressor::Decompress(std::ifstream& file, std::ofstream& output_file, HuffmanTree& tree) {
    FileDecompressor::RebuildTree(file, tree);
    Cell* original_root = tree.m_Root;
    std::string buffer = "";
    FileDecompressor::DecodeFile(output_file, tree.m_Root, file, buffer, original_root);
}

void FileDecompressor::Decompress(std::string& INPUT_FILE, const std::string& OUTPUT_FILE) {
    std::ifstream file(INPUT_FILE, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Erro na Função FileDecompressor::Decompress. Arquivo: " << INPUT_FILE << " para leitura não foi aberto ou não existe\n";
        return;
    }

    std::ofstream output_file(OUTPUT_FILE);
    if(!output_file.is_open()) {
        std::cout << "Erro na Função FileDecompressor::Decompress. Arquivo: " << INPUT_FILE << " para escrita não foi aberto ou não existe\n";
        return;
    }

    HuffmanTree tree;

    FileDecompressor::Decompress(file, output_file, tree);

    file.close();
    output_file.close();
}
