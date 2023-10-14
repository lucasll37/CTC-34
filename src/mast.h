#ifndef EXAME_MAST_H
#define EXAME_MAST_H

#include <iostream>
#include <map>
#include <fstream>

struct STATE {
    std::map<char, STATE *> transitions;
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
    

}; //class

#endif /* MAST_H */
