#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    // Substitua "palavras.txt" pelo caminho do seu arquivo
    std::ifstream arquivoEntrada("./data/dummy.txt");

    if (!arquivoEntrada.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada!" << std::endl;
        return 1;
    }

    std::vector<std::string> palavras;
    std::string palavra;

    // Lê as palavras do arquivo de entrada e armazena no vetor
    while (std::getline(arquivoEntrada, palavra)) {
        palavras.push_back(palavra);
    }
    arquivoEntrada.close();

    // Ordena o vetor lexicograficamente
    std::sort(palavras.begin(), palavras.end());

    // Substitua "palavras_ordenadas.txt" pelo caminho desejado para o arquivo de saída
    std::ofstream arquivoSaida("./data/dummy-correct.txt");

    if (!arquivoSaida.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída!" << std::endl;
        return 1;
    }

    // Escreve as palavras ordenadas no arquivo de saída
    for (const auto& p : palavras) {
        arquivoSaida << p << std::endl;
    }

    std::cout << "Palavras ordenadas e escritas em 'palavras_ordenadas.txt'" << std::endl;

    arquivoSaida.close();
    return 0;
}
