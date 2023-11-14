# Exame de CTC-34

#### Obs.: Execute no Linux ou WSL2 através dos comandos do makefile. Caso utilize outro Sistema Operacional, entenda o que o comando faz e o adapte-o para execução direta dos comandos no terminal.

## Base de dados ordenados

- `american-english.txt`: Dicionário original da língua inglesa fornecido no Linux (quase ordenado).
- `american-english-correct.txt`: Dicionário original da língua inglesa com correção de ordenação de casos anômalos (Ångström, étude, ...). Gerado com o comando:

    ```bash
    make all-sort
    ```
- `hundred.txt`: Lista de 100 palavras comuns da língua inglesa.
- `months.txt`: Lista de meses do ano em inglês.
- `week.txt`: Lista de dias da semana em inglês.
- `dummy.txt`:	Lista de palavras consultada para a prova de conceito.

sugestão de uso: popule `dummy.txt` com palavras de sua preferência e execute as provas de conceito para ver o funcionamento dos algoritmos.

## Provas de conceito

#### Casos simples que geram gráficos para visualização de funcionamento dos algoritmos e permitem o entendimento da interface criada.

- #### Compila prova de conceito do algoritmo de Levenshtein (`./src/concept_proof/poc_levenshtein.cpp`), salva executável em `./build/poc_trie.exe`, gera arquivo de descrição de grafo em `./graphs/graphViz/poc_lev.dot` e imagem desse mesmo grafo gerado em `./graphs/poc_lev.png`.
    ```bash
    make poc-lev
    ```

- #### Compila prova de conceito de uma TRIE (`./src/concept_proof/poc_trie.cpp`), salva executável em `./build/poc_trie.exe`, gera arquivo de descrição de grafo em `./graphs/graphViz/poc_trie.dot` e imagem desse mesmo grafo gerado em `./graphs/poc_trie.png`.
    ```bash
    make poc-trie
    ```

- #### Compila prova de conceito de uma FST (implementada com o algoritmo MAST) (`./src/concept_proof/poc_fst.cpp`), salva executável em `./build/poc_fst.exe`, gera arquivo de descrição de grafo em `./graphs/graphViz/poc_fst.dot` e imagem desse mesmo grafo gerado em `./graphs/poc_fst.png`.
    ```bash
    make poc-fst
    ```


## Compilação do AutoComplete

- #### Compila o autocomplete implementado com um FST (`./src/main_fst.cpp`), salva executável em `./build/main_fst.exe`.
    ```bash
    make build-fst
    ```

- #### Compila o autocomplete implementado com uma TRIE (`./src/main_trie.cpp`), salva executável em `./build/main_trie.exe`.
    ```bash
    make build-trie
    ```

## Execução do AutoComplete

- #### Executa o arquivo previamente compilado do autocomplete implementado com uma TRIE (`./build/main_trie.exe`).
    ```bash
    make run-trie
    ```

- #### Executa o arquivo previamente compilado do autocomplete implementado com um FST (`./build/main_fst.exe`).
    ```bash
    make run-fst
    ```

## Atalhos (Compilação e Execução)

- #### Compila o autocomplete implementado com um FST (`./src/main_fst.cpp`), salva executável em `./build/main_fst.exe` e o executa na sequência.
    ```bash
    make all-fst
    ```

- #### Compila o autocomplete implementado com uma TRIE (`./src/main_trie.cpp`), salva executável em `./build/main_trie.exe`  e o executa na sequência.
    ```bash
    make all-trie
    ```
## Exclusão de Executáveis

- #### Apaga todos os arquivos executáveis (*.exe) da pasta `./build`.
    ```bash
    make clear
    ```