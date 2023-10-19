#ifndef EXAME_MAST_H
#define EXAME_MAST_H

#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>

#define MAX_WORD_SIZE 100

struct STATE {

    STATE() {
        isFinal = false;
        transactions.clear();
    }

    std::map<char, std::pair<unsigned int, STATE *>> transactions;
    bool isFinal;
};

class MAST {

    public:
        
        std::size_t nStates = 0;

        MAST();
        void printDigraph();
        void generate(std::ifstream ordenatedWords);


    private:
    
        std::map<STATE *, std::size_t> states;
        STATE *tempStates[MAX_WORD_SIZE];
        STATE *initialState;

        void setTransition(STATE *state, char c, unsigned int value, STATE *nextState);
        STATE *getNextStateTransition(STATE *state, char c);
        unsigned int getValueTransition(STATE *state, char c);
        void setFinal(STATE *state, bool isFinal);
        STATE *findMinimized(STATE *s);
        void cleanState(STATE *state);
};

#endif /* MAST_H */