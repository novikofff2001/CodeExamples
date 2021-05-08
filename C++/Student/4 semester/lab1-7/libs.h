#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <clocale>
#include <iterator>
#include "json.hpp"
#include "csv_exception.h"
using namespace std;
// consts //
const string WORK_DIR = string(getenv("USERPROFILE"))+"\\Desktop\\";
const string CSV_IN = WORK_DIR+"csv_in.csv";
const string CSV_OUT = WORK_DIR+"csv_out.csv";
const string JSON_IN = WORK_DIR+"json_in.json";
const string JSON_OUT = WORK_DIR+"json_in.json";
// ENUMs //
enum e_Colors{COLOR_RED=0, COLOR_ORANGE, COLOR_YELLOW, COLOR_GREEN,
              COLOR_CYAN, COLOR_BLUE, COLOR_PURPLE, COLOR_BLACK, COLOR_WHITE};
//
enum e_VehicleType{VEHICLE_CAR=0, VEHICLE_TRUCK, VEHICLE_BUS};

// STRUCTs //
struct s_cars{
              static int gen_id;
              static int genId() {static int gen_id = 0; return gen_id++; };
              int id;
              string mark;
              e_Colors color;
              int year;
              e_VehicleType veh_type;};

struct s_passenger_cars: s_cars {
                                 int max_speed;
                                 friend bool operator< (const s_passenger_cars& car1, const s_passenger_cars& car2);
                                 s_passenger_cars& operator= (const s_passenger_cars& another_car);
                                 s_passenger_cars&& operator<< (const s_passenger_cars&& another_car);
                                 s_passenger_cars(const s_passenger_cars &another_car) = default;
                                 s_passenger_cars(const s_passenger_cars &&another_car);
                                 s_passenger_cars();
                                 };
// OPERATORs //
ostream& operator<< (ostream& out, const s_passenger_cars &print_car);

// FUNCTIONs //
vector <string> split(const string& str, char delim);
//

