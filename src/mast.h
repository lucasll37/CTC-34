#ifndef EXAME_MAST_H
#define EXAME_MAST_H

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <set>


struct STATE {
    std::map<char, std::pair<STATE *, std::string>> transitions;
    int output;
    bool isFinal;
};

class MAST {
    
public:

    MAST();
    ~MAST();
    void generate(std::ifstream& arquivoEntrada);
    STATE *FST;
    
private:
    // STATE *currentState;
    // STATE *newState;
    // STATE *lastState;
    
    // void addTransition(char symbol);
    // void addFinalState();
    // void reset();
    std::map<STATE *, int> MinimalTranducerStatesDictionary;
    void clearState(STATE *state);
    void addTransition(STATE *state, char symbol, STATE *newState);
    void setFinalState(STATE *state, bool isFinal);
    void setOutput(STATE *state, char c, std::string output);
    std::string output(STATE *state, char symbol);
    STATE *findMinimized(STATE *state);
    bool isFinal(STATE *state);
    
}; //class

#endif /* MAST_H */
