#ifndef MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H
#define MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H

#include <unordered_map>
#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define MAX_WORD_SIZE 30

struct STATE {

    STATE() {
        isFinal = false;
        transictions.clear();
        output = "";

    }

    bool isFinal;
    std::string output;
    std::size_t id;
    std::map<char, std::pair<std::string, STATE *>> transictions;
};

struct StateHasher {
    size_t operator()(const STATE *state) const {
        size_t hashValue = 0;
        
        hashValue ^= std::hash<bool>()(state->isFinal) + 0x9e3779b9;
        hashValue ^= std::hash<std::string>()(state->output) + 0x9e3779b9;
        hashValue ^= std::hash<std::size_t>()(state->id) + 0x9e3779b9;
        
        for(const auto& pair : state->transictions) {
            hashValue ^= std::hash<char>()(pair.first) + 0x9e3779b9;
            hashValue ^= std::hash<std::string>()(pair.second.first) + 0x9e3779b9;
            hashValue ^= std::hash<STATE*>()(pair.second.second) + 0x9e3779b9;
        }
        
        return hashValue;
    }
};

struct StateEqual {
    bool operator()(const STATE *lhs, const STATE *rhs) const {
        if(lhs->isFinal != rhs->isFinal) {
            return false;
        }
        
        if(lhs->output != rhs->output) {
            return false;
        }

        if(lhs->id != rhs->id) {
            return false;
        }

        if(lhs->transictions.size() != rhs->transictions.size()) {
            return false;
        }
        
        for(const auto& pair : rhs->transictions) {
            auto lhs_it = lhs->transictions.find(pair.first);

            if (lhs_it == lhs->transictions.end()) return false;
            if (pair.second.first != lhs_it->second.first) return false;        
            if (pair.second.second != lhs_it->second.second) return false;
        }

        return true;
    }
};

class Trie {

    public:
        
        STATE *initialState;
        std::size_t nStates = 0;
        std::size_t nEdges = 0;
        std::size_t nWords = 0;
        std::vector<std::string> WORDS;

        Trie();
        ~Trie();
        void printDigraph(const std::string& graphVizFolder);
        void generate(const std::string& filePath);

    private:

        std::unordered_map<STATE *, std::size_t, StateHasher, StateEqual> states;
        STATE *tempStates[MAX_WORD_SIZE];
        std::string output(STATE *state, char c);
        void setOutput(STATE *state, char c, std::string output);
        std::string stateOutput(STATE *state);
        void setStateOutput(STATE *state, std::string output);
        void setTransition(STATE *state, char c, STATE *nextState);
        void setFinal(STATE *state, bool isFinal);
        STATE *includeState(STATE *s);
        void cleanState(STATE *state);
};

#endif /* MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H */