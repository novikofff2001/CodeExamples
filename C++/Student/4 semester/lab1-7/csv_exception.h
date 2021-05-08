#ifndef CSV_EXCEPTION_H
#define CSV_EXCEPTION_H
#include <exception>
#include <string>
class CSVException: public std::exception
{
private:
    std::string err_mess;
    int _line_no;
    std::string _line;
public:
    CSVException(std::string error, int f_line_no=-1, std::string line=""): err_mess(error), _line_no(f_line_no), _line(line){};
    const char* what();
};

#endif // CSV_EXCEPTION_H
