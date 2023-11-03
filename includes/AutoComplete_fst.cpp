#include "AutoComplete_fst.h"

void AutoComplete::execute(std::string pathToOrdenatedWords, unsigned int maxLevenshteinDistance){
   
    //////////////////////////////////////////////////////////////
    auto start_ind = std::chrono::high_resolution_clock::now(); //
    //////////////// START OF TIME COUNTING //////////////////////
    FiniteStateTransducer fst;
    LevenshteinAutomaton *lev;

    STATE *st_mast;

    fst.generate(pathToOrdenatedWords);
    
    ///////////// END OF TIME COUNTING ///////////////////////////
    auto stop_ind = std::chrono::high_resolution_clock::now(); ///
    //////////////////////////////////////////////////////////////

    #ifdef _WIN32
        if(system("cls")) return;
    #else
        if(system("clear")) return;

    #endif

    auto duration_ind = std::chrono::duration_cast<std::chrono::milliseconds>(stop_ind - start_ind);
    bool useLevenshtein = true;
    unsigned int memoryUsage = fst.nEdges * sizeof(std::pair<std::string, STATE *>) + fst.nStates * ( sizeof(bool) + sizeof(std::string) );
    auto fileSize = std::filesystem::file_size(pathToOrdenatedWords);

    std::cout << "\n\nAutomatic completion for the English language dictionary with word suggestions up to n character(s) apart (levenshtein algorithm)\n" << std::endl;
    std::cout << "Data structure: " << "\033[32m" <<  "Finite State Transducer (build with MAST algorithm)" <<  "\033[0m" << std::endl;
    std::cout << "File size: " << "\033[32m" << fileSize / 1024 << " kB" << "\033[0m" << "." << std::endl;
    std::cout << "Number of words: " << "\033[32m" << fst.nWords << " words" << "\033[0m" << "." << std::endl;
    std::cout << "Number of states: " << "\033[32m" << fst.nStates << " states" << "\033[0m" << "." <<  std::endl;
    std::cout << "Number of edges: " << "\033[32m" << fst.nEdges << " edges" << "\033[0m" << "." <<  std::endl;
    std::cout << "Memory usage: " << "\033[32m" << memoryUsage / 1024 << " kB" << "\033[0m" << "." <<  std::endl;
    std::cout << "Index creation time: " << "\033[32m" << duration_ind.count() << " milliseconds" << "\033[0m" << "." <<  std::endl;
    std::cout << "\n\nType the desired word. Press \"SPACE\" to toggle Levenshtein Algorithm. Press 0, 1 or 2 to change Levenshtein distance. Press \"ESC\" or \"ENTER\" to exit." << std::endl;

    std::cout << "\nLevenshtein Algorithm: ";
    if(useLevenshtein) std::cout << "\033[32m" << "ON" << "\033[0m" << std::endl;
    else std::cout << "\033[31m" << "OFF" << "\033[0m" << std::endl;

    std::cout << "Levenshtein Distance: ";
    if(useLevenshtein) std::cout << "\033[32m" << maxLevenshteinDistance << "\033[0m" << std::endl;
    else std::cout << "\033[31m" << "-" << "\033[0m" << std::endl;

    std::cout << "\n\tINPUT: ";

    char c;
    std::string input, index, lWord, rWord;
    std::vector<std::pair<std::string, std::string>> bagOfWords;
    STATE_LEV *st_lev;

    while(true) {
        c = getch();
        if (c == 27 || c == '\n') break; // ESC or ENTER

        else if(c == 127 && input.size() > 0) { // BACKSPACE
            input.pop_back();
        }

        else if(c == ' ') {
            useLevenshtein = !useLevenshtein;
        }

        else if(c == '0') {
            maxLevenshteinDistance = 0;
        }

        else if(c == '1') {
            maxLevenshteinDistance = 1;
        }

        else if(c == '2') {
            maxLevenshteinDistance = 2;
        }
        
        if(!std::isdigit(c) && c!=' ' && c!=127 && c!=27 && c!='\n' && input.size() < MAX_WORD_SIZE) {
            input += c;
        }
        
        #ifdef _WIN32
            if(system("cls")) return;
        #else
            if(system("clear")) return;
        #endif
        
        std::cout << "\n\nAutomatic completion for the English language dictionary with word suggestions up to n character(s) apart (levenshtein algorithm)\n" << std::endl;
        std::cout << "Data structure: " << "\033[32m" <<  "Finite State Transducer (build with MAST algorithm)" <<  "\033[0m" << std::endl;
        std::cout << "File size: " << "\033[32m" << fileSize / 1024 << " kB" << "\033[0m" << "." << std::endl;
        std::cout << "Number of words: " << "\033[32m" << fst.nWords << " words" << "\033[0m" << "." << std::endl;
        std::cout << "Number of states: " << "\033[32m" << fst.nStates << " states" << "\033[0m" << "." <<  std::endl;
        std::cout << "Number of edges: " << "\033[32m" << fst.nEdges << " edges" << "\033[0m" << "." <<  std::endl;
        std::cout << "Memory usage: " << "\033[32m" << memoryUsage / 1024 << " kB" << "\033[0m" << "." <<  std::endl;
        std::cout << "Index creation time: " << "\033[32m" << duration_ind.count() << " milliseconds" << "\033[0m" << "." <<  std::endl;
        std::cout << "\n\nType the desired word. Press \"SPACE\" to toggle Levenshtein Algorithm. Press 0, 1 or 2 to change Levenshtein distance. Press \"ESC\" or \"ENTER\" to exit." << std::endl;

        std::cout << "\nLevenshtein Algorithm: ";
        if(useLevenshtein) std::cout << "\033[32m" << "ON" << "\033[0m" << std::endl;
        else std::cout << "\033[31m" << "OFF" << "\033[0m" << std::endl;

        std::cout << "Levenshtein Distance: ";
        if(useLevenshtein) std::cout << "\033[32m" << maxLevenshteinDistance << "\033[0m" << std::endl;
        else std::cout << "\033[31m" << "-" << "\033[0m" << std::endl;

        if(input.size() != 0) {
            std::cout << "\n\tINPUT: " << "\033[1;37;42m" << input << "\033[0m" << std::endl;

        }
        else {
            std::cout << "\n\tINPUT: ";
            continue;
        }

        st_mast = fst.initialState;
        lWord = "";
        rWord = "";
        index = "";
        bagOfWords.clear();

        //////////////////////////////////////////////////////////////
        auto start_aut = std::chrono::high_resolution_clock::now(); //
        //////////////// START OF TIME COUNTING //////////////////////

        if(useLevenshtein) {    
            lev = new LevenshteinAutomaton(input, maxLevenshteinDistance);
        }

        else {
            lev = new LevenshteinAutomaton("A", 0);

            for(char c: input) {
                if(st_mast->transictions.find(c) != st_mast->transictions.end()) {
                    index += st_mast->transictions[c].first;
                    lWord += c;
                    st_mast = st_mast->transictions[c].second;
                }

                else break;
            }
        }

        lev->generate();
        st_lev = lev->initialState;    

        dfs(st_mast, st_lev, input, lWord, rWord, index, bagOfWords, useLevenshtein);
        delete lev;

        ///////////// END OF TIME COUNTING ///////////////////////////
        auto stop_aut = std::chrono::high_resolution_clock::now(); ///
        //////////////////////////////////////////////////////////////

        auto duration_aut = std::chrono::duration_cast<std::chrono::microseconds>(stop_aut - start_aut);
        std::cout << "\nAutocomplete run time: " << "\033[32m" << duration_aut.count() << " microseconds" << "\033[0m" << "." << std::endl;
        if(!useLevenshtein && bagOfWords.size() == MAX_WORD_WITHOUT_LEV) {
            std::cout << "Suggestions (total: more than " << "\033[32m" << MAX_WORD_WITHOUT_LEV << " word(s)" << "\033[0m" << "):\n" << std::endl;
        }

        else {
            std::cout << "Suggestions (total: " << "\033[32m" << bagOfWords.size() << " word(s)" << "\033[0m" << "):\n" << std::endl;
        }

        std::cout << "\t(" << "\033[1;34m" << "INDEX" << "\033[0m" << ") "<< "\033[1;34m" << "WORD" << "\033[0m\n" << std::endl;

        for(auto wordPair: bagOfWords) {
            std::cout << "\t(" << wordPair.first << ") " << wordPair.second << std::endl;
        }

        if(bagOfWords.size() == 0) {
            std::cout << "\t(" << "\033[31m" << "without suggestion ..." << "\033[0m" << ")" << std::endl;
        }        
    }

    return;
}

void AutoComplete::dfs(STATE *st_mast,
                       STATE_LEV *st_lev,
                       std::string &input,
                       std::string &lWord,
                       std::string rWord,
                       std::string index,
                       std::vector<std::pair<std::string, std::string>> &bagOfWords,
                       bool useLevenshtein) {

    if(!useLevenshtein && bagOfWords.size() == MAX_WORD_WITHOUT_LEV) return;

    std::string word = lWord + rWord;

    if(st_mast->isFinal && (word >= input || useLevenshtein) && (st_lev->isMatch || !useLevenshtein)) {
        bagOfWords.push_back(std::make_pair(index + st_mast->output, word));
    }

    if(st_lev->transitions['*'] == st_lev && useLevenshtein) {
        return;
    }

    STATE *nextState;
    STATE_LEV *nextStateLev;
    std::string newRWord;
    std::string newIndex;

    for(auto transictionPair: st_mast->transictions) {
        nextState = transictionPair.second.second;
        newRWord = rWord + transictionPair.first;
        newIndex = index + transictionPair.second.first;

        if(st_lev->transitions.find(transictionPair.first) != st_lev->transitions.end()) {
            nextStateLev = st_lev->transitions[transictionPair.first];
        }

        else if (st_lev->transitions.find('*') != st_lev->transitions.end()) {
            nextStateLev = st_lev->transitions['*'];
        }

        else {
            std::cout << "ERROR: Levenshtein Automaton is not well formed." << std::endl;
            break;
        }

        dfs(nextState, nextStateLev, input, lWord, newRWord, newIndex, bagOfWords, useLevenshtein);
    }

    return;
}