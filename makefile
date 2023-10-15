# Nome do executável
EXECUTABLE = ./build/mast.exe

# Diretório dos arquivos de origem
SRC_DIR = ./src

# Lista de arquivos de origem
SOURCES = $(SRC_DIR)/main2.cpp $(SRC_DIR)/levenshtein.cpp
# SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/mast.cpp

# Comando de compilação
CC = g++

# Opções do compilador
CFLAGS = -Wall -std=c++11

# Comando para limpar os arquivos compilados
RM = rm -f

all: 
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

run:
	$(EXECUTABLE)

graph:
	dot -Tpng ./graphs/graph.dot -o ./graphs/graph.png

clean:
	$(RM) $(EXECUTABLE)