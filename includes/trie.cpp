#include "trie.h"


Trie::Trie() {
    initialState = new STATE();
    states[initialState] = 0;
}

void Trie::setTransition(STATE *state, char c, unsigned int value, STATE *nextState) {
    state->transactions[c] = std::make_pair(value, nextState);
}

void Trie::setFinal(STATE *state, bool isFinal) {
    state->isFinal = isFinal;
}

STATE * Trie::includeState(STATE *s) {
    
    STATE *r = new STATE();
    r->isFinal = s->isFinal;
    
    for(auto &transictionPair: s->transactions) {
        r->transactions[transictionPair.first] = transictionPair.second;
    }

    states[r] = nStates++;

    return r;
}

void Trie::cleanState(STATE *state) {
    state->isFinal = false;
    state->transactions.clear();
}

void Trie::printDigraph(const std::string& graphVizFolder) {

    std::ofstream digraph(graphVizFolder + "/poc_trie.dot");
    digraph << "digraph G {\n";
    digraph << "rankdir=LR;\n";
    digraph << "node [shape=circle];\n";
    digraph <<  "ini [shape=point];\n";
    digraph << "ini -> q" << states[initialState] << ";\n";

    for(auto &state : states) {
        digraph << "\tq" << state.second << " [label=\"q" << state.second << "\"];\n";
        if(state.first->isFinal) {
            digraph << "\tq" << state.second << " [shape=doublecircle];\n";
            digraph << "\tq" << state.second << " [style=filled fillcolor=gray];\n";
        }
    }

    for(auto &state : states) {
        for(auto &transition : state.first->transactions) {
            digraph << "\tq" << state.second << " -> q" << states[transition.second.second] << " [label=\"" << transition.first << " / " << transition.second.first << "\"];\n";
        }
    }

    digraph << "}\n";
}

std::size_t Trie::generate(const std::string& filePath) {
    
    std::ifstream ordenatedWords(filePath);

    if (!ordenatedWords.is_open()) {
        std::cout << "Error opening the file for reading." << std::endl;
        return 0;
    }

    std::string previousWord = "";
    std::string currentWord;
    std::size_t prefixLengthPlus1;

    for(auto &tempState : tempStates) {
        tempState = new STATE();
    }

    while(std::getline(ordenatedWords, currentWord)) {
        nWords++;
        prefixLengthPlus1 = 0;

        while(prefixLengthPlus1 < previousWord.size() && prefixLengthPlus1 < currentWord.size() && currentWord[prefixLengthPlus1] == previousWord[prefixLengthPlus1]) {
                prefixLengthPlus1 += 1;
        }

        for(std::size_t i = previousWord.size(); i > prefixLengthPlus1; i--) {
            setTransition(tempStates[i-1], previousWord[i-1], 0, includeState(tempStates[i]));
        }

        for(std::size_t i = prefixLengthPlus1; i < currentWord.size(); i++) {
            cleanState(tempStates[i+1]);
            setTransition(tempStates[i], currentWord[i], 0, tempStates[i+1]);
        }

        setFinal(tempStates[currentWord.size()], true);
        previousWord = currentWord;
    }

    ordenatedWords.close();


    for(std::size_t i = previousWord.size(); i > 0; i--) {
        setTransition(tempStates[i-1], previousWord[i-1], 0, includeState(tempStates[i]));
    }

    initialState = tempStates[0];

    return nStates;
}