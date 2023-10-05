#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>



void generateSummary(const std::string& filename) { // declaring function, void returns result, & passes by reference
    std::ifstream inFile(filename); // attempts to open file with the location of value filename
    if (!inFile.is_open()) { 
        std::cerr << "That doesn't exist." << std::endl;
        return; // check if opening the file worked and give an error otherwise. Return exits the function
    }

    int numberOfSentences = 0;
    int numberOfWords = 0;
    std::vector<std::pair<std::string, int>> wordList; //vector creates array of pairs called wordList. Each pair containing a string and an integar

    std::string line, word;
    while (getline(inFile, line)) {
        // Count sentences based on '.', '!', '?'
        numberOfSentences += std::count_if(line.begin(), line.end(), [](char c) {
            return c == '.' || c == '!' || c == '?';
            });

        std::istringstream iss(line);
        while (iss >> word) {
            numberOfWords++;
            bool found = false;
            for (auto& pair : wordList) {
                if (pair.first == word) {
                    pair.second++;
                    found = true;
                    break;
                }
            }
            if (!found) wordList.push_back({ word, 1 });
        }
    }

    std::cout << "Number of sentences: " << numberOfSentences << std::endl;
    std::cout << "Number of words: " << numberOfWords << std::endl;

    for (const auto& pair : wordList) {
        double frequency = static_cast<double>(pair.second) / numberOfWords;
        std::cout << "Word: " << pair.first << ", Count: " << pair.second << ", Frequency: " << frequency << std::endl;
    }
}

int main() {
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;
    generateSummary(filename);
    return 0;
}
