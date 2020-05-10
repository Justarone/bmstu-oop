/* В лекционном примере наследники перегружают конструкторы, можно 
 * было внести информацию об индексе или добавить еще какую-то информацию
 * */
#pragma once
#include <exception>
#include <string>

using string = std::string;


class ExceptionMatrix: public std::exception {
protected:
    string _errmsg;
public:
    ExceptionMatrix(const string time_info, const string file_info, const int line_info, 
                    const string errmsg = "No error message");
    virtual ~ExceptionMatrix() {};
    virtual const char *what() const noexcept override {
        return _errmsg.c_str();
    };
};


class IndexError: public ExceptionMatrix {
public:
    IndexError(const string time_info, const string file_info, const int line_info, 
               const string errmsg = "No error message"):
               ExceptionMatrix(time_info, file_info, line_info, errmsg) {
        _errmsg += " (error type: IndexError)";
    }
};


class MemoryError: public ExceptionMatrix {
public:
    MemoryError(const string time_info, const string file_info, const int line_info, 
               const string errmsg = "No error message"):
               ExceptionMatrix(time_info, file_info, line_info, errmsg) {
        _errmsg += " (error type: MemoryError)";
    }
};

class InvalidArgument: public ExceptionMatrix {
public:
    InvalidArgument(const string time_info, const string file_info, const int line_info, 
               const string errmsg = "No error message"):
               ExceptionMatrix(time_info, file_info, line_info, errmsg) {
        _errmsg += " (error type: InvalidArgument)";
    }
};

class IncompatibleElements: public ExceptionMatrix {
public:
    IncompatibleElements(const string time_info, const string file_info, const int line_info, 
               const string errmsg = "No error message"):
               ExceptionMatrix(time_info, file_info, line_info, errmsg) {
        _errmsg += " (error type: IncompatibleElements)";
    }
};

class InvalidState: public ExceptionMatrix {
public:
    InvalidState(const string time_info, const string file_info, const int line_info, 
               const string errmsg = "No error message"):
               ExceptionMatrix(time_info, file_info, line_info, errmsg) {
        _errmsg += " (error type: IncompatibleElements)";
    }
};

#include "../implementation/exception.hpp"
