#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <fstream>

const int MAX_WORD_SIZE = 100;

class State {
public:
    std::unordered_map<char, State*> transitions;
    bool isFinal;
    std::set<std::string> outputs;

    State() : isFinal(false) {}

    State* getTransition(char c) {
        if(transitions.find(c) != transitions.end())
            return transitions[c];
        return nullptr;
    }

    void setTransition(char c, State* s) {
        transitions[c] = s;
    }
};

class Transducer {
private:
    std::unordered_map<std::string, State*> statesDictionary;
    State* tempStates[MAX_WORD_SIZE];
    State* initialState;

    State* findMinimized(State* s) {
        for(auto& pair : statesDictionary) {
            if(pair.second->outputs == s->outputs)
                return pair.second;
        }
        State* newState = new State(*s);
        statesDictionary[s->outputs] = newState;
        return newState;
    }

public:
    Transducer() {
        for(int i = 0; i < MAX_WORD_SIZE; i++) {
            tempStates[i] = new State();
        }
    }

    void processWords(const std::string& filename) {
        std::ifstream input(filename);
        if(!input.is_open()) {
            std::cerr << "Erro ao abrir o arquivo!" << std::endl;
            return;
        }

        std::string previousWord = "";
        std::string currentWord;

        while(std::getline(input, currentWord)) {
            // Como exemplo simples, a saída é a própria palavra.
            std::string currentOutput = currentWord;

            // TODO: Adicionar lógica de transição, saída e manipulação de estados.

            previousWord = currentWord;
        }
        input.close();
    }

    void printTransducer(std::ostream& output) {
        output << "digraph Transducer {\n";
        output << "\trankdir=LR;\n";
        output << "\tnode [shape=circle];\n";

        for (auto& pair : statesDictionary) {
            State* s = pair.second;

            if (s->isFinal) {
                output << "\t\"" << pair.first << "\" [shape=doublecircle];\n";
            }

            for (auto& trans : s->transitions) {
                output << "\t\"" << pair.first << "\" -> \"" << trans.second->outputs << "\" "
                       << "[label=\"" << trans.first << "/" << trans.second->outputs << "\"];\n";
            }
        }

        output << "}\n";
    }
};

int main() {
    Transducer t;
    t.processWords("input.txt");  // Supondo que o arquivo se chame input.txt
    t.printTransducer(std::cout);  // Imprime o transdutor no formato DOT na saída padrão.
    return 0;
}
