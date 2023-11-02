#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <utility>

struct STATE_LEV {
    std::map<char, STATE_LEV *> transitions;
    bool isMatch;
};

class LevenshteinAutomaton {

public:
    
    STATE_LEV *initialState;

    LevenshteinAutomaton(const std::string& s, int n);
    ~LevenshteinAutomaton(void);
    void generate(void);
    void printDigraph(const std::string& graphVizFolder);

private:

    std::string s;
    int max_edits;
    std::vector<STATE_LEV *> statesAddress;
    std::string graphVizFolder;
    
    std::vector<std::tuple<int, int, char>> transitionsStates;
    std::vector<int> start(void);
    std::vector<int> step(const std::vector<int>& state, char c);
    bool is_match(const std::vector<int>& state);
    bool can_match(const std::vector<int>& state);
    std::set<char> transitions(const std::vector<int>& state);

    int explore(std::vector<int> &state,
                std::map<std::vector<int>, int> &states,
                int &counter, std::vector<int> &matching,
                std::vector<std::tuple<int, int, char>> &transitionsStates);  
};

#endif /* LEVENSHTEIN_H */