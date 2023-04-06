#include "points.h"


Points::Points()
{
    readDataFromJson();
    number_of_points = range * (1 / step) * 2;
};

Points::~Points()
{
    free(array_x);
    free(array_y);
    std::cout << "arrays destroyed\n";
}

void Points::init(string expr)
{
    expr = replace(expr, " ");
    expression = replace(expr, "y=");
    array_x = (double*)malloc(sizeof(double) * number_of_points);
    array_y = (double*)malloc(sizeof(double) * number_of_points);
    fillArrays();
}

void Points::fillArrays()
{
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;

    double x;
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();
    expression_t expr_t;
    expr_t.register_symbol_table(symbol_table);
    parser_t parser;
    parser.compile(expression, expr_t);
    {
        int i = 0;
        x = -range;
        for (; x <= +range; i++, x += step)
        {
            const double y = expr_t.value();
            *(array_x + i) = x;
            *(array_y + i) = -y;
        }
    }
}

void Points::readDataFromJson()
{
    std::ifstream jsonFile(json_filename);
    assert(jsonFile.is_open());
    json parsedFile = json::parse(jsonFile);
    jsonFile.close();
    range = stoi(parsedFile["points"]["range"].dump());
    step = parsedFile["points"]["step"].get<double>();;
}

string Points::replace(string str, string to_remove)
{
    while (str.find(to_remove) != std::string::npos)
        str.replace(str.find(to_remove), to_remove.length(), "");
    return str;
}
