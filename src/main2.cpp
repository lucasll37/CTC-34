#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include "levenshtein.h"



int main() {

    LevenshteinAutomaton lev("woof", 1);

    std::map<std::vector<int>, int> states;
    int counter = 0;
    std::vector<int> matching;
    std::vector<std::tuple<int, int, char>> transitionsStates;

    std::vector<int> initialState(lev.start());

    lev.explore(initialState, states, counter, matching, transitionsStates);


    int start, end;
    char label;

    std::ofstream file("./graphs/graph.dot");

    file << "digraph G {\n";

    for (const auto& transaction : transitionsStates) {
        start = std::get<0>(transaction);
        end = std::get<1>(transaction);
        label = std::get<2>(transaction);

        file << start << " -> " << end << " [label=\" " << label << " \"];\n";
    }

    for (int i : matching) {
        file << i << " [style=filled];\n";
    }

    file << "}\n";
    
    file.close();

    std::cout << "Graph saved to 'graph.dot'. Submit this to Graphviz for visualization." << std::endl;

    return 0;
}



