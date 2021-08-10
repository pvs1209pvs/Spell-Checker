#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>   
#include <utility>
#include <cctype>


/**
 * Finds the cost for single row.
 * @param a String goes left to right.
 * @param b String goes top to bottom.
 * @param itr Iteration number.
 * @param cost_mtx Current cost.
 */ 
void lev(const std::string &a, const std::string &b, int itr, int * cost_mtx){

    int dig = cost_mtx[0];
    int top = 0;
    int left = itr+1;

    for (size_t i = 1; i < a.length()+1; ++i){
        top = cost_mtx[i];
        left = (a[i-1] != b[itr]) ? std::min({dig, top, left})+1 : dig;
        dig = top;
        cost_mtx[i-1] = left;
    }

    std::rotate(&cost_mtx[0], &cost_mtx[a.length()], &cost_mtx[a.length()+1]);
    cost_mtx[0] = itr+1;
  
}

/**
 * Returns the levenshtein edit distance.
 * @param a First string.
 * @param b Second string.
 * @return Levenshtein edit distance.
 */
int lev(const std::string &a, const std::string &b){

    int cost_mtx[a.length()+1];
    for (size_t i = 0; i < a.length()+1; ++i){
        cost_mtx[i] = i;
    }

    for (size_t i = 0; i < b.length(); ++i){
        lev(a, b, i, cost_mtx);
    }

    return cost_mtx[a.length()];
    
}

/**
 * Reads words from english3.txt.
 * @return Returns all the words from the file. 
 */
std::vector<std::string> read_words(){
    
    std::vector<std::string> words{};

    std::ifstream dict("../res/english3.txt");

    std::string line;

    while(std::getline(dict, line)){
        words.push_back(line);
    }

    return words;

}

/**
 * Checks if the string only contains alphabets.
 * @param a String to be tested.
 * @return True if the string only contains alphabets, else false.
 */
bool isalpha(const std::string &a){

    for(char x : a){
        if(!std::isalpha(x)){
            return false;
        }
    }

    return true;

}

int main(){

    const size_t NUM_SUGGESTIONS = 10;
    
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
    for (size_t i = 0; i < std::min(NUM_SUGGESTIONS, suggestions.size()); i++){
        std::cout << i << ". "<< suggestions.top().first << std::endl;
        suggestions.pop();
    }

    return 0;

}