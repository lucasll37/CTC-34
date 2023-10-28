#include <minAcyclicSubseqTransducers.h>

int main() {
    MinAcyclicSubseqTransducers mast;
    mast.generate("./data/dummy.txt");
    mast.printDigraph("./graphs/graphViz");

    return 0;
}