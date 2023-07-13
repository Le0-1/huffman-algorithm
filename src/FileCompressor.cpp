#include "FileCompressor.hpp"

void FileCompressor::ReadFromFile(const std::string& FILENAME, Hashtable& table, HuffmanTree& tree, Dictionary&  dictionary) {
    std::ifstream stream(FILENAME);
    if(!stream.is_open()) {
        std::cout << "Arquivo não foi aberto!\n";
        return;
    }
    while (!stream.eof()) {
        unsigned char aux;
        stream.read(reinterpret_cast<char*>(&aux), 1);
        if (!stream.eof()) {
            table.InsertCharacter(aux);
        }
    }
    //Constrói árvore e dicionário.
    LinkedList new_list = table.ReturnOrderedList();
    tree.BuildTree(&new_list);
    int collums = tree.TreeHeight();
    dictionary.BuildDictionary(collums, &tree);
    stream.close();
}

void FileCompressor::WriteBufferInFile(std::ofstream& file, std::string& buffer) {
    std::bitset<BYTE_SIZE_COMPRESSOR> byte(buffer.substr(0, BYTE_SIZE_COMPRESSOR));
    file.write(reinterpret_cast<char*>(&byte), 1);
    buffer = buffer.substr(BYTE_SIZE_COMPRESSOR, buffer.size() - 1);
}

void FileCompressor::EmptyBufferWithHeader(std::ofstream& file, std::string& buffer, int& header_size) {
    if (buffer.size() > BYTE_SIZE_COMPRESSOR) {
        std::bitset<BYTE_SIZE_COMPRESSOR> remaining_byte(buffer.substr(0, BYTE_SIZE_COMPRESSOR));
        file.write(reinterpret_cast<char*>(&remaining_byte), 1);
        buffer = buffer.substr(BYTE_SIZE_COMPRESSOR, buffer.size() - 1);
        header_size++;
    }
    if (buffer.size() == BYTE_SIZE_COMPRESSOR) {
        std::bitset<BYTE_SIZE_COMPRESSOR> remaining_byte(buffer);
        file.write(reinterpret_cast<char*>(&remaining_byte), 1);
        buffer = "";
        header_size++;
    }
    if (buffer.size() > 0 && buffer.size() < BYTE_SIZE_COMPRESSOR) {
        while (buffer.size() < BYTE_SIZE_COMPRESSOR) {
            buffer.push_back('0');
        }
        std::bitset<BYTE_SIZE_COMPRESSOR> remaining_byte(buffer);
        file.write(reinterpret_cast<char*>(&remaining_byte), 1);
        buffer = "";
        header_size++;
    }
}

void FileCompressor::EmptyBufferWithZeroCount(std::ofstream& file, std::string& buffer, int& zero_count) {
    if (buffer.size() > BYTE_SIZE_COMPRESSOR) {
        std::bitset<BYTE_SIZE_COMPRESSOR> remaining_byte(buffer.substr(0, BYTE_SIZE_COMPRESSOR));
        file.write(reinterpret_cast<char*>(&remaining_byte), 1);
        buffer = buffer.substr(BYTE_SIZE_COMPRESSOR, buffer.size() - 1);
    }
    if (buffer.size() == BYTE_SIZE_COMPRESSOR) {
        std::bitset<BYTE_SIZE_COMPRESSOR> remaining_byte(buffer);
        file.write(reinterpret_cast<char*>(&remaining_byte), 1);
        buffer = "";
    }
    if (buffer.size() > 0 && buffer.size() < BYTE_SIZE_COMPRESSOR) {
        while (buffer.size() < BYTE_SIZE_COMPRESSOR) {
            buffer.push_back('0');
            zero_count++;
        }
        std::bitset<BYTE_SIZE_COMPRESSOR> remaining_byte(buffer);
        file.write(reinterpret_cast<char*>(&remaining_byte), 1);
        buffer = "";
    }
}


void FileCompressor::WriteTreeInFile(std::ofstream& file, Cell* root) {
    std::string buffer = "";
    int header_size = 0;

    // Ponteiro para o início do arquivo
    std::streampos header_pos = file.tellp();

    // Espaço de 4 bytes reservado para armazenar o tamanho do cabeçalho e quantos bits
    // foram adicionados para fechar o byte final
    //A variável header_space é apenas para os 3 primeiros bytes que estão reservador para dizer o tamanho
    //do cabeçalho.
    unsigned char header_space[3] = {0};
    std::bitset<32> reserve_header(0);
    file.write(reinterpret_cast<char*>(&reserve_header), 4);

    FileCompressor::WriteTreeInFileRecursive(file, root, buffer, header_size);

    // Caso tenha algo no buffer
    FileCompressor::EmptyBufferWithHeader(file, buffer, header_size);


    // Move o ponteiro de leitura para a posição inicial do arquivo
    file.seekp(header_pos);

    // Converte o tamanho do cabeçalho em um array de bytes
    header_space[0] = (header_size >> 16) & 0xFF;
    header_space[1] = (header_size >> 8) & 0xFF;
    header_space[2] = header_size & 0xFF;

    // Escreve o tamanho do cabeçalho nos 3 primeiros bytes
    file.write(reinterpret_cast<char*>(header_space), 3);

    // Move o ponteiro de volta para o final do arquivo
    file.seekp(0, std::ios::end);
}

void FileCompressor::WriteTreeInFileRecursive(std::ofstream& FILENAME, Cell* root, std::string& buffer, int& header_size) {
    if (root != nullptr) {
        if (root->m_Left == nullptr && root->m_Right == nullptr) {
            buffer+= "1";
            std::bitset<BYTE_SIZE_COMPRESSOR>char_code(root->m_Char);
            buffer+= char_code.to_string();
            std::bitset<BYTE_SIZE_COMPRESSOR> byte(buffer.substr(0, BYTE_SIZE_COMPRESSOR));
            FILENAME.write(reinterpret_cast<char*>(&byte), 1);
            header_size++;
            buffer = buffer.substr(BYTE_SIZE_COMPRESSOR, buffer.size() - 1);
        }

        else {
            buffer+= "0";
            if (buffer.size() >= BYTE_SIZE_COMPRESSOR) {
                std::bitset<BYTE_SIZE_COMPRESSOR> byte(buffer.substr(0, BYTE_SIZE_COMPRESSOR));
                FILENAME.write(reinterpret_cast<char*>(&byte), 1);
                header_size++;
                buffer = buffer.substr(BYTE_SIZE_COMPRESSOR, buffer.size() - 1);
            }
        }
        FileCompressor::WriteTreeInFileRecursive(FILENAME, root->m_Left, buffer, header_size);
        FileCompressor::WriteTreeInFileRecursive(FILENAME, root->m_Right, buffer, header_size);
    }
}

void FileCompressor::Compress(const std::string& INPUT_FILE, const std::string& OUTPUT_FILE) {
    //Cria as variáveis necessárias
    std::string buffer = "";
    Hashtable table;
    HuffmanTree tree;
    Dictionary dictionary;

    //Lê o arquivo para montar a árvore
    ReadFromFile(INPUT_FILE, table, tree, dictionary);

    //Abre o arquivo denovo para gerar o arquivo binário
    std::ifstream stream(INPUT_FILE);
    if(!stream.is_open()) {
        std::cout << "Erro na Função FileCompressor::Compress. Arquivo: " << INPUT_FILE << " para leitura não foi aberto ou não existe\n";
        return;
    }

    /*Pega quantos bytes um arquivo tem para ler ele. Por algum motivo o método 
    file.eof() itera por uma vez a mais*/
    stream.seekg(0, stream.end);
    unsigned long long stream_size = stream.tellg();
    stream.seekg(0, stream.beg); 

    //arquivo aberto para escrita do código de huffman
    std::ofstream file(OUTPUT_FILE, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Erro na Função FileCompressor::Compress. Arquivo: " << OUTPUT_FILE << " para escrita não foi aberto ou não existe\n";
        return;
    }

    //Escreve o cabeçalho no arquivo de output
    FileCompressor::WriteTreeInFile(file, tree.m_Root);

    //Escreve o texto no formato de código de huffman
    for(unsigned long long i = 0; i < stream_size; i++) {
        unsigned char aux;
        stream.read(reinterpret_cast<char*>(&aux), 1);
        buffer = buffer + dictionary.m_Dictionary[aux];

        if (buffer.size() >= BYTE_SIZE_COMPRESSOR) {
            FileCompressor::WriteBufferInFile(file, buffer);
        }
    }
    //Resto da string e variável para saber quantos zeros foram colocados no final
    int zero_count = 0;
    FileCompressor::EmptyBufferWithZeroCount(file, buffer, zero_count);
    //Volta o ponteiro para o byte 4 para escrever quantos zeros foram colocados no final
    file.seekp(3);
    file.write(reinterpret_cast<char*>(&zero_count), 1);
    file.seekp(0, std::ios::end);

    //Fecha os arquivos
    file.close();
    stream.close();
}