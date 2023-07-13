# huffman-algorithm
Projeto que implementa um compressor e descompressor para arquivos de texto no ambiente Linux. Atualmente só funciona para os 128 caracteres da tabela ASCII.


# Descrição do Projeto
> Dado um arquivo texto, queremos compactá-lo usando o algoritmo de Huffman, ou seja, devemos criar a árvore de huffman ao ler o arquivo de texto e, após a essa primeira leitura, ler o texto novamente mas desta vez trocando os caracteres pelo código que foi criado na árvore. Além disso, o programa também é capaz de descomprimir o arquivo comprimido.

## Instruções de Uso e Compilação

Para compilar o programa digite o comando `make` no terminal. Após isso você pode rodar o programa com as seguintes flags :
1. Flag `-c` : para poder compactar um arquivo de texto. Você deve possuir o arquivo de texto e também o arquivo vazio em que o código será escrito, exemplo:
* `diretoriodoprograma/program -c nome-arquivo-texto nome-arquivo-binario`

2. Flag `-d` : para poder descompactar algum arquivo anteriormente compactado pelo programa. Note
que para usar essa flag também deve existir um arquivo vazio onde será escrito o arquivo decodificado, exemplo:
* `diretoriodoprograma/program -d nome-arquivo-binario nome-arquivo-decodificado`

### Como Rodar os Arquivos Teste
Na raiz do projeto existe uma pasta com o nome `TESTES` que contém arquivos textos para serem usados como exemplo e, além disso, dois arquivos vazios que serão usados para escrever o código e, posteriormente, escrever a decodificaçao deste código. Para rodar os testes digite no terminal vá para a pasta raiz do projeto e digita os seguintes comandos:

1. `make`
2. `./bin/program -c TESTES/aragorn-speech.txt arquivo-codificado`
3. `./bin/program -d arquivo-codificado arquivo-decodificado`

Para conferir se o arquivo original e o decodificado são idênticos digite no terminal do Linux:
1. sha256sum arquivo-decodificado TESTES/aragorn-speech.txt

> Também existem arquivos maiores para teste na pasta `TESTES`, variando de 5MB até 50MB.

### TO-DO
1. Fazer funcionar com todo o UTF-8.
