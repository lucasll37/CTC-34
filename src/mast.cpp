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
    std::map<STATE *, unsigned int> states;
    STATE *tempStates[MAX_WORD_SIZE];
    STATE *fisrtState;
    // unsigned int nStates = 0;

    public:

        void setTransition(STATE *state, char c, unsigned int value, STATE *nextState) {
            state->transactions[c] = std::make_pair(value, nextState);
        }

        STATE *getNextStateTransition(STATE *state, char c) {
            if(state->transactions.find(c) == state->transactions.end()) {
                return nullptr;
            }

            return state->transactions[c].second;
        }

        unsigned int getValueTransition(STATE *state, char c) {
            if(state->transactions.find(c) == state->transactions.end()) {
                return 0;
            }

            return state->transactions[c].first;
        }

        void setFinal(STATE *state, bool isFinal) {
            state->isFinal = isFinal;
        }

        STATE *findMinimized(STATE *s) {
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

                states[r] = states.size();
            }

            return r;
        }

        void printDigraph() {

            std::ofstream digraph("test.dot");

            digraph << "digraph G {\n";
            digraph << "rankdir=LR;\n";
            digraph << "node [shape=circle];\n";

            for(auto &state : states) {
                digraph << "\tq" << state.second << " [label=\"q" << state.second << "\"];\n";
            }

            for(auto &state : states) {
                for(auto &transition : state.first->transactions) {
                    digraph << "\tq" << state.second << " -> q" << states[transition.second.second] << " [label=\"" << transition.first << " / " << transition.second.first << "\"];\n";
                }
            }

            digraph << "}\n";
        }

        void generate(std::ifstream ordenatedWords) {
            std::string previousWord = "";
            std::string currentWord;
            bool fistLine = true;

            for(auto &tempState : tempStates) {
                tempState = new STATE();
            }

            while(std::getline(ordenatedWords, currentWord)) {
                if(fistLine) {
                    previousWord = currentWord;
                    fistLine = false;
                    continue;
                }

                unsigned int prefixLengthPlus1 = 0;

                for(unsigned int i = 0; i < currentWord.length(); i++) {
                    if(currentWord[i] != previousWord[i]) {
                        prefixLengthPlus1 = i + 1;
                        break;
                    }
                }

                for(int i = currentWord.size(); i > prefixLengthPlus1; i--) {
                    setTransition(tempStates[i-1], currentWord[i-1], 0, findMinimized(tempStates[i]));
                }

                previousWord = currentWord;
            }


        }

};