#include "jsonreader.h"
#include <string>

JSONReader::JSONReader(string path)
{
    this->path = path;
}
JSONReader::~JSONReader(){

}
void JSONReader::Sort(){
    sort(shedule.begin(), shedule.end(), [](Lesson s1, Lesson s2) {
        return (s1.get_room() > s2.get_room());
        });
}

void JSONReader::info(){
    for (auto elem : this->shedule) {
        cout << elem.get_id() << " | " << elem.get_subject() << " | " << elem.get_type() << " | " << elem.get_room() << endl;
    }
}
vector<Lesson> JSONReader::read(){
    //main things...
    F.open(path);

            if(!this->is_open())
    {
        cout << "Can't open file! ERROR!!!" << endl;
    }
            nlohmann::json json;
            F >> json;
            for(auto & elem : json){
                shedule.push_back(parse(elem));
            }
      return shedule;
}

bool JSONReader::is_open(){
    return F.is_open();
}

Lesson JSONReader::parse(const nlohmann::json &j){
    int id = j.at("id");
    int room = j.at("room");
    string subject = j.at("subject");
    string type = j.at("type");
    return Lesson(id,subject, type, room);
}
