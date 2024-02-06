/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"
#include <iostream>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    PronounceDict prondict("data/cmudict.0.7a");
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            if(word.length()<=2) continue;
            string split1 = word.substr(1);
            string split2 = word[0] + word.substr(2);
            //cout<<word<<"     "<<split1<<"     "<<split2<<endl;
            if(prondict.homophones(word,split1)&&prondict.homophones(word,split2)){
                ret.push_back(std::tuple<string,string,string>(word,split1,split2));
            }
        }
    }
    return ret;
}
