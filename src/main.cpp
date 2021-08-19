#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>   
#include <utility>
#include <cctype>
#include "levenshtein.h"

int main(){

    std::string input_word{};

    while(input_word.length() < 1 || !isalpha(input_word)){
        std::cout << "Enter your word." << std::endl;
        std::cin >> input_word;
    }
    
    std::transform (input_word.begin(), input_word.end(), input_word.begin(), ::tolower);

    std::vector<std::string> words = read_words();

    auto compare = [](std::pair<std::string, int> a, std::pair<std::string, int> b){
        return a.second > b.second;
    };

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(compare)> suggestions(compare);

    for (size_t i = 0; i < words.size(); i++){
        suggestions.push(std::pair<std::string, int>{words.at(i), lev(input_word, words.at(i))});
    }

    std::cout << "Suggestions" << std::endl;
    std::vector<std::string> corrected = list_suggestions(input_word);

    for(std::string s : corrected){
        std::cout << s << std::endl;
    }

    return 0;

}