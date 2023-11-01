# Exame de CTC-34

#### Obs.: Execute no Linux ou WSL2 através dos comandos do makefile. Caso utilize outro SO, entenda o que o comando faz e o adapte-o para execução direta dos comandos no terminal.

## Exemplo de execução

```bash
make poc-lev
```

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
    make all-fst
    ```

## Atalhos

- #### Compila o autocomplete implementado com um FST (`./src/main_fst.cpp`), salva executável em `./build/main_fst.exe` e o executa na sequência.
    ```bash
    make build-fst
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