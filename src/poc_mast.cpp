#include "mast.h"

int main() {
    std::ifstream american_english("./data/dummy.txt");
    MAST mast;

    if (!american_english.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
        return 1;
    }

    mast.generate(std::move(american_english));
    mast.printDigraph();

    return 0;
}