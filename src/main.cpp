#include "../include/header.hpp"

using std::string;
using std::cout;;
void cout_info(Parser::pointsConfig points, Parser::windowConfig window) 
{
    cout << __cplusplus << "\n";
    
    cout << "expression: " << points.expression << "\n";
    cout << "range: " << points.range << "\n";
    cout << "axes color: " << window.colorAxes << "\n";
    cout << "bg color: " << window.colorBackground << "\n";
    cout << "line graph: " << window.colorFunctionGraph << "\n";
    cout << "height: " << window.height << "\n";
    cout << "width: " << window.width << "\n";
    int range = points.range * 100 * 2;
    for (int i = 0; i <= range; i++)
    {
        cout << points.array_x[i] << "\t" << points.array_y[i] << "\n";
    }
}

int main()
{
    string expression, background_color, color_axes, function_graph_color;
    int range = 0;
    Parser::pointsConfig points;
    Parser::windowConfig window;

    JSON::getData(points, window);

    Parser::getPoints<double>(points);
    cout_info(points, window);
}
