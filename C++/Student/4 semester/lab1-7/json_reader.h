#ifndef LIBS_H
#define LIBS_H
#include "libs.h"
#endif
//
#include "abstract_reader.h"
//

#ifndef JSON_READER_H
#define JSON_READER_H
class JSON :public AbstractReader
{
private:
    ifstream Fin;
    ofstream Fout;
    nlohmann::json json;
    int pos = 0;
    nlohmann::json::const_iterator it;
    bool eof = 0;
public:
        //
        vector<s_passenger_cars> Read();
        s_passenger_cars parse(const nlohmann::json& j);
        string GetFormattedString(s_passenger_cars& car);
        string DrawTable();
        void Write(vector<s_passenger_cars> cars, string write_to);
        bool is_open();
        void Open(string read_from=JSON_IN);
        //
        AbstractReader & operator>> (s_passenger_cars & car);
        operator bool();
};

#endif // JSON_READER_H
