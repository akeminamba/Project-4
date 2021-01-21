#include <fstream>
#include <vector>
#include <string>
#include <map>

#include <iostream>

#include "sanitize.h"

class BookBot {
private:
    std::map<std::string, std::vector<std::string>> markov_chain;

public:
    BookBot(const unsigned int seed);

    void readIn(const std::string & filename);
    bool isEndPunctuation(std::string word, int number);
    std::vector<std::string> getValues(const std::string & key);
    std::string generateSentence();
};

void BookBot::readIn(const std::string & filename) {
  std::ifstream inFile(filename);
  std::string word_one = "^";
  std::string word_two;

  while(inFile >> word_two) {
    sanitize(word_two);
    if(isEndPunctuation(word_two, word_two.length() - 1) == true) {
      std::string punctuation(1, word_two[word_two.size() - 1]);
      word_two = word_two.substr(0, word_two.size() - 1);
      markov_chain[word_one].push_back(word_two);
      markov_chain[word_two].push_back(punctuation);
      markov_chain[punctuation].push_back("$");
      word_one = "^";
    } else {
      markov_chain[word_one].push_back(word_two);
      word_one = word_two;
    }
  }
}

BookBot::BookBot(const unsigned int seed) {
  srand(seed);
}

bool BookBot::isEndPunctuation(std::string word, int number) {
  if(word[number] == '.' || word[number] == '?' || word[number] == '!') {
    return true;
  } else {
    return false;
  }
}

std::vector<std::string> BookBot::getValues(const std::string & key) {
  std::vector<std::string> values = markov_chain[key];
  return values;
}

std::string BookBot::generateSentence() {
  std::string word = "^";
  std::vector<std::string> candidates;
  std::string nextword;
  std::string sentence = "";
  while(word != "$") {
    candidates = markov_chain[word];
    nextword = candidates[rand()%candidates.size()];
    if(nextword != "$") {
      if(isEndPunctuation(nextword, nextword.length() - 1) == true) {
        sentence = sentence + nextword;
      } else {
        if(sentence == "") {
          sentence = sentence + nextword;
        } else {
          sentence = sentence + " " + nextword;
          word = nextword;
        }
      }
    }
    word = nextword;
  }
  return sentence;
}
