#ifndef MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H
#define MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H

#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define MAX_WORD_SIZE 100

struct STATE {

    STATE() {
        isFinal = false;
        transactions.clear();
    }

    std::map<char, std::pair<unsigned int, STATE *>> transactions;
    bool isFinal;
};

class MinAcyclicSubseqTransducers {

    public:
        
        std::size_t nStates = 0;

        MinAcyclicSubseqTransducers();
        void printDigraph(const std::string& graphVizFolder);
        void generate(const std::string& filePath);

    private:
    
        std::map<STATE *, std::size_t> states;
        STATE *tempStates[MAX_WORD_SIZE];
        STATE *initialState;

        void setTransition(STATE *state, char c, unsigned int value, STATE *nextState);
        void setFinal(STATE *state, bool isFinal);
        STATE *findMinimized(STATE *s);
        void cleanState(STATE *state);
};

#endif /* MIN_ACYCLIC_SUBSEQ_TRANSDUCERS_H */