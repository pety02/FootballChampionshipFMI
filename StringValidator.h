//
// Created by User on 5/16/2026.
//

#ifndef STRINGVALIDATOR_H
#define STRINGVALIDATOR_H

#include <string>

/**
*
*/
class StringValidator final {
public:
    StringValidator() = default;

    /**
    *
    */
    static void validate(const std::string& str, const std::string& emptyStringMessage, const std::string &blankStringMessage);
};

#endif //STRINGVALIDATOR_H