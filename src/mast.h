#ifndef EXAME_MAST_H
#define EXAME_MAST_H

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <set>


struct TRANSICTION {
    char symbol;
    STATE *nextState;
    int output;
};

struct STATE {
    std::map<char, TRANSICTION *> transitions;
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
    void _clearState(STATE *state);
    void _addTransition(STATE *state, char symbol, STATE *newState);
    void _setFinalState(STATE *state, bool isFinal);
    void _setOutput(STATE *state, int output);
    int _output(STATE *state, char symbol);
    
    

}; //class

#endif /* MAST_H */
