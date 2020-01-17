//
// Created by bhave on 12/25/2019.
//

/**
 * Sample Exception class setup to use for creating other exception classes
 */

#include <string>

class SampleException : public std::exception {
    std::string message;
public:
    explicit SampleException(std::string msg) {
        message = std::move(msg);
    }

    const char *what() const noexcept override {
        return message.c_str();
    }
};
