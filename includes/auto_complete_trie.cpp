#include "auto_complete_trie.h"

void AutoComplete::execute(void){
   
    //////////////////////////////////////////////////////////////
    auto start_ind = std::chrono::high_resolution_clock::now(); //
    //////////////// START OF TIME COUNTING //////////////////////

    // MinAcyclicSubseqTransducers mast;
    Trie mast;
    STATE *st_mast = mast.initialState;

    std::size_t nStates = mast.generate("./data/american-english.txt");
    
    ///////////// END OF TIME COUNTING ///////////////////////////
    auto stop_ind = std::chrono::high_resolution_clock::now(); ///
    //////////////////////////////////////////////////////////////

    #ifdef _WIN32
        if(system("cls")) return;
    #else
        if(system("clear")) return;

    #endif

    auto duration_ind = std::chrono::duration_cast<std::chrono::milliseconds>(stop_ind - start_ind);

    std::cout << "\n\nAuto complete for the English language with word suggestions with levenshtein distance up to 1 (one)" << std::endl;
    std::cout << "\nData structure: TRIE" << std::endl;
    std::cout << "\nNumber of states: " << nStates << " states." << std::endl;
    std::cout << "Index creation time: " << duration_ind.count() << " milliseconds." << std::endl;
    std::cout << "\n\nType the desired word or press \"ESC\" or \"ENTER\" to exit" << std::endl; 
    std::cout << "\nINPUT:\n" << std::endl;


    char c;
    std::string input;
    std::string lWord, rWord;
    std::vector<std::string> bagOfWords;
    STATE_LEV *st_lev;

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
        
        std::cout << "\n\nAuto complete for the English language with word suggestions with levenshtein distance up to 1 (one)" << std::endl;
        std::cout << "\nData structure: TRIE" << std::endl;
        std::cout << "\nNumber of states: " << nStates << " states." << std::endl;
        std::cout << "Index creation time: " << duration_ind.count() << " milliseconds." << std::endl;
        std::cout << "\n\nType the desired word or press \"ESC\" or \"ENTER\" to exit" << std::endl;
        std::cout << "\nINPUT: " << input << "\n" << std::endl;

        lWord = "";
        rWord = "";
        bagOfWords.clear();

        //////////////////////////////////////////////////////////////
        auto start_aut = std::chrono::high_resolution_clock::now(); //
        //////////////// START OF TIME COUNTING //////////////////////

        LevenshteinAutomaton lev(input, 1);
        lev.generate();
        st_mast = mast.initialState;
        st_lev = lev.initialState;
        dfs(st_mast, st_lev, lWord, rWord, bagOfWords);
            
        ///////////// END OF TIME COUNTING ///////////////////////////
        auto stop_aut = std::chrono::high_resolution_clock::now(); ///
        //////////////////////////////////////////////////////////////

        auto duration_aut = std::chrono::duration_cast<std::chrono::microseconds>(stop_aut - start_aut);
        std::cout << "Autocomplete run time (" << duration_aut.count() << " microseconds):\n\n" << std::endl;

        for(auto word: bagOfWords) {
            std::cout << word << std::endl;
        }

        if(bagOfWords.size() == 0) {
            std::cout << "(without suggestion ...)" << std::endl;
        }

        std::cout << "\033[H";
    }

    return;
}


void AutoComplete::dfs(STATE *st_mast, STATE_LEV *st_lev, std::string &lWord, std::string rWord, std::vector<std::string> &bagOfWords) {

    if(st_mast->isFinal && st_lev->isMatch) {
        bagOfWords.push_back(lWord + rWord);
    }

    if(st_lev->transitions.size() == 1) {
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