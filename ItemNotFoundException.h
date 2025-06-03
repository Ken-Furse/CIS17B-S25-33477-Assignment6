#ifndef ITEMNOTFOUNDEXCEPTION_H
#define ITEMNOTFOUNDEXCEPTION_H

#include <stdexcept>

class ItemNotFoundException : public std::runtime_error {
public:
    explicit ItemNotFoundException(const std::string &msg) : std::runtime_error(msg) {}
};

#endif
