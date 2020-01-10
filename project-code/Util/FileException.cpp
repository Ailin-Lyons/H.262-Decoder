//
// Created by bhave on 12/23/2019.
//

#include <string>

class FileException : public std::exception {
    std::string message;

public:
    explicit FileException(std::string msg) {
        message = std::move(msg);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};