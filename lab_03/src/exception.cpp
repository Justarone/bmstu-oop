#include "exception.hpp"

AppBaseException::AppBaseException(const char *errmsg): _errmsg(errmsg) {};
AppBaseException::~AppBaseException() {};
const char *AppBaseException::what() const noexcept {
    return _errmsg;
};

AppOutOfRange::AppOutOfRange(const char *errmsg): AppBaseException(errmsg) {};
AppInvalidArgument::AppInvalidArgument(const char *errmsg): AppBaseException(errmsg) {};
AppValueException::AppValueException(const char *errmsg): AppBaseException(errmsg) {};
