#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "levenshtein.h"

int main() {
    LevenshteinAutomaton lev("woof", 10);

    std::unordered_map<std::pair<std::vector<int>, std::vector<int>>, int> states;
    std::vector<std::tuple<int, int, char>> transitions;
    std::vector<int> matching;
    int counter = 0;

    auto explore = [&](auto&& self, const std::pair<std::vector<int>, std::vector<int>>& state) -> int {
        if (states.find(state) != states.end()) {
            return states[state];
        }

        int i = counter++;
        states[state] = i;

        if (lev.is_match(state)) {
            matching.push_back(i);
        }

        auto trans = lev.transitions(state);
        trans.insert('*');

        for (char c : trans) {
            auto newstate = lev.step(state, c);
            int j = self(self, newstate);
            transitions.emplace_back(i, j, c);
        }

        return i;
    };

    explore(explore, lev.start());

    std::ofstream file("graph.dot");

    file << "digraph G {\n";

    for (const auto& [start, end, label] : transitions) {
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

