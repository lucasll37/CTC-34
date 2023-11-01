#include "minAcyclicSubseqTransducers.h"


MinAcyclicSubseqTransducers::MinAcyclicSubseqTransducers() {
    for(auto &tempState : tempStates) {
        tempState = new STATE();
    }
}

MinAcyclicSubseqTransducers::~MinAcyclicSubseqTransducers() {
    for(auto &tempState : tempStates) {
        delete tempState;
    }

    for(auto &state : states) {
        delete state.first;
    }
}

void MinAcyclicSubseqTransducers::setTransition(STATE *state, char c, STATE *nextState) {
    if(state->transictions.find(c) == state->transictions.end()) {
        state->transictions[c] = std::make_pair("", nextState);
    }

    else {
        state->transictions[c].second = nextState;
    }
}

void MinAcyclicSubseqTransducers::setFinal(STATE *state, bool isFinal) {
    state->isFinal = isFinal;
}

STATE *MinAcyclicSubseqTransducers::findMinimized(STATE *s) {
    
    STATE *r = nullptr;


    if(states.find(s) != states.end()) {
        auto it = states.find(s);
        r = it->first;
    }

    else {
        r = new STATE();
        r->isFinal = s->isFinal;
        
        for(auto &transictionPair: s->transictions) {
            r->transictions[transictionPair.first] = transictionPair.second;
        }

        states[r] = nStates++;
        nEdges += r->transictions.size();
    }

    return r;
}

void MinAcyclicSubseqTransducers::cleanState(STATE *state) {
    state->isFinal = false;
    state->transictions.clear();
}

void MinAcyclicSubseqTransducers::printDigraph(const std::string& graphVizFolder) {

    std::ofstream digraph(graphVizFolder + "/poc_mast.dot");
    digraph << "digraph G {\n";
    digraph << "rankdir=LR;\n";
    digraph << "charset=\"utf8\";\n";
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
        for(auto &transition : state.first->transictions) {
            
            if(transition.second.first != "") {
                digraph << "\tq" << state.second << " -> q" << states[transition.second.second] << " [label=\"" << transition.first << " / " << transition.second.first << "\"];\n";
            }

            else {
                digraph << "\tq" << state.second << " -> q" << states[transition.second.second] << " [label=\"" << transition.first << "\"];\n";
            }
        }
    }

    digraph << "}\n";
}

std::string MinAcyclicSubseqTransducers::output(STATE *state, char c) {
    return state->transictions[c].first;
}

void MinAcyclicSubseqTransducers::setOutput(STATE *state, char c, std::string output) {
    state->transictions[c].first = output;
}

void MinAcyclicSubseqTransducers::generate(const std::string &filePath) {    
    std::ifstream ordenatedWords(filePath);
    if (!ordenatedWords.is_open()) {
        std::cout << "Error opening the file for reading." << std::endl;
        return;
    }
    
    std::string previousWord = "";
    std::string currentWord;
    std::string currentOutput;
    std::string outputTemp;
    std::string commonPrefix;
    std::string wordSuffix;
    std::size_t prefixLengthPlus1;
    std::size_t aux;
   
    while(std::getline(ordenatedWords, currentWord)) {
        currentOutput = std::to_string(++nWords);
        prefixLengthPlus1 = 0;

        while(prefixLengthPlus1 < previousWord.size() && prefixLengthPlus1 < currentWord.size() && currentWord[prefixLengthPlus1] == previousWord[prefixLengthPlus1]) {
                prefixLengthPlus1++;
        }

        for(std::size_t i = previousWord.size(); i > prefixLengthPlus1; i--) {
            setTransition(tempStates[i-1], previousWord[i-1], findMinimized(tempStates[i]));
        }

        for(std::size_t i = prefixLengthPlus1; i < currentWord.size(); i++) {
            cleanState(tempStates[i+1]);
            setTransition(tempStates[i], currentWord[i], tempStates[i+1]);
        }

        setFinal(tempStates[currentWord.size()], true);

        for (std::size_t i = 0; i < prefixLengthPlus1; i++) {
            outputTemp = output(tempStates[i], currentWord[i]);
            aux = 0;

            while(aux < currentOutput.size() && aux < outputTemp.size() && currentOutput[aux] == outputTemp[aux]) {
                aux++;
            }

            commonPrefix = outputTemp.substr(0, aux);
            wordSuffix = outputTemp.substr(aux, outputTemp.size());
            setOutput(tempStates[i], currentWord[i], commonPrefix);

            for(auto &transictionPair: tempStates[i+1]->transictions) {
                setOutput(tempStates[i+1], transictionPair.first, wordSuffix + output(tempStates[i+1], transictionPair.first));
            }

            currentOutput = currentOutput.substr(aux, currentOutput.size());
        }

        setOutput(tempStates[prefixLengthPlus1], currentWord[prefixLengthPlus1], currentOutput);
        previousWord = currentWord;
    }

    ordenatedWords.close();

    for(std::size_t i = previousWord.size(); i > 0; i--) {
        setTransition(tempStates[i-1], previousWord[i-1], findMinimized(tempStates[i]));
    }

    initialState = findMinimized(tempStates[0]);

    return;
}
