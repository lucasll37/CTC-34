# Nome do executável
EXECUTABLE_MAST = ./build/mast.exe
EXECUTABLE_LEV = ./build/lev.exe

# Diretório dos arquivos de origem
SRC_DIR = ./src

# Diretório de bibiotecas
SRC_LIB = ./libraries

# Lista de arquivos de origem
SOURCES_MAST = $(SRC_DIR)/poc_mast.cpp $(SRC_LIB)/minAcyclicSubseqTransducers.cpp
SOURCES_LEV = $(SRC_DIR)/poc_levenshtein.cpp $(SRC_LIB)/levenshtein.cpp

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

graph-lev:
	dot -Tpng ./graphs/lev.dot -o ./graphs/lev.png

graph-mast:
	dot -Tpng ./graphs/mast.dot -o ./graphs/mast.png

clean:
	$(RM) $(EXECUTABLE_MAST) $(EXECUTABLE_LEV)

all-lev:
	$(CC) $(CFLAGS) $(SOURCES_LEV) -o $(EXECUTABLE_LEV)
	$(EXECUTABLE_LEV)
	dot -Tpng ./graphs/graphViz/lev.dot -o ./graphs/lev.png

all-mast:
	$(CC) $(CFLAGS) $(SOURCES_MAST) -o $(EXECUTABLE_MAST)
	$(EXECUTABLE_MAST)
	dot -Tpng ./graphs/graphViz/mast.dot -o ./graphs/mast.png