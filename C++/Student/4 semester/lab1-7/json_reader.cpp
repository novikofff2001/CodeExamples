#include "json_reader.h"
//
AbstractReader & JSON::operator>> (s_passenger_cars & car)
{
    if(it != json.cend())     // смущает форма записи
        car = parse(*it);
    return *this;
}
//

JSON::operator bool()
{
    return it++ != json.cend();
}
//

//
void JSON::Open(string read_from)
{
    this->Fin.open(read_from);
    this->Fin>>this->json;
    it = json.begin();
}
//

vector<s_passenger_cars> JSON::Read()
{
    if(!this->is_open())
        throw CSVException("Error while reading file: File not opened!");
    vector <s_passenger_cars> cars;
    for(auto it = json.begin();it != json.end();it++)
        cars.push_back(parse(*it));
    return cars;
}
//

void JSON::Write(vector <s_passenger_cars> cars, string write_to)
{
    this->Fout.open(write_to);
    if(!Fin)
        throw CSVException("Error while writing to file: File not opened!");
    nlohmann::json jsonfile;
    for(const auto &car: cars)
    {
        jsonfile["mark"] = car.mark;
        jsonfile["color"] = car.color;
        jsonfile["year"] = car.year;
        jsonfile["veh_type"] = car.veh_type;
        jsonfile["max_speed"] = car.max_speed;
        Fout<<jsonfile;
    }
}

//
bool JSON::is_open()
{
    return this->Fin.is_open();
}

s_passenger_cars JSON::parse(const nlohmann::json &j)
{
    s_passenger_cars car;
    try
    {
        car.id = s_passenger_cars::genId();
        car.year = j.at("year").get<int>();
        car.mark = j.at("mark");
        car.color = j.at("color").get<e_Colors>();
        car.veh_type = j.at("veh_type").get<e_VehicleType>();
        car.max_speed = j.at("max_speed").get<int>();
    }
    catch(nlohmann::detail::type_error& pe)
    {
        throw CSVException(pe.what());
    }
    return car;
}


string JSON::GetFormattedString(s_passenger_cars& car)
{
    stringstream ss;
    ss<<setw(4)<<car.id<<'|'<<setw(8)<<car.mark<<'|'<<setw(8)<<car.color<<'|'<<setw(8)<<car.year<<'|'
      <<setw(14)<<car.veh_type<<'|'<<setw(11)<<car.max_speed<<'|';
    return ss.str();
}
//


string JSON::DrawTable()
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

