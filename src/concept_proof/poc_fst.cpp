#include "../../includes/FiniteStateTransducer.h"

int main() {
    FiniteStateTransducer fst;
    fst.generate("./data/dummy.txt");
    fst.printDigraph("./graphs/graphViz");

    return 0;
}