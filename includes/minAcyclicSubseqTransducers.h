#ifndef MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H
#define MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H

#include <unordered_map>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

#define MAX_WORD_SIZE 30

struct STATE {

    STATE() {
        isFinal = false;
        transictions.clear();
    }

    bool isFinal;
    std::unordered_map<char, std::pair<unsigned int, STATE *>> transictions;
};

struct StateHasher {
    size_t operator()(const STATE *state) const {
        size_t hashValue = 0;
        
        hashValue ^= std::hash<bool>()(state->isFinal) + 0x9e3779b9;
        
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


class MinAcyclicSubseqTransducers {

    public:
        
        STATE *initialState;
        std::size_t nStates = 0;
        std::size_t nWords = 0;

        MinAcyclicSubseqTransducers();
        ~MinAcyclicSubseqTransducers();
        void printDigraph(const std::string& graphVizFolder);
        std::size_t generate(const std::string& filePath);

    private:

        std::unordered_map<STATE *, std::size_t, StateHasher, StateEqual> states;
        STATE *tempStates[MAX_WORD_SIZE];

        void setTransition(STATE *state, char c, unsigned int value, STATE *nextState);
        void setFinal(STATE *state, bool isFinal);
        STATE *findMinimized(STATE *s);
        void cleanState(STATE *state);
};

#endif /* MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H */