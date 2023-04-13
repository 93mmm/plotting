#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../include/exprtk.hpp"

using std::string;
using json = nlohmann::json;

class Points
{
public:
    Points();
    ~Points();
    void init(string expr);

    double *array_x;
    double *array_y;

    int number_of_points;

private:
    void fillArrays();
    void readDataFromJson();

    string replace(string str, string to_remove);

    double step;

    int range;

    string expression;
    string json_filename = "json/settings.json";
};
