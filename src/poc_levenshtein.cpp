#include "../libraries/levenshtein.h"

int main() {
    LevenshteinAutomaton lev("woof", 1);
    lev.generate();
    lev.printDigraph("./graphs/graphViz");
    
    return 0;
}



