# Nome do executável
EXECUTABLE_MAST = ./build/mast.exe
EXECUTABLE_LEV = ./build/lev.exe

# Diretório dos arquivos de origem
SRC_DIR = ./src

# Lista de arquivos de origem
SOURCES_MAST = $(SRC_DIR)/poc_mast.cpp $(SRC_DIR)/mast.cpp
SOURCES_LEV = $(SRC_DIR)/poc_levenshtein.cpp $(SRC_DIR)/levenshtein.cpp

# Comando de compilação
CC = g++

# Opções do compilador
CFLAGS = -Wall -std=c++11

# Comando para limpar os arquivos compilados
RM = rm -f

mast:
	$(CC) $(CFLAGS) $(SOURCES_MAST) -o $(EXECUTABLE_MAST)

lev:
	$(CC) $(CFLAGS) $(SOURCES_LEV) -o $(EXECUTABLE_LEV)

run-mast:
	$(EXECUTABLE_MAST)

run-lev:
	$(EXECUTABLE_LEV)

graph:
	dot -Tpng ./graphs/graph.dot -o ./graphs/graph.png

clean:
	$(RM) $(EXECUTABLE_MAST) $(EXECUTABLE_LEV)