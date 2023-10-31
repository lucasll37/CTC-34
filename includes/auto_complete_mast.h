#ifndef AUTO_COMPLETE_MAST_H
#define AUTO_COMPLETE_MAST_H

#include "minAcyclicSubseqTransducers.h"
#include "levenshtein.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <chrono>


class AutoComplete {

public:

    void execute(std::string pathToOrdenatedWords, unsigned int maxLevenshteinDistance);

private:

    void dfs(STATE *st_mast,
            STATE_LEV *st_lev,
            std::string &lWord,
            std::string rWord,
            std::vector<std::string> &bagOfWords,
            bool useLevenshtein);
};

#endif /* EXAME_AUTO_COMPLETE_MAST_H */