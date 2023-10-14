#include "mast.h"

MAST::MAST(void) {
    FST = new STATE();
    FST->isFinal = true;
}

MAST::~MAST(void) {
    delete FST;
}

void MAST::generate(std::ifstream &inputFile) {

    MAST::FST->isFinal = false;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;

    }
}