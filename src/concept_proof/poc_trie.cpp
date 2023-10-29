#include <trie.h>

int main() {
    Trie trie;
    // trie.generate("./data/american-english.txt");
    trie.generate("./data/dummy.txt");
    trie.printDigraph("./graphs/graphViz");

    return 0;
}