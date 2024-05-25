#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <stdexcept>

class MyException : public std::exception
{
private:
    std::string errorMessage;
public:
    MyException() = delete;
    MyException(const std::string& message) : errorMessage(message) {}
    const char* what() const noexcept override {return errorMessage.c_str();}
};

#endif // MYEXCEPTION_H
