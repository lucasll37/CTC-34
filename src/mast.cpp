#include "mast.h"

MAST::MAST(void) {
    FST = new STATE();
    FST->isFinal = true;
}

MAST::~MAST(void) {
    delete FST;
}

void MAST::_clearState(STATE *state) {
    state->transitions.clear();
    state->isFinal = false;
}

void MAST::_addTransition(STATE *state, char symbol, STATE *newState) {
    state->transitions[symbol] = new TRANSICTION();
    state->transitions[symbol]->nextState = newState;
}

void MAST::_setFinalState(STATE *state, bool isFinal) {
    state->isFinal = isFinal;
}

void MAST::_setOutput(STATE *state, int output) {
    // state->transitions[symbol]->output = output;
}

int MAST::_output(STATE *state, char symbol) {
    return state->transitions[symbol]->output;
}



void MAST::generate(std::ifstream &inputFile) {

    MAST::FST->isFinal = false;
    std::string line;

    std::map<std::string, int> MinimalTranducerStatesDictionary;
    std::vector<STATE* > TempStates(1);
    std::string previousWord, currentWord, currentOutput, wordSuffix, commonPrefix;
    std::string tempString;
    std::set<std::string> tempSet;
    char c;
    int count;

    count = 0;

    while (std::getline(inputFile, line)) {
        TempStates[count] = new STATE();
        _clearState(TempStates[count]);
        count++;
    }

    previousWord = "";

    int charIndex;

    while (std::getline(inputFile, line)) {
        
        if(count == 0) {
            currentWord = line;
            count++;
            continue;
        }

        previousWord = currentWord;
        currentWord = line;
        charIndex = 0;


        while(charIndex < currentWord.length() && charIndex < previousWord.length() && currentWord[charIndex] == previousWord[charIndex]) {
            charIndex++;
        }

        for(int i = previousWord.length(); i > charIndex; i--) {
            _addTransition(TempStates[i-1], previousWord[i], TempStates[i]);
        }

        for(int i = charIndex+1; i <= currentWord.length(); i++) {
            _clearState(TempStates[i]);
            _addTransition(TempStates[i-1], currentWord[i], TempStates[i]);
        }

        if(currentOutput == previousWord) {
            _setFinalState(TempStates[currentWord.length()], true);
            _setOutput(TempStates[currentWord.length()], 0);
        }

        for(int i = 0; i <= charIndex; i++) {
            commonPrefix = _output(TempStates[i], previousWord[i]);

        }

        count++;

        if(count == 10) {
            break;
        }
    }
}