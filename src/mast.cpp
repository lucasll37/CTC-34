#include "mast.h"


MAST::MAST() {
    initialState = new STATE();
    states[initialState] = 0;
}

void MAST::setTransition(STATE *state, char c, unsigned int value, STATE *nextState) {
    state->transactions[c] = std::make_pair(value, nextState);
}

STATE * MAST::getNextStateTransition(STATE *state, char c) {
    if(state->transactions.find(c) == state->transactions.end()) {
        return nullptr;
    }

    return state->transactions[c].second;
}

unsigned int MAST::getValueTransition(STATE *state, char c) {
    if(state->transactions.find(c) == state->transactions.end()) {
        return 0;
    }

    return state->transactions[c].first;
}

void MAST::setFinal(STATE *state, bool isFinal) {
    state->isFinal = isFinal;
}

STATE * MAST::findMinimized(STATE *s) {
    STATE *r = nullptr;
    bool isEqual;

    for(auto &state: states) {

        if(s->isFinal != state.first->isFinal) {
            continue;
        }

        isEqual = true;

        for(auto &transictionPair: s->transactions) {
            if(state.first->transactions.find(transictionPair.first) == state.first->transactions.end()) {
                isEqual = false;
                break;
            }
        }

        if(isEqual) {
            r = state.first;
            break;
        }
    }

    if(r == nullptr) {
        r = new STATE();
        r->isFinal = s->isFinal;
        
        for(auto &transictionPair: s->transactions) {
            r->transactions[transictionPair.first] = transictionPair.second;
        }

        states[r] = nStates++;
    }

    return r;
}

void MAST::cleanState(STATE *state) {
    state->isFinal = false;
    state->transactions.clear();
}

void MAST::printDigraph() {

    std::ofstream digraph("./graphs/mast.dot");

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

void MAST::generate(std::ifstream ordenatedWords) {
    std::string previousWord = "";
    std::string currentWord;
    std::size_t prefixLengthPlus1;

    for(auto &tempState : tempStates) {
        tempState = new STATE();
    }

    while(std::getline(ordenatedWords, currentWord)) {

        prefixLengthPlus1 = 0;

        while(prefixLengthPlus1 < previousWord.size() && prefixLengthPlus1 < currentWord.size() && currentWord[prefixLengthPlus1] == previousWord[prefixLengthPlus1]) {
                prefixLengthPlus1 += 1;
        }

        for(std::size_t i = previousWord.size(); i > prefixLengthPlus1; i--) {
            setTransition(tempStates[i-1], previousWord[i-1], 0, findMinimized(tempStates[i]));
        }

        for(std::size_t i = prefixLengthPlus1; i < currentWord.size(); i++) {
            cleanState(tempStates[i+1]);
            setTransition(tempStates[i], currentWord[i], 0, tempStates[i+1]);
        }

        setFinal(tempStates[currentWord.size()], true);


        previousWord = currentWord;
    }

    for(std::size_t i = currentWord.size(); i > 0; i--) {
        setTransition(tempStates[i-1], currentWord[i-1], 0, findMinimized(tempStates[i]));
    }

    initialState = findMinimized(tempStates[0]);
}
