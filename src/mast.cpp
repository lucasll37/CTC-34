#include "mast.h"
#include <utility>

#define MAX_WORD_SIZE 100

MAST::MAST(void) {
    FST = new STATE();
    FST->isFinal = false;
}

MAST::~MAST(void) {
    delete FST;
}

void MAST::clearState(STATE *state) {
    state->transitions.clear();
    state->output = 0;
    state->isFinal = false;
}

void MAST::addTransition(STATE *state, char symbol, STATE *newState) {
    state->transitions[symbol].first = newState;
    state->transitions[symbol].second = "";
}

void MAST::setFinalState(STATE *state, bool isFinal) {
    state->isFinal = isFinal;
}

void MAST::setOutput(STATE *state, char symbol, std::string output) {
    state->transitions[symbol].second = output;
}

std::string MAST::output(STATE *state, char symbol) {
    return state->transitions[symbol].second;
}

bool isFinal(STATE *state) {
    return state->isFinal;
}


STATE * MAST::findMinimized(STATE *state) {
    if(MinimalTranducerStatesDictionary.find(state) == MinimalTranducerStatesDictionary.end()) {
        MinimalTranducerStatesDictionary[state] = 0;
    }

    else {
        return state;
    }
}


void MAST::generate(std::ifstream &inputFile) {

    std::string line;

    std::map<STATE *, int> MinimalTranducerStatesDictionary;
    std::vector<STATE *> tempStates(MAX_WORD_SIZE);
    std::string previousWord, currentWord, currentOutput, wordSuffix, commonPrefix;
    std::string tempString;
    std::set<std::string> tempSet;
    int count, i, j, prefixLenght;
    char c;

    for(auto &tempState: tempStates) {
        tempState = new STATE();
        clearState(tempState);
    }

    // for(auto &tempState: tempStates) {
    //     delete tempState;
    // }

    previousWord = "";

    int charIndex;

    int count = 0;

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
            addTransition(tempStates[i-1], previousWord[i-1], findMinimized(tempStates[i]));
        }

        for(int i = charIndex+1; i <= currentWord.length(); i++) {
            clearState(tempStates[i]);
            addTransition(tempStates[i-1], currentWord[i], tempStates[i]);
        }

        if(currentOutput == previousWord) {
            setFinalState(tempStates[currentWord.length()], true);
            setOutput(tempStates[currentWord.length()], 0);
        }

        for(int i = 0; i <= charIndex; i++) {
            commonPrefix = output(tempStates[i], previousWord[i]);
            wordSuffix = 'perdido!';


            for (char c = 'a'; c <= 'z'; ++c) {
                if(tempStates[i]->transitions.find(c) != tempStates[i]->transitions.end()) {
                    setOutput(tempStates[i], c, wordSuffix + output(tempStates[i], c));
                }
            }

            if(isFinal(tempStates[i])) {
                tempSet.clear();
            }

        }
        count++;

        if(count == 10) {
            break;
        }
    }
}