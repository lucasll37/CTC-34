#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include "levenshtein.h"



int main() {

    LevenshteinAutomaton lev("deodado", 2);
    lev.generate();
    
    std::string candidate = "waofa";

    std::cout << "Candidate: " << candidate << std::endl;

    STATE *state = lev.DFA;

    for(char c : candidate) {
        if(state->transitions.find(c) == state->transitions.end()) {
            state = state->transitions['*'];
            std::cout << "Transition: " << '*' << std::endl;
        }

        else {
            state = state->transitions[c];
            std::cout << "Transition: " << c << std::endl;

        }
    }

    std::cout << "Is match: " << (state->isMatch ? "true" : "false") << std::endl;


    return 0;
}



