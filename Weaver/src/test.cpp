#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <unordered_set>

#include <algorithm>

//file path to read dictionary from
const std::string filePath = "../assets/en_words_scrabble.txt";
//dictionary of all words
std::unordered_set<std::string> dictionary;

const int WORD_LENGTH = 4;

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
            if(word.size() == WORD_LENGTH) dictionary.insert(word);
        }
    }
    return true;
}

void solve() {
    if(!loadDictionary()) {
        std::cout << "Dictionary could not be loaded from file " << filePath << "\n";
        return;
    } else {
        std::cout << "Dictionary loaded from file " << filePath << "\n";
        std::cout << "Dictionary has a size of " << dictionary.size() << "\n";
    }

    int total = 0, maxCur = 0;
    for(std::string word : dictionary) {

        int cur = 0;
        for(std::string comp : dictionary) {
            int difference = 0;

            for(int i = 0;i < WORD_LENGTH;i++) {
                if(word[i] != comp[i]) {
                    difference++;
                }
            }

            if(difference == 1) cur++;
        }

        maxCur = std::max(maxCur, cur);
        total += cur;
    }

    std::cout << (double) total / (double) dictionary.size() << "\n";
    std::cout << maxCur << "\n";
}

int main() {
    solve();
}