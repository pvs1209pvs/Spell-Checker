#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>   
#include <utility>


int lev(const std::string &a, const std::string &b){
 
    int cost_mtx[b.length()+1][a.length()+1];
     for (size_t i = 0; i < b.length()+1; i++){
        for (size_t j = 0; j < a.length()+1; j++){
            cost_mtx[i][j] = 0;
        }
    }
    
    for (size_t i = 1; i < a.length()+1; ++i){
        cost_mtx[0][i] = i;
    }

    for (size_t i = 1; i < b.length()+1; ++i){
        cost_mtx[i][0] = i;
    }
    
    for (size_t i = 1; i < b.length()+1; ++i){
        for (size_t j = 1; j < a.length()+1; ++j){
            cost_mtx[i][j] = 
            a[j-1] != b[i-1] ? 
            std::min({cost_mtx[i-1][j-1], cost_mtx[i-1][j], cost_mtx[i][j-1]}) + 1 : 
            cost_mtx[i-1][j-1];
        }
    }
    
    
    return cost_mtx[b.length()][a.length()];

}

std::vector<std::string> read_words(){
    
    std::vector<std::string> words{};

    std::ifstream dict("english3.txt");

    std::string line;

    while(std::getline(dict, line)){
        words.push_back(line);
    }

    return words;

}

int main(){

    const std::string a = "dnosaur";
    const size_t num_sug = 10;

    std::vector<std::string> words = read_words();

    auto compare = [](std::pair<std::string, int> a, std::pair<std::string, int> b){
        return a.second > b.second;
    };

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(compare)> sug(compare);

    for (size_t i = 0; i < words.size(); i++){
        sug.push(std::pair<std::string, int>{words.at(i), lev(a, words.at(i))});
    }

    for (size_t i = 0; i < std::min(num_sug, sug.size()); i++){
        std::cout << sug.top().first << std::endl;
        sug.pop();
    }

    return 0;

}