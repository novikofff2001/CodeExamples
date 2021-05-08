#ifndef LIBS_H
#define LIBS_H
#include "libs.h"
#endif
//

#ifndef ABSTRACT_READER_H
#define ABSTRACT_READER_H

class AbstractReader
{
    public:
        virtual vector <s_passenger_cars> Read() = 0;
        virtual string GetFormattedString(s_passenger_cars& car) = 0;
        virtual string DrawTable() = 0;
        virtual bool is_open() = 0;
        virtual void Open(string read_from) = 0;
        virtual AbstractReader & operator>> (s_passenger_cars & car) = 0;
        virtual operator bool() = 0;
};
#endif
