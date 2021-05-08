#ifndef JSONREADER_H
#define JSONREADER_H

#include "abstractreader.h"
#include <vector>
#include <string>
#include <algorithm>
#include "lesson.h"
#include <fstream>
#include "json-develop/single_include/nlohmann/json.hpp"
class JSONReader : public AbstractReader
{
public:
    JSONReader(string path);
    bool is_open();
    vector<Lesson> read();
    void info();
    void Sort();
    ~JSONReader();
    Lesson parse(const nlohmann::json & j);

private:
    vector<Lesson> shedule;
    string path;
    ifstream F;
};

#endif // JSONREADER_H
