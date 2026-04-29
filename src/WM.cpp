#include "WM.h"
#include<vector>
#include<fstream>
#include<iostream>
#include<random>
WM::WM(const std::string& filename) {
    std::ifstream f(filename);
    std::string word;

    if (!f.is_open()) {
        std::cout<<"Nu am putut deschide fisierul!"<<std::endl;
    }
    while (f>>word) {
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);

        if (word.length()==5) {
            dictionary.insert(word);
            words.push_back(word);
        }
    }
    f.close();
}

bool WM::isValidWord(const std::string& word) const {
    if (dictionary.find(word)!=dictionary.end()) {
        return true;}
    return false;
}

std::string WM::getRandomWord() const {
    if (words.empty()) {
        return "PIZZA";
    }

    static std::mt19937 rng(std::random_device{}());

    std::uniform_int_distribution<std::size_t> dist{0,words.size()-1};

    return words[dist(rng)];
}