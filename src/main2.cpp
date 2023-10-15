#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include "levenshtein.h"



int main() {

    LevenshteinAutomaton lev("woof", 1);
    lev.generate(true);


    return 0;
}



