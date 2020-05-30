#pragma once
#include <exception>

class AppBaseException: public std::exception {
protected:
    const char *_errmsg;
public:
    AppBaseException() = delete;
    explicit AppBaseException(const char *errmsg = "No error message"): _errmsg(errmsg) {};
    virtual ~AppBaseException() {};
    virtual const char *what() const noexcept override {
        return _errmsg;
    };
};


class AppOutOfRange: public AppBaseException {
public:
    explicit AppOutOfRange(const char *errmsg = "No error message (out of range exception)"): 
        AppBaseException(errmsg) {};
};


class AppValueException: public AppBaseException {
public:
    explicit AppValueException(const char *errmsg = "No error message (value exception)"): 
        AppBaseException(errmsg) {};
};


class AppInvalidArgument: public AppBaseException {
public:
    explicit AppInvalidArgument(const char *errmsg = "No error message (invalid argument)"): 
        AppBaseException(errmsg) {};
};
