#include "../includes/Levenshtein.h"

int main() {
    std::string word = "levenshtein";
    LevenshteinAutomaton lev(word, 1);
    lev.generate();
    lev.printDigraph("./graphs/graphViz");
    
    return 0;
}