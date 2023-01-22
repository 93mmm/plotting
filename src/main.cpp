#include "../include/header.hpp"

using std::string;
using std::cout;;
void cout_info(Parser::pointsConfig points, Window::windowConfig window) 
{
    int range;

    cout << __cplusplus << "\n"
         << "expression: " << points.expression << "\n"
         << "range: " << points.range << "\n"
         << "axes color: " << window.colorAxes << "\n"
         << "bg color: " << window.colorBackground << "\n"
         << "line graph: " << window.colorFunctionGraph << "\n"
         << "height: " << window.height << "\n"
         << "width: " << window.width << "\npoints:\n";

    range = points.range * 100 * 2;
    for (int i = 0; i <= range; i++)
    {
        cout << points.array_x[i] << "\t" << points.array_y[i] << "\n";
    }
}

int main()
{
    string expression, background_color, color_axes, function_graph_color;
    Parser::pointsConfig points;
    Window::windowConfig window;
    int range = 0;

    JSON::getData(points, window);
    Parser::getPoints<double>(points);
    cout_info(points, window);
}
