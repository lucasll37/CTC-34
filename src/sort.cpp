#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]) {

    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 0;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        std::cout << "Error opening the input file for reading." << std::endl;
        return 1;
    }

    std::vector<std::string> words;
    std::string word;

    while (std::getline(inputFile, word)) {
        words.push_back(word);
    }

    inputFile.close();
    std::sort(words.begin(), words.end());
    std::ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        std::cout << "Error opening the output file for writing." << std::endl;
        return 1;
    }

    for (const auto& w : words) {
        outputFile << w << std::endl;
    }

    std::cout << "Words ordered and written in " << outputFileName << std::endl;
    outputFile.close();
    return 0;
}
