#ifndef EXAME_LEVENSHTEIN_H
#define EXAME_LEVENSHTEIN_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <utility>


struct STATE {
    std::map<char, STATE *> transitions;
    bool isMatch;
};

class LevenshteinAutomaton {

private:

    std::string s;
    int max_edits;
    std::vector<STATE *> statesAddress;
    std::vector<int> start(void);
    std::vector<int> step(const std::vector<int>& state, char c);
    bool is_match(const std::vector<int>& state);
    bool can_match(const std::vector<int>& state);
    std::unordered_set<char> transitions(const std::vector<int>& state);

    int explore(std::vector<int> &state,
                std::map<std::vector<int>, int> &states,
                int &counter, std::vector<int> &matching,
                std::vector<std::tuple<int, int, char>> &transitionsStates);

public:

    STATE *DFA;
    LevenshteinAutomaton(const std::string& s, int n);
    ~LevenshteinAutomaton(void);
    void generate(void);
    
};

#endif /* LEVENSHTEIN_H */