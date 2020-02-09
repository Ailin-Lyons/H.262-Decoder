//
// Created by elnsa on 2020-01-16.
//

#ifndef __VIDEOEXCEPTION
#define __VIDEOEXCEPTION

#include <string>
/**
 * This exception is thrown when an unhandled value or an error occurs during the decoding process
 */

class VideoException : public std::exception {
    std::string message;

public:
    explicit VideoException(std::string msg) {
        message = std::move(msg);
    }

    const char *what() const noexcept override {
        return message.c_str();
    }
};

#endif