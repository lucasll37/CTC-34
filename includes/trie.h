#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
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
    }

    std::unordered_map<char, std::pair<unsigned int, STATE *>> transictions;
    bool isFinal;
};

struct StateHasher {
    size_t operator()(const STATE *state) const {
        size_t hashValue = 0;
        
        // Hash para o campo isFinal
        hashValue ^= std::hash<bool>()(state->isFinal) + 0x9e3779b9;
        
        // Hash para cada item no unordered_map
        for(const auto& pair : state->transictions) {
            hashValue ^= std::hash<char>()(pair.first) + 0x9e3779b9;
            hashValue ^= std::hash<unsigned int>()(pair.second.first) + 0x9e3779b9;
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
        
        return lhs->transictions == rhs->transictions;

        for(const auto& pair : rhs->transictions) {
            if(pair.first != rhs->transictions.find(pair.first)->first) {
                return false;
            }
        }

        return true;
    }
};

class Trie {

    public:
        
        STATE *initialState;

        Trie();
        ~Trie();
        std::size_t nWords = 0;
        std::size_t nStates = 0;
        std::size_t nEdges = 0;
        void printDigraph(const std::string& graphVizFolder);
        void generate(const std::string& filePath);

    private:
    
        std::unordered_map<STATE *, std::size_t, StateHasher, StateEqual> states;
        STATE *tempStates[MAX_WORD_SIZE];

        void setTransition(STATE *state, char c, unsigned int value, STATE *nextState);
        void setFinal(STATE *state, bool isFinal);
        STATE *includeState(STATE *s);
        void cleanState(STATE *state);
};

#endif /* TRIE_H */