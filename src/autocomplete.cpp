#include "../libraries/levenshtein.h"
#include "../libraries/mast.h"

int main(){
    MAST mast;
    std::ifstream american_english("./data/dummy.txt"); // american-english.txt

    if (!american_english.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
        return 1;
    }

    mast.generate(std::move(american_english));
    mast.printDigraph("./graphs/graphViz");



        LevenshteinAutomaton lev("woof", 1);
    lev.generate();
    lev.printDigraph("./graphs/graphViz");
}