NAME = program
CC = g++
SRC_DIR = ./src
INC_DIR = ./include
BIN_DIR = ./bin
OBJ_DIR = ./obj
CFLAGS = -Wall -g
EXE = $(BIN_DIR)/$(NAME)

OBJS = \
	$(OBJ_DIR)/Cell.o \
	$(OBJ_DIR)/LinkedList.o \
	$(OBJ_DIR)/Hashtable.o \
	$(OBJ_DIR)/HuffmanTree.o \
	$(OBJ_DIR)/Dictionary.o \
	$(OBJ_DIR)/FileCompressor.o \
	$(OBJ_DIR)/FileDecompressor.o \
	$(OBJ_DIR)/main.o

all: $(EXE)

run: all
	$(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/**/%.cpp $(INC_DIR)/%.hpp
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -o $@

valgrind: $(EXE)
	valgrind --leak-check=full bin/program
	
clean:
	rm -f $(OBJS)
	rm -f $(EXE)