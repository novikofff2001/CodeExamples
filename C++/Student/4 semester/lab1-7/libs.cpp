#include "libs.h"
//
bool operator< (const s_passenger_cars& car1, const s_passenger_cars& car2)
{
    return car1.year < car2.year;
}
//

s_passenger_cars& s_passenger_cars::operator= (const s_passenger_cars &another_car)
{
   if(this==&another_car)         //self-equal protect
        return *this;
    this->id = std::move(another_car.id);
    this->color = std::move(another_car.color);
    this->mark = std::move(another_car.mark);
    this->year = std::move(another_car.year);
    this->veh_type = std::move(another_car.veh_type);
    this->max_speed = std::move(another_car.max_speed);
    return *this;
}
////
s_passenger_cars::s_passenger_cars(const s_passenger_cars &&another_car)
{
    this->id = std::move(another_car.id);
    this->color = std::move(another_car.color);
    this->mark = std::move(another_car.mark);
    this->max_speed = std::move(another_car.max_speed);
    this->year =std::move( another_car.year);
    this->veh_type = std::move(another_car.veh_type);
}

s_passenger_cars::s_passenger_cars()
{
    this->id = s_passenger_cars::genId();
    this->color = COLOR_WHITE;
    this->mark = "None";
    this->year = -1;
    this->max_speed = -1;
    this->veh_type = VEHICLE_CAR;
}
//

ostream& operator<< (ostream& out, const s_passenger_cars &car)
{
    out<<"id:"<<car.id<<" mark:"<<car.mark<<" color:"<<car.color<<" year:"<<car.year<<" veh_type:"<<car.veh_type<<" max_speed:"<<car.max_speed;
    return out;
}
//

extern vector<string> split(const string& str, char delim)
{
    vector<string> tokens;
    if (str.empty())
        return tokens;
    else
    {
        size_t start = 0, end = str.find(delim, start);
        do
        {
            end = str.find(delim, start);
            if (start != end)
                tokens.push_back(str.substr(start, (end - start)));
            start = end + 1;
        } while (end != str.npos);
    }
    return tokens;
}
//
