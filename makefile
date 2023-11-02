# Diretório dos arquivos de origem
SRC_DIR = ./src

# Diretório de bibiotecas
SRC_LIB = ./includes

# Diretório de executáveis
SRC_EXE = ./build


# Nome do executável
EXECUTABLE_SORT = $(SRC_EXE)/sort.exe
EXECUTABLE_LEV = $(SRC_EXE)/poc_lev.exe
EXECUTABLE_TRIE = $(SRC_EXE)/poc_trie.exe
EXECUTABLE_MAST = $(SRC_EXE)/poc_fst.exe
EXECUTABLE_AUTO_COMPLETE_TRIE = $(SRC_EXE)/main_trie.exe
EXECUTABLE_AUTO_COMPLETE_MAST = $(SRC_EXE)/main_fst.exe


# Lista de arquivos de origem
SOURCES_LEV = $(SRC_LIB)/Levenshtein.cpp
SOURCES_TRIE = $(SRC_LIB)/Trie.cpp

SOURCES_SORT = $(SRC_DIR)/sort.cpp
SOURCES_FST = $(SRC_LIB)/FiniteStateTransducer.cpp
SOURCES_AUTO_COMPLETE_TRIE = $(SRC_LIB)/AutoComplete_trie.cpp $(SOURCES_LEV)  $(SOURCES_TRIE) $(SRC_LIB)/utils.h
SOURCES_AUTO_COMPLETE_FST = $(SRC_LIB)/AutoComplete_fst.cpp $(SOURCES_LEV) $(SOURCES_FST) $(SRC_LIB)/utils.h

# Comando de compilação
CC = g++

# Opções do compilador
CFLAGS = -Wall -Wextra -std=c++17 -O3

# Comando para limpar os arquivos compilados
RM = rm -f

poc-lev:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/concept_proof/poc_levenshtein.cpp $(SOURCES_LEV) -o $(EXECUTABLE_LEV)
	$(EXECUTABLE_LEV)
	dot -Tpng ./graphs/graphViz/poc_lev.dot -o ./graphs/poc_lev.png

poc-trie:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/concept_proof/poc_trie.cpp $(SOURCES_TRIE) -o $(EXECUTABLE_TRIE)
	$(EXECUTABLE_TRIE)
	dot -Tpng ./graphs/graphViz/poc_trie.dot -o ./graphs/poc_trie.png

poc-fst:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/concept_proof/poc_fst.cpp $(SOURCES_FST) -o $(EXECUTABLE_MAST)
	$(EXECUTABLE_MAST)
	dot -Tpng ./graphs/graphViz/poc_fst.dot -o ./graphs/poc_fst.png

build-sort:
	$(CC) $(CFLAGS) $(SOURCES_SORT) -o $(EXECUTABLE_SORT)

build-trie:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/main_trie.cpp $(SOURCES_AUTO_COMPLETE_TRIE)  -o $(EXECUTABLE_AUTO_COMPLETE_TRIE)

build-fst:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/main_fst.cpp $(SOURCES_AUTO_COMPLETE_FST)  -o $(EXECUTABLE_AUTO_COMPLETE_MAST)

run-sort:
	$(EXECUTABLE_SORT) ./data/american-english.txt ./data/american-english-correct.txt

run-trie:
	$(EXECUTABLE_AUTO_COMPLETE_TRIE)

run-fst:
	$(EXECUTABLE_AUTO_COMPLETE_MAST)

all-sort:
	$(CC) $(CFLAGS) $(SOURCES_SORT) -o $(EXECUTABLE_SORT)
	$(EXECUTABLE_SORT) ./data/american-english.txt ./data/american-english-correct.txt

all-trie:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/main_trie.cpp $(SOURCES_AUTO_COMPLETE_TRIE)  -o $(EXECUTABLE_AUTO_COMPLETE_TRIE)
	$(EXECUTABLE_AUTO_COMPLETE_TRIE)

all-fst:
	$(CC) $(CFLAGS) -I$(SRC_LIB) $(SRC_DIR)/main_fst.cpp $(SOURCES_AUTO_COMPLETE_FST)  -o $(EXECUTABLE_AUTO_COMPLETE_MAST)
	$(EXECUTABLE_AUTO_COMPLETE_MAST)

clear:
	$(RM) $(EXECUTABLE_MAST) $(EXECUTABLE_LEV) $(EXECUTABLE_TRIE) $(EXECUTABLE_AUTO_COMPLETE_TRIE) $(EXECUTABLE_AUTO_COMPLETE_MAST) $(EXECUTABLE_SORT)
