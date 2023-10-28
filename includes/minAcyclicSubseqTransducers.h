#ifndef MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H
#define MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H

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
        transactions.clear();
    }

    std::unordered_map<char, std::pair<unsigned int, STATE *>> transactions;
    bool isFinal;
};

struct StateHasher {
    size_t operator()(const STATE *state) const {
        size_t hashValue = 0;
        
        // Hash para o campo isFinal
        hashValue ^= std::hash<bool>()(state->isFinal) + 0x9e3779b9;
        
        // Hash para cada item no unordered_map
        for(const auto& pair : state->transactions) {
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
        
        // return lhs->transactions == rhs->transactions;

        for(const auto& pair : rhs->transactions) {
            if(pair.first != lhs->transactions.find(pair.first)->first) {
                return false;
            }
        }

        for(const auto& pair : lhs->transactions) {
            if(pair.first != rhs->transactions.find(pair.first)->first) {
                return false;
            }
        }

        return true;
    }
};

class MinAcyclicSubseqTransducers {

    public:
        
        STATE *initialState;
        std::size_t nStates = 0;
        std::size_t nWords;

        MinAcyclicSubseqTransducers();
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