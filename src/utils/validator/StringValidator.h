#ifndef STRINGVALIDATOR_H
#define STRINGVALIDATOR_H

#include <string>

/**
 * Utility class responsible for validating string inputs.
 *
 * This class provides common validation rules used across the system,
 * such as checking whether a string is empty or contains only whitespace.
 */
class StringValidator final {
public:
    /**
     * Default constructor.
     * The class is intended to be used in a static way only.
     */
    StringValidator() = default;

    /**
     * Validates a string according to basic rules:
     * - Must not be empty
     * - Must not consist only of whitespace characters
     *
     * @param str The string to validate
     * @param emptyStringMessage Exception message used if the string is empty
     * @param blankStringMessage Exception message used if the string contains only whitespace
     *
     * @throws std::invalid_argument if validation fails
     */
    static void validate(
        const std::string& str,
        const std::string& emptyStringMessage,
        const std::string& blankStringMessage
    );
};

#endif // STRINGVALIDATOR_H