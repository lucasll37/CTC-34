#include "../includes/Levenshtein.h"

int main() {
    std::string word = "test";
    LevenshteinAutomaton lev(word, 1);
    lev.generate();
    lev.printDigraph("./graphs/graphViz");
    
    return 0;
}