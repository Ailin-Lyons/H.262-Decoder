//
// Created by bhave on 12/23/2019.
//



#include <string>
#include <utility>

class PacketException : public std::exception {
    std::string message;

public:
    explicit PacketException(std::string msg) {
        message = std::move(msg);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};