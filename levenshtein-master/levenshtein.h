#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class LevenshteinAutomaton {
private:
    std::string s;
    int max_edits;

public:
    LevenshteinAutomaton(const std::string& s, int n);
    std::vector<int> start();
    std::vector<int> step(const std::vector<int>& state, char c);
    bool is_match(const std::vector<int>& state);
    bool can_match(const std::vector<int>& state);
    std::unordered_set<char> transitions(const std::vector<int>& state);

};