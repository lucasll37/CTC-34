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

    std::cout << "\n\nAutomatic completion for the English language dictionary with word suggestions up to 1 character apart (levenshtein)\n" << std::endl;
    std::cout << "Data structure: " << "\033[32m" <<  "TRIE" <<  "\033[0m" << std::endl;
    std::cout << "Number of words: " << "\033[32m" << trie.nWords << " words." << "\033[0m" << std::endl;
    std::cout << "Number of states: " << "\033[32m" << nStates << " states." << "\033[0m" << std::endl;
    std::cout << "Index creation time: " << "\033[32m" << duration_ind.count() << " milliseconds." << "\033[0m" << std::endl;
    std::cout << "\n\nType the desired word. Press \"ESC\" or \"ENTER\" to exit" << std::endl;
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

        if(c == 127 && input.size() > 0) {
            input.pop_back();
        }
        
        else if(c != 127) {
            input += c;
        }
        
        else continue;

        #ifdef _WIN32
            if(system("cls")) return;
        #else
            if(system("clear")) return;
        #endif
        
        std::cout << "\n\nAutomatic completion for the English language dictionary with word suggestions up to 1 character apart (levenshtein)\n" << std::endl;
        std::cout << "Data structure: " << "\033[32m" <<  "TRIE" <<  "\033[0m" << std::endl;
        std::cout << "Number of words: " << "\033[32m" << trie.nWords << " words." << "\033[0m" << std::endl;
        std::cout << "Number of states: " << "\033[32m" << nStates << " states." << "\033[0m" << std::endl;
        std::cout << "Index creation time: " << "\033[32m" << duration_ind.count() << " milliseconds." << "\033[0m" << std::endl;
        std::cout << "\n\nType the desired word or press \"ESC\" or \"ENTER\" to exit" << std::endl;
        std::cout << "\n\tINPUT: " << "\033[32m" << input << "\033[0m" << std::endl;

        lWord = "";
        rWord = "";
        bagOfWords.clear();

        //////////////////////////////////////////////////////////////
        auto start_aut = std::chrono::high_resolution_clock::now(); //
        //////////////// START OF TIME COUNTING //////////////////////

        LevenshteinAutomaton lev(input, maxLevenshteinDistance);
        lev.generate();
        st_mast = trie.initialState;
        st_lev = lev.initialState;
        dfs(st_mast, st_lev, lWord, rWord, bagOfWords);
            
        ///////////// END OF TIME COUNTING ///////////////////////////
        auto stop_aut = std::chrono::high_resolution_clock::now(); ///
        //////////////////////////////////////////////////////////////

        auto duration_aut = std::chrono::duration_cast<std::chrono::microseconds>(stop_aut - start_aut);
        std::cout << "\nAutocomplete run time (" << "\033[32m" << duration_aut.count() << " microseconds" << "\033[0m" << "):\n" << std::endl;

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


void AutoComplete::dfs(STATE *st_mast, STATE_LEV *st_lev, std::string &lWord, std::string rWord, std::vector<std::string> &bagOfWords) {

    if(st_mast->isFinal && st_lev->isMatch) {
        bagOfWords.push_back(lWord + rWord);
    }

    if(st_lev->transitions.size() == 1 && st_lev->transitions['*'] == st_lev) {
        return;
    }

    for(auto transictionPair: st_mast->transactions) {
        STATE *nextState = transictionPair.second.second;
        STATE_LEV *nextStateLev;

        if(st_lev->transitions.find(transictionPair.first) == st_lev->transitions.end()) {
            nextStateLev = st_lev->transitions['*'];
        }

        else {
            nextStateLev = st_lev->transitions[transictionPair.first];
        }

        dfs(nextState, nextStateLev, lWord, rWord + transictionPair.first, bagOfWords);
    }

    return;
}