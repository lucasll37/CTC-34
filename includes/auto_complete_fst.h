#ifndef AUTO_COMPLETE_MAST_H
#define AUTO_COMPLETE_MAST_H

#include "minAcyclicSubseqTransducers.h"
#include "levenshtein.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <chrono>
#include <filesystem>


#define MAX_WORD_WITHOUT_LEV 30

class AutoComplete {

public:

    void execute(std::string pathToOrdenatedWords, unsigned int maxLevenshteinDistance);

private:

    void dfs(STATE *st_mast,
            STATE_LEV *st_lev,
            std::string &input,
            std::string &lWord,
            std::string rWord,
            std::string index,
            std::vector<std::pair<std::string, std::string>> &bagOfWords,
            bool useLevenshtein);
            
};

#endif /* EXAME_AUTO_COMPLETE_MAST_H */

