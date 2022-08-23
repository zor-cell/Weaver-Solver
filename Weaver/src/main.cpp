#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include <algorithm>

const std::string filePath = "../assets/en_words_scrabble.txt";
const int WORD_LENGTH = 4;
const int DEPTH = 50;

//dictionary of all words
std::unordered_set<std::string> dictionary;
//same size as dictionary, holds extra information of all the words in the dictionary which differ in exactly one letter
std::unordered_map<std::string, std::vector<std::string>> possibles; //{word, possibles}
//same size as dictionary, contains the path to each word as value
std::unordered_map<std::string, std::vector<std::string>> dp; //{word, path}

template<typename T>
void print(std::vector<T>& a) {
    for(T e : a) {
        std::cout << e << " ";
    }
    std::cout << "\n";
}

bool loadDictionary() {
    std::ifstream file(filePath);

    if(file.fail()) return false;
    else {
        std::string word;
        unsigned long long int freq;

        while(file >> word >> freq) {
            if(word.size() == WORD_LENGTH) {
                dictionary.insert(word);
                dp[word] = {};
            } 
        }
    }

    return true;
}

void input(std::string& start, std::string& target) {
    std::cout << "Enter start word: ";
    std::cin >> start;
    if(!dictionary.count(start)) {
        std::cout << start << " not in word list!\n\n";
        input(start, target);
        return;
    }
    
    std::cout << "Enter target word: ";
    std::cin >> target;
    if(!dictionary.count(target)) {
        std::cout << target << " not in word list!\n\n";
        input(start, target);
        return;
    }

    std::cout << "\n";
}

void search(std::string targetWord, std::string currentWord, int depth, std::vector<std::string> path) {
    //update path to current word with shorter path  
    dp[currentWord] = path;
    
    if(depth == 0) {
        return;
    };

    //get possible words if not yet computed
    if(possibles[currentWord].size() == 0) {
        std::vector<std::string> p;
        for(std::string word : dictionary) {
            int difference = 0;

            //word is only valid if there is exactly one difference
            for(int i = 0;i < WORD_LENGTH;i++) {
                if(word[i] != currentWord[i]) {
                    difference++;
                }
            }

            if(difference == 1) p.push_back(word);
        }

        possibles[currentWord] = p;
    }

    //search from each possible word
    //add current word to path each time
    for(std::string word : possibles[currentWord]) {
        path.push_back(word);
        if(dp[word].size() == 0 || path.size() < dp[word].size()) {
            search(targetWord, word, depth - 1, path);
        }
        path.pop_back();
    }

    return;
}

void solve() {
    if(!loadDictionary()) {
        std::cout << "Dictionary could not be loaded from file " << filePath << "\n";
        return;
    } else std::cout << "Dictionary of " << WORD_LENGTH << "-letter-words with size " << dictionary.size() << " loaded from file " << filePath << "!\n";

    while(1) {
        std::string start, target;
        input(start, target);

        search(target, start, DEPTH, {start});

        if(dp[target].size() == 0) std::cout << "No path found from " << start << " to " << target << " with depth of " << DEPTH << "\n";
        else {
            std::cout << "Path from " << start << " to " << target << " found in " << dp[target].size() - 1 << ": ";
            print(dp[target]);
            std::cout << "\n";
        }
    }
}

int main() {
    solve();
}