#include "auto_complete_trie.h"


void AutoComplete::execute(std::string pathToOrdenatedWords, unsigned int maxLevenshteinDistance) {
   
    //////////////////////////////////////////////////////////////
    auto start_ind = std::chrono::high_resolution_clock::now(); //
    //////////////// START OF TIME COUNTING //////////////////////

    Trie trie;
    STATE *st_mast = trie.initialState;

    std::size_t nStates = trie.generate(pathToOrdenatedWords);
    
    ///////////// END OF TIME COUNTING ///////////////////////////
    auto stop_ind = std::chrono::high_resolution_clock::now(); ///
    //////////////////////////////////////////////////////////////

    #ifdef _WIN32
        if(system("cls")) return;
    #else
        if(system("clear")) return;

    #endif

    auto duration_ind = std::chrono::duration_cast<std::chrono::milliseconds>(stop_ind - start_ind);
    auto memoryInfo = getMemoryUsage();
    bool useLevenshtein = true;

    std::cout << "\n\nAutomatic completion for the English language dictionary with word suggestions up to 1 character apart (levenshtein)\n" << std::endl;
    std::cout << "Data structure: " << "\033[32m" <<  "TRIE" <<  "\033[0m" << "." << std::endl;
    std::cout << "PID: " << "\033[32m" << memoryInfo.second << "\033[0m" << "." << std::endl;
    std::cout << "Number of words: " << "\033[32m" << trie.nWords << " words" << "\033[0m" << "." << std::endl;
    std::cout << "Number of states: " << "\033[32m" << nStates << " states" << "\033[0m" << "." << std::endl;
    std::cout << "Memory usage: " << "\033[32m" << memoryInfo.first << " bytes" << "\033[0m" << "." << std::endl;
    std::cout << "Index creation time: " << "\033[32m" << duration_ind.count() << " milliseconds" << "\033[0m" << "." << std::endl;
    std::cout << "\n\nType the desired word. Press \"SPACE\" to toggle Levenshtein Algorithm. Press 0, 1, 2 or 3 to change Levenshtein distance. Press \"ESC\" or \"ENTER\" to exit." << std::endl;

    std::cout << "\nLevenshtein Algorithm: ";
    if(useLevenshtein) std::cout << "\033[32m" << "ON" << "\033[0m" << std::endl;
    else std::cout << "\033[31m" << "OFF" << "\033[0m" << std::endl;

    std::cout << "Levenshtein Distance: ";
    if(useLevenshtein) std::cout << "\033[32m" << maxLevenshteinDistance << "\033[0m" << std::endl;
    else std::cout << "\033[31m" << "-" << "\033[0m" << std::endl;

    std::cout << "\n\tINPUT: ";


    char c;
    std::string input;
    std::string lWord, rWord;
    std::vector<std::string> bagOfWords;
    STATE_LEV *st_lev;
    std::size_t count;

    while(true) {
        c = getch();
        if (c == 27 || c == '\n') break; // ESC or ENTER

        else if(c == 127 && input.size() > 0) {
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

        else if(c == '3') {
            maxLevenshteinDistance = 3;
        }
        
        else if(c != 127 && c != 27 && c != '\n' && c != ' ' && c != '0' && c != '1' && c != '2' && c != '3') {
            input += c;
        }

        else continue;

        #ifdef _WIN32
            if(system("cls")) return;
        #else
            if(system("clear")) return;
        #endif
        
        std::cout << "\n\nAutomatic completion for the English language dictionary with word suggestions up to 1 character apart (levenshtein)\n" << std::endl;
        std::cout << "Data structure: " << "\033[32m" <<  "TRIE" <<  "\033[0m" << "." << std::endl;
        std::cout << "PID: " << "\033[32m" << memoryInfo.second << "\033[0m" << "." << std::endl;
        std::cout << "Number of words: " << "\033[32m" << trie.nWords << " words" << "\033[0m" << "." << std::endl;
        std::cout << "Number of states: " << "\033[32m" << nStates << " states" << "\033[0m" << "." << std::endl;
        std::cout << "Memory usage: " << "\033[32m" << memoryInfo.first << " bytes" << "\033[0m" << "." << std::endl;
        std::cout << "Index creation time: " << "\033[32m" << duration_ind.count() << " milliseconds" << "\033[0m" << "." << std::endl;
        std::cout << "\n\nType the desired word. Press \"SPACE\" to toggle Levenshtein Algorithm. Press 0, 1, 2 or 3 to change Levenshtein distance. Press \"ESC\" or \"ENTER\" to exit." << std::endl;

        std::cout << "\nLevenshtein Algorithm: ";
        if(useLevenshtein) std::cout << "\033[32m" << "ON" << "\033[0m" << std::endl;
        else std::cout << "\033[31m" << "OFF" << "\033[0m" << std::endl;

        std::cout << "Levenshtein Distance: ";
        if(useLevenshtein) std::cout << "\033[32m" << maxLevenshteinDistance << "\033[0m" << std::endl;
        else std::cout << "\033[31m" << "-" << "\033[0m" << std::endl;

        if(input.size() != 0) {
            std::cout << "\n\tINPUT: " << "\033[32m" << input << "\033[0m" << std::endl;
        }
        else {
            std::cout << "\n\tINPUT: ";
            continue;
        }

        lWord = "";
        rWord = "";
        bagOfWords.clear();

        if(useLevenshtein) {
            //////////////////////////////////////////////////////////////
            auto start_aut = std::chrono::high_resolution_clock::now(); //
            //////////////// START OF TIME COUNTING //////////////////////
        
            LevenshteinAutomaton lev(input, maxLevenshteinDistance);
            lev.generate();
            st_mast = trie.initialState;
            st_lev = lev.initialState;
            dfs(st_mast, st_lev, lWord, rWord, bagOfWords, useLevenshtein);
                
            ///////////// END OF TIME COUNTING ///////////////////////////
            auto stop_aut = std::chrono::high_resolution_clock::now(); ///
            //////////////////////////////////////////////////////////////

            auto duration_aut = std::chrono::duration_cast<std::chrono::microseconds>(stop_aut - start_aut);
            std::cout << "\nAutocomplete run time: " << "\033[32m" << duration_aut.count() << " microseconds" << "\033[0m" << "." << std::endl;

        }

        else {

            for(char c: input) {
                if(st_mast->transictions.find(c) == st_mast->transictions.end()) {
                    break;
                }

                lWord += c;
                st_mast = st_mast->transictions[c].second;
            LevenshteinAutomaton lev(input, maxLevenshteinDistance);
            lev.generate();
            st_mast = trie.initialState;
            st_lev = lev.initialState;
            dfs(st_mast, st_lev, lWord, rWord, bagOfWords, useLevenshtein);
                
            std::cout << "\nAutocomplete run time: " << "-" << "\033[0m" << "." << std::endl;

        }

        std::cout << "Suggestions (total: " << "\033[32m" << bagOfWords.size() << " word(s)" << "\033[0m" << "):\n" << std::endl;

        count = 0;

        for(auto word: bagOfWords) {
            std::cout << "\t(" << ++count << ") " << word << std::endl;
        }

        if(bagOfWords.size() == 0) {
            std::cout << "\t(" << "\033[31m" << "without suggestion ..." << "\033[0m" << ")" << std::endl;
        }        
    }

    return;
}


void AutoComplete::dfs(STATE *st_mast, STATE_LEV *st_lev, std::string &lWord, std::string rWord, std::vector<std::string> &bagOfWords, bool useLevenshtein) {

    if(st_mast->isFinal && (st_lev->isMatch || !useLevenshtein)) {
        bagOfWords.push_back(lWord + rWord);
    }

    if(st_lev->transitions['*'] == st_lev) {
        return;
    }

    for(auto transictionPair: st_mast->transictions) {
        STATE *nextState = transictionPair.second.second;
        STATE_LEV *nextStateLev;

        if(st_lev->transitions.find(transictionPair.first) == st_lev->transitions.end()) {
            nextStateLev = st_lev->transitions['*'];
        }

        else {
            nextStateLev = st_lev->transitions[transictionPair.first];
        }

        dfs(nextState, nextStateLev, lWord, rWord + transictionPair.first, bagOfWords, useLevenshtein);
    }

    return;
}