#include "levenshtein.h"

int main() {
    LevenshteinAutomaton lev("wood", 1);
    lev.generate();
    lev.printDigraph("./graphs/graphViz");
    
    return 0;
}