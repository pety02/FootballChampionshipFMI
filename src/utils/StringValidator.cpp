//
// Created by User on 5/16/2026.
//

#include "StringValidator.h"
#include <stdexcept>

void StringValidator::validate(const std::string& str,  const std::string& emptyStringMessage, const std::string &blankStringMessage) {
    if(str.empty() || (str.size() == 1 && str[0] == '\0')) {
        throw std::invalid_argument(emptyStringMessage);
    }

    int whiteSpacesCount = 0;
    for(const char ch : str) {
        if(ch == ' ') {
            whiteSpacesCount++;
        }
    }

    if(whiteSpacesCount == str.size()) {
        throw std::invalid_argument(blankStringMessage);
    }
}