/* В лекционном примере наследники перегружают конструкторы, можно 
 * было внести информацию об индексе или добавить еще какую-то информацию
 * */
#include <exception>
#include <cstring>

class ExceptionMatrix: public std::exception {
protected:
    char *_errmsg;
public:
    ExceptionMatrix(const char *errmsg, );
    virtual ~ExceptionMatrix();
    virtual const char *what() const noexcept override;
};
class InvalidArgument: public ExceptionMatrix {};
class IndexError: public InvalidArgument {};
class OutOfRange: public IndexError {};
class MemoryError: public ExceptionMatrix {};
