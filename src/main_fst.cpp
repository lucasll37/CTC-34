#include <auto_complete_fst.h>

int main() {
    AutoComplete auto_complete;
    auto_complete.execute("./data/american-english-correct.txt", 1);

    return 0;
}