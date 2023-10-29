#include <levenshtein.h>

int main(int argc, char *argv[]) {
    std::string word;

    if(argc == 2) word = argv[1];
    else word = "zoo";
    
    LevenshteinAutomaton lev(word, 1);

    lev.generate();
    lev.printDigraph("./graphs/graphViz");
    
    return 0;
}