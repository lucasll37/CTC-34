#include "levenshtein.h"


LevenshteinAutomaton::LevenshteinAutomaton(const std::string& s, int n) : s(s), max_edits(n) {}

LevenshteinAutomaton::~LevenshteinAutomaton(void) {
    for (auto &x : statesAddress) {
        delete x;
    }
}

std::vector<int> LevenshteinAutomaton::start(void) {
    std::vector<int> v(s.size() + 1);
    for (size_t i = 0; i <= s.size(); ++i) {
        v[i] = i;
    }
     
    return v;
}

std::vector<int> LevenshteinAutomaton::step(const std::vector<int> &state, char c) {
    std::vector<int> new_state;
    new_state.push_back(state[0] + 1);
    for (size_t i = 0; i < state.size() - 1; ++i) {
        int cost = (s[i] == c) ? 0 : 1;
        new_state.push_back(std::min({new_state[i] + 1, state[i] + cost, state[i + 1] + 1}));
    }
    
    for (auto &x : new_state) {
        x = std::min(x, max_edits + 1);
    }

    return new_state;
}

bool LevenshteinAutomaton::is_match(const std::vector<int>& state) {
    return state.back() <= max_edits;
}

bool LevenshteinAutomaton::can_match(const std::vector<int>& state) {
    return *std::min_element(state.begin(), state.end()) <= max_edits;
}

std::unordered_set<char> LevenshteinAutomaton::transitions(const std::vector<int>& state) {
    std::unordered_set<char> result;
    for (size_t i = 0; i < s.size(); ++i) {
        if (state[i] <= max_edits) {
            result.insert(s[i]);
        }
    }
    return result;
}

int LevenshteinAutomaton::explore(std::vector<int> &state,
                                  std::map<std::vector<int>, int> &states,
                                  int &counter, std::vector<int> &matching,
                                  std::vector<std::tuple<int, int, char>> &transitionsStates) {

    if(states.find(state) != states.end()) {
        return states[state];
    }

    int i = counter++;
    states[state] = i;

    if(is_match(state)) {
        matching.push_back(i);
    }

    auto trans = transitions(state);
    trans.insert('*');

    for (const char c : trans) {
        std::vector<int> nextState(step(state, c));
        int j = explore(nextState, states, counter, matching, transitionsStates);
        transitionsStates.push_back(std::make_tuple(i, j, c));
    }

    return i;
}

void LevenshteinAutomaton::generate(void) {

    std::map<std::vector<int>, int> states;
    int counter = 0;
    std::vector<int> matching;
    std::vector<std::tuple<int, int, char>> transitionsStates;
    std::vector<int> initialState(start());
    explore(initialState, states, counter, matching, transitionsStates);

    statesAddress.resize(counter);

    for(int i = 0; i < counter; i++) {
        statesAddress[i] = new STATE();
        statesAddress[i]->isMatch = false;
        statesAddress[i]->transitions.clear();
    }

    int start, end;
    char label;

    std::ofstream file("./graphs/graph.dot");
    file << "digraph G {\n";
    

    for (const auto& transaction : transitionsStates) {
        start = std::get<0>(transaction);
        end = std::get<1>(transaction);
        label = std::get<2>(transaction);
        file << start << " -> " << end << " [label=\" " << label << " \"];\n";

        statesAddress[start]->transitions[label] = statesAddress[end];
    }

    for (int i : matching) {
        file << i << " [style=filled];\n";

        statesAddress[i]->isMatch = true;
    }

    DFA = statesAddress[0];

    file << "}\n";
    file.close();
    std::cout << "Graph saved to 'graph.dot'. Submit this to Graphviz for visualization." << std::endl;
}