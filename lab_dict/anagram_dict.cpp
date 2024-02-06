/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream anagramFile(filename);
    string anagram;
    if(anagramFile.is_open()){
        while (getline(anagramFile, anagram)) {
            if(anagram.empty()) continue;
            string key = anagram;
            sort(key.begin(),key.end());
            vector<string>& valuevec = dict[key];
            //check whether the word has existed
            size_t j = 0;
            for(; j < valuevec.size(); j++){
                if(valuevec[j]==anagram) break;
            }
            if(j==valuevec.size()) valuevec.push_back(anagram);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(size_t i = 0; i < words.size(); i++){
        if(words[i].empty()) continue;
        string key = words[i];
        sort(key.begin(),key.end());
        vector<string>& valuevec = dict[key];
        //check whether the word has existed
        size_t j = 0;
        for(; j < valuevec.size(); j++){
            if(valuevec[j]==words[i]) break;
        }
        if(j==valuevec.size()) valuevec.push_back(words[i]);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string key = word;
    sort(key.begin(),key.end());
    auto findan = dict.find(key);
    //std::cout<<findan->second.size()<<std::endl;
    if(findan==dict.end()) return vector<string>();
    if(findan->second.size()<=1) return vector<string>();
    return findan->second;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
    for(auto& dictkv: dict){
        if(dictkv.second.size()>1) ret.push_back(dictkv.second);
        //std::cout<<dictkv.second.size()<<std::endl;
    }
    return ret;
}
