# Diretório dos arquivos de origem
SRC_DIR = ./src

# Diretório de bibiotecas
SRC_LIB = ./includes

# Diretório de executáveis
SRC_EXE = ./build


# Nome do executável
EXECUTABLE_AUTO_COMPLETE_TRIE = $(SRC_EXE)/main_trie.exe
EXECUTABLE_AUTO_COMPLETE_MAST = $(SRC_EXE)/main_mast.exe
EXECUTABLE_MAST = $(SRC_EXE)/poc_mast.exe
EXECUTABLE_LEV = $(SRC_EXE)/poc_lev.exe
EXECUTABLE_TRIE = $(SRC_EXE)/poc_trie.exe


# Lista de arquivos de origem
SOURCES_MAST = $(SRC_LIB)/minAcyclicSubseqTransducers.cpp
SOURCES_LEV = $(SRC_LIB)/levenshtein.cpp
SOURCES_TRIE = $(SRC_LIB)/trie.cpp
SOURCES_AUTO_COMPLETE_TRIE = $(SRC_LIB)/auto_complete_trie.cpp $(SRC_LIB)/levenshtein.cpp  $(SRC_LIB)/trie.cpp $(SRC_LIB)/utils.h
SOURCES_AUTO_COMPLETE_MAST = $(SRC_LIB)/auto_complete_mast.cpp $(SRC_LIB)/levenshtein.cpp $(SRC_LIB)/minAcyclicSubseqTransducers.cpp $(SRC_LIB)/utils.h

# Comando de compilação
CC = g++

# Opções do compilador
CFLAGS = -Wall -Wextra -std=c++11 -O3

# Comando para limpar os arquivos compilados
RM = rm -f

poc-lev:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/concept_proof/poc_levenshtein.cpp $(SOURCES_LEV) -o $(EXECUTABLE_LEV)
	$(EXECUTABLE_LEV)
	dot -Tpng ./graphs/graphViz/poc_lev.dot -o ./graphs/poc_lev.png

poc-mast:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/concept_proof/poc_mast.cpp $(SOURCES_MAST) -o $(EXECUTABLE_MAST)
	$(EXECUTABLE_MAST)
	dot -Tpng ./graphs/graphViz/poc_mast.dot -o ./graphs/poc_mast.png

poc-trie:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/concept_proof/poc_trie.cpp $(SOURCES_TRIE) -o $(EXECUTABLE_TRIE)
	$(EXECUTABLE_TRIE)
	dot -Tpng ./graphs/graphViz/poc_trie.dot -o ./graphs/poc_trie.png

build-trie:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/main_trie.cpp $(SOURCES_AUTO_COMPLETE_TRIE)  -o $(EXECUTABLE_AUTO_COMPLETE_TRIE)
	$(EXECUTABLE_AUTO_COMPLETE_TRIE)

build-mast:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/main_mast.cpp $(SOURCES_AUTO_COMPLETE_MAST)  -o $(EXECUTABLE_AUTO_COMPLETE_MAST)
	$(EXECUTABLE_AUTO_COMPLETE_MAST)

run-trie:
	$(EXECUTABLE_AUTO_COMPLETE_TRIE)

run-mast:
	$(EXECUTABLE_AUTO_COMPLETE_MAST)

clean:
	$(RM) $(EXECUTABLE_MAST) $(EXECUTABLE_LEV) $(EXECUTABLE_TRIE) $(EXECUTABLE_AUTO_COMPLETE_TRIE) $(EXECUTABLE_AUTO_COMPLETE_MAST)