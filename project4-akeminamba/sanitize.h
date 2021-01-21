#pragma once
#include <string>
#include <iostream>

void sanitize(std::string &);
bool shouldFilter(const char &);
void debug(std::map<std::string, std::vector<std::string>>);


// Sanitizes a given word by removing non-essential characters from the start
// and end.
void sanitize(std::string & word) {
    size_t start_index = 0;
    size_t end_index = word.size() - 1;

    while(shouldFilter(word[start_index])) {
        start_index++;
    }

    while(shouldFilter(word[end_index])) {
        end_index--;
    }

    if (start_index != 0 || end_index != word.size() - 1) {
        word = word.substr(start_index, end_index);
    }
}


// Returns true if character should be filtered out.
bool shouldFilter(const char & target) {
    char bad_char[] = { ' ', '_', '-', '\"', '\'', '(', ')' };

    for (unsigned int i = 0; i < 7; ++i) {
        if (target == bad_char[i]) {
            return true;
        }
    }

    return false;
}


// Helps print out map of vectors structure. Each new line is a new key,
// followed by it's associated keys. Like so:
//      key1 : value1 value2
//      key2 : value3 value4 value5
void debug(std::map<std::string, std::vector<std::string>> map_of_vectors) {
    for (std::pair<std::string, std::vector<std::string>> obs : map_of_vectors) {
        std::cout << obs.first << " :";
        for (auto value : obs.second) {
            std::cout << " " << value;
        }
        std::cout << std::endl;
    }
}
