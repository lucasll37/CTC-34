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
            digraph << "\tq" << state.second << " -> q" << states[transition.second.second] << " [label=\"" << transition.first << " / " << transition.second.first << "\"];\n";
        }
    }

    digraph << "}\n";
}

std::string MinAcyclicSubseqTransducers::output(STATE *state, char c) {
    return state->transictions[c].first; // sempre vai dar certo????
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
    std::string previousOutput = "";
    std::string currentWord;
    std::string currentOutput;
    std::string commonPrefix;
    std::string wordSuffix;
    std::size_t prefixLengthPlus1;
    std::size_t aux;

    ///////////////////////
    std::unordered_map<std::string, std::string> outputMap;

    outputMap["january"] = "1";
    outputMap["july"] = "1111111";
    outputMap["june"] = "111111";
    ///////////////////////
    

    while(std::getline(ordenatedWords, currentWord)) {
        currentOutput = outputMap[currentWord];
        // currentOutput = std::to_string(nWords);
        nWords++;
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

        aux = 0;

        while(aux < previousOutput.size() && aux < currentOutput.size() && currentOutput[aux] == previousOutput[aux]) {
            aux++;
        }

        commonPrefix = currentOutput.substr(0, aux);
        wordSuffix = currentOutput.substr(aux, currentOutput.size());

        std::cout << "previousWord: " << previousWord << " ";
        std::cout << "previousOutput: " << previousOutput << " " << std::endl;
        std::cout << "currentWord: " << currentWord << " ";
        std::cout << "currentOutput: " << currentOutput << " " << std::endl;
        std::cout << "commonPrefix: " << commonPrefix << " ";
        std::cout << "wordSuffix: " << wordSuffix << "\n\n" <<std::endl;

        setOutput(tempStates[aux], currentWord[aux], commonPrefix);
        
        previousWord = currentWord;
        previousOutput = currentOutput;
    }

    ordenatedWords.close();


    for(std::size_t i = previousWord.size(); i > 0; i--) {
        setTransition(tempStates[i-1], previousWord[i-1], findMinimized(tempStates[i]));
    }

    initialState = findMinimized(tempStates[0]);

    return;
}
