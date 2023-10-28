# Exame de CTC-34

### Obs.: Execute no Linux ou WSL2 através dos comandos do makefile. Caso utilize outro SO, entenda o que o comando faz e o adapte-o para execução direta dos comandos no terminal.

- #### `poc-lev`: Compila prova de conceito do algoritmo de Levenshtein (`./src/concept_proof/poc_levenshtein.cpp`), salva executável em `./build/poc_trie.exe`, gera arquivo de descrição de grafo em `./graphs/graphViz/poc_lev.dot` e imagem desse mesmo grafo gerado em `./graphs/poc_lev.png`.

- #### `poc-trie`: Compila prova de conceito de uma TRIE (`./src/concept_proof/poc_trie.cpp`), salva executável em `./build/poc_trie.exe`, gera arquivo de descrição de grafo em `./graphs/graphViz/poc_trie.dot` e imagem desse mesmo grafo gerado em `./graphs/poc_trie.png`.

- #### `poc-mast`: Compila prova de conceito de uma FST (implementada com o algoritmo MAST) (`./src/concept_proof/poc_mast.cpp`), salva executável em `./build/poc_mast.exe`, gera arquivo de descrição de grafo em `./graphs/graphViz/poc_mast.dot` e imagem desse mesmo grafo gerado em `./graphs/poc_mast.png`.

- #### `build-mast`: Compila o autocomplete implementado com um FST (`./src/main_mast.cpp`), salva executável em `./build/main_mast.exe` e o executa na sequência.

- #### `build-trie`: Compila o autocomplete implementado com uma TRIE (`./src/main_trie.cpp`), salva executável em `./build/main_trie.exe` e o executa na sequência.

- #### `run-trie`: Executa o executável previamente compilado do autocomplete implementado com uma TRIE (`./build/main_trie.exe`).

- #### `run-mast`: Executa o executável previamente compilado do autocomplete implementado com um FST (`./build/main_mast.exe`).

- #### `clean`: Apaga todos os arquivos executáveis (*.exe) da pasta `./build`