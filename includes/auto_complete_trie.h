#ifndef AUTO_COMPLETE_TRIE_H
#define AUTO_COMPLETE_TRIE_H

#include "trie.h"
#include "levenshtein.h"

#include <string>
#include <iostream>
#include <chrono>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    inline int getch(void) {
        int ch;
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

#endif

class AutoComplete {

public:

    void execute(void);

private:

    void dfs(STATE *st_mast,
            STATE_LEV *st_lev,
            std::string &lWord,
            std::string rWord,
            std::vector<std::string> &bagOfWords);
};

#endif /* AUTO_COMPLETE_TRIE_H */