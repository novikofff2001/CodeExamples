#include "csv_reader.h"
AbstractReader & CSV::operator>> (s_passenger_cars & car)
{
        string str;
        getline(this->Fin, str);
        auto tokens = split(str, ';');
        car.id = stoi(tokens[0]);
        car.mark = tokens[1];
        car.color = static_cast<e_Colors>(stoi(tokens[2]));
        car.year = stoi(tokens[3]);
        car.veh_type = static_cast<e_VehicleType>(stoi(tokens[4]));
        car.max_speed = stoi(tokens[5]);
        return *this;
}
//
CSV::operator bool()
{
    return !this->Fin.eof();
}
//
bool CSV::is_open()
{
    return this->Fin.is_open();
}
//

void CSV::Open(string read_from)
{
    Fin.open(read_from);
}
//
vector <s_passenger_cars> CSV::Read()
{
    if(!this->is_open())
        throw CSVException("Error while reading file: File not opened!");
    string row;
    vector <s_passenger_cars> cars;
    s_passenger_cars car;
    int line_no = 0;
    try
    {
        while(getline(this->Fin, row))
        {
            auto tokens = split(row, ';');
            car.id = s_passenger_cars::genId();
            car.mark = tokens[1];
            car.color = static_cast<e_Colors>(stoi(tokens[2]));
            car.year = stoi(tokens[3]);
            car.veh_type = static_cast<e_VehicleType>(stoi(tokens[4]));
            if(car.veh_type == VEHICLE_CAR)
            {
                car.max_speed = stoi(tokens[5]);
                cars.push_back(std::move(car));
            }
            line_no++;
        }
    }
    catch(std::invalid_argument &ia)
    {
        throw CSVException(ia.what(), line_no, row);
    }
    return cars;
}
//

void CSV::Write(vector <s_passenger_cars> cars, string write_to)
{
    this->Fout.open(write_to);
    if(!this->Fout)
        throw CSVException("Error while writing file: File was not opened!");
    for(const auto &car: cars)
    {
        this->Fout<<car.id<<';'<<car.mark<<';'<<car.color<<';'<<car.year  <<';';
        this->Fout<<car.veh_type<<';'<<car.max_speed<<';'<<endl;
    }
}
//

string CSV::DrawTable()
{
    stringstream output;
    output<<endl;
    output<<setw(3)<<"id"   <<setw(2)<<'|';
    output<<setw(6)<<"Mark" <<setw(3)<<'|';
    output<<setw(6)<<"Color"<<setw(3)<<'|';
    output<<setw(6)<<"Year" <<setw(3)<<'|';
    output<<setw(13)<<"Vehicle Type" <<setw(2)<<'|';
    output<<setw(10)<<"Max Speed" <<setw(2)<<'|';
//    output<<setw(16)<<"Num Of Passengers"<<setw(2)<<'|';
//    output<<setw(11)<<"Max Weight" <<setw(2)<<'|';
    output<<endl;
    for(int i=0; i<60;i++)
        output<<'-';
    output<<endl;
    return output.str();
}
//

void CSV::DrawTable(ostream& output)
{
    output<<endl;
    output<<setw(3)<<"id"   <<setw(2)<<'|';
    output<<setw(6)<<"Mark" <<setw(3)<<'|';
    output<<setw(6)<<"Color"<<setw(3)<<'|';
    output<<setw(6)<<"Year" <<setw(3)<<'|';
    output<<setw(13)<<"Vehicle Type" <<setw(2)<<'|';
    output<<setw(10)<<"Max Speed" <<setw(2)<<'|';
//    output<<setw(16)<<"Num Of Passengers"<<setw(2)<<'|';
//    output<<setw(11)<<"Max Weight" <<setw(2)<<'|';
    output<<endl;
    for(int i=0; i<60;i++)
        output<<'-';
    output<<endl;
}
//

vector <s_passenger_cars> CSV::SortByChoice(vector <s_passenger_cars> cars, int elder_than, e_Colors color_choice)
{
    vector <s_passenger_cars> sorted_cars;
    for(const auto &car: cars)
        if (2021-car.year >= elder_than && car.color==color_choice)
            sorted_cars.push_back(car);
    return sorted_cars;
}
//

vector <s_passenger_cars> CSV::SortByYear(vector <s_passenger_cars> cars)
{
    sort(cars.begin(), cars.end());
    return cars;
}
//

string CSV::GetFormattedString(s_passenger_cars& car)
{
    stringstream ss;
    ss<<setw(4)<<car.id<<'|'<<setw(8)<<car.mark<<'|'<<setw(8)<<car.color<<'|'<<setw(8)<<car.year<<'|'
      <<setw(14)<<car.veh_type<<'|'<<setw(11)<<car.max_speed<<'|';
    return ss.str();
}
//

vector <s_passenger_cars> CSV::Add(vector <s_passenger_cars> cars, string mark,
                                   e_Colors color, int year, e_VehicleType veh_type, int max_speed)
{
    s_passenger_cars car;
    car.color = color;
    car.year = year;
    car.mark = mark;
    car.max_speed = max_speed;
    car.veh_type = veh_type;
    cars.push_back(car);
    return cars;
}
//

string CSV::Repr(s_passenger_cars car)
{
    stringstream ss;
    ss<<car.id<<';'<<car.mark<<';'<<car.color<<';'<<car.year<<car.veh_type<<';';
    ss<<car.max_speed<<';';
    return ss.str();
}


