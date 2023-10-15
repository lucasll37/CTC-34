#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include "levenshtein.h"



LevenshteinAutomaton::LevenshteinAutomaton(const std::string& s, int n) : s(s), max_edits(n) {}

std::vector<int> LevenshteinAutomaton::start() {
    std::vector<int> v(s.size() + 1);
    for (size_t i = 0; i <= s.size(); ++i) {
        v[i] = i;
    }
    return v;
}

std::vector<int> LevenshteinAutomaton::step(const std::vector<int>& state, char c) {
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