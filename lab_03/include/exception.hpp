#pragma once
#include <exception>

class AppBaseException: public std::exception {
protected:
    const char *_errmsg;
public:
    AppBaseException() = delete;
    explicit AppBaseException(const char *errmsg = "No error message");
    virtual ~AppBaseException() = 0;
    virtual const char *what() const noexcept override;
};


class AppOutOfRange: public AppBaseException {
public:
    explicit AppOutOfRange(const char *errmsg = "No error message (out of range exception)"); 
};


class AppValueException: public AppBaseException {
public:
    explicit AppValueException(const char *errmsg = "No error message (value exception)"); 
};


class AppInvalidArgument: public AppBaseException {
public:
    explicit AppInvalidArgument(const char *errmsg = "No error message (invalid argument)"); 
};

