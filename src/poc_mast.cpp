#include "mast.h"

int main() {
    
    std::ifstream american_english;

    american_english.open("./data/american-english.txt");

    MAST mast;

    if (american_english.is_open()) {
        mast.generate(american_english);
    }

    else {
        std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
        return 1;
    }

    american_english.close();
    
    return 0;
}