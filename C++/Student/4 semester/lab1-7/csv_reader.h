#ifndef LIBS_H
#define LIBS_H
#include "libs.h"
#endif
//
#include "abstract_reader.h"
#include "csv_exception.h"
//
#ifndef CSV_READER_H
#define CSV_READER_H
//
class CSV: public AbstractReader
{
    private:
        ifstream Fin;
        ofstream Fout;
    public:
        vector <s_passenger_cars> Read();
        vector <s_passenger_cars> SortByChoice(vector <s_passenger_cars> cars, int elder_than, e_Colors color_choice);
        vector <s_passenger_cars> SortByYear(vector <s_passenger_cars> cars);
        vector <s_passenger_cars> Add(vector <s_passenger_cars> cars, string mark,
                                      e_Colors color, int year, e_VehicleType veh_type=VEHICLE_CAR, int max_speed=0);
        string GetFormattedString(s_passenger_cars& car);
        string DrawTable();
        string Repr(s_passenger_cars car);
        void Write(vector <s_passenger_cars> cars, string write_to=CSV_OUT);
        void DrawTable(ostream& output);
        bool is_open();
        void Open(string read_from=CSV_IN);
        //
        AbstractReader & operator>> (s_passenger_cars & car);
        operator bool();
};

#endif // CSV_READER_H
