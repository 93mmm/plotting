#include "application.h"
#include "gui_window.h"
#include "./ui_mainwindow.h"

using std::string;
using std::cout;;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{

}


void MainWindow::on_actionSave_As_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::on_actionPlot_Graph_triggered()
{
    Window::pointsCFG.expression = ui->plainTextEdit->textCursor().selectedText().toStdString();
    Window::SetPointsConfig<double>();
    Window::SetWindowConfig();
    Window::MovePoints(Window::windowCFG.width / 2, Window::windowCFG.height / 2);
    Window::CreateWindow();
}

template <typename T>
void Window::SetPointsConfig()
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);
    pointsCFG.range = stoi(parsedFile["points"]["range"].dump());
    pointsCFG.step = 0.01;
    jsonFile.close();

    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T>   expression_t;
    typedef exprtk::parser<T>       parser_t;

    T x;
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();
    expression_t expression;
    expression.register_symbol_table(symbol_table);
    parser_t parser;
    parser.compile(pointsCFG.expression, expression);
    {
        int i = 0;
        int range = pointsCFG.range;
        double step = 0.01;
        for (x = T(-range); x <= T(+range); i++, x += T(step))
        {
            const T y = expression.value();
            pointsCFG.arrayX[i] = x;
            pointsCFG.arrayY[i] = y;
        }
    }
}

void Window::MovePoints(double moveX, double moveY)
{
    int range = pointsCFG.range * (1 / pointsCFG.step) * 2;
    for (int i = 0; i < range; i++)
    {
        pointsCFG.arrayX[i] += moveX;
        pointsCFG.arrayY[i] += moveY;
        cout << pointsCFG.arrayX[i] << "\t" << pointsCFG.arrayY[i] << "\n";
    }
}

void Window::SetWindowConfig()
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);

    windowCFG.width = stoi(parsedFile["window"]["width"].dump());
    windowCFG.height = stoi(parsedFile["window"]["height"].dump());

    windowCFG.colorAxes[0] = stoi(parsedFile["window"]["colorAxes"][0].dump());
    windowCFG.colorAxes[1] = stoi(parsedFile["window"]["colorAxes"][1].dump());
    windowCFG.colorAxes[2] = stoi(parsedFile["window"]["colorAxes"][2].dump());

    windowCFG.colorBackground[0] = stoi(parsedFile["window"]["colorBackground"][0].dump());
    windowCFG.colorBackground[1] = stoi(parsedFile["window"]["colorBackground"][1].dump());
    windowCFG.colorBackground[2] = stoi(parsedFile["window"]["colorBackground"][2].dump());

    windowCFG.colorFunctionGraph[0] = stoi(parsedFile["window"]["colorFunctionGraph"][0].dump());
    windowCFG.colorFunctionGraph[1] = stoi(parsedFile["window"]["colorFunctionGraph"][1].dump());
    windowCFG.colorFunctionGraph[2] = stoi(parsedFile["window"]["colorFunctionGraph"][2].dump());

}

void Window::RenderWindow()
{

}

void Window::CreateWindow()
{
    sf::RenderWindow window(sf::VideoMode(windowCFG.width, windowCFG.height), "");
    
    sf::Vertex x_axis[] =
    {
        sf::Vertex(sf::Vector2f(windowCFG.width / 2, 0)),
        sf::Vertex(sf::Vector2f(windowCFG.width / 2, windowCFG.height))
    };

    sf::Vertex y_axis[] =
    {
        sf::Vertex(sf::Vector2f(0, windowCFG.height / 2)),
        sf::Vertex(sf::Vector2f(windowCFG.width, windowCFG.height / 2))
    };

    Window::MovePoints(windowCFG.height / 2, windowCFG.width / 2);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(x_axis, 2, sf::Lines);
        window.draw(y_axis, 2, sf::Lines);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
