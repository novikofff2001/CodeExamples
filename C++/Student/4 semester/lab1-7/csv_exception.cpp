#include "csv_exception.h"

const char* CSVException::what()
{
    std::string out = err_mess;
    if(_line_no!=-1)
        out+=", line "+std::to_string(_line_no);
    if(_line!="")
        out+=": "+_line;
    return out.c_str();
}
