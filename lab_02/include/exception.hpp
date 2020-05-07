/* В лекционном примере наследники перегружают конструкторы, можно 
 * было внести информацию об индексе или добавить еще какую-то информацию
 * */
#include <exception>
#include <string>

using string = std::string;


class ExceptionMatrix: public std::exception {
protected:
    string _errmsg;
public:
    ExceptionMatrix(const string file_info, const string line_info, 
                    const string time_info, const string errmsg = "No error message");
    virtual ~ExceptionMatrix() {};
    virtual const char *what() const noexcept override;
};


class IndexError: public ExceptionMatrix {
    IndexError(const string file_info, const string line_info, 
               const string time_info, const string errmsg = "No error message"):
               ExceptionMatrix(file_info, line_info, time_info, errmsg) {
        _errmsg += " (error type: IndexError)";
    }
};


class MemoryError: public ExceptionMatrix {
    MemoryError(const string file_info, const string line_info, 
               const string time_info, const string errmsg = "No error message"):
               ExceptionMatrix(file_info, line_info, time_info, errmsg) {
        _errmsg += " (error type: MemoryError)";
    }
};
