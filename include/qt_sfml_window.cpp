#include "sfml_window.h"
#include "qt_window.h"
#include "./ui_mainwindow.h"
#include <math.h>

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
    Win sfml_win;
    sfml_win.SetPointsConfig(ui->plainTextEdit->textCursor().selectedText().toStdString());
    sfml_win.RunWindow();
}

void Win::InitVertexArrays()
{
    int side = windowCFG.side;
    axes[0].position = sf::Vector2f(side / 2, 0);
    axes[1].position = sf::Vector2f(side / 2, side);
    axes[2].position = sf::Vector2f(0, side / 2);
    axes[3].position = sf::Vector2f(side, side / 2);
}

void Win::CheckEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::MouseWheelMoved)
        {
            cout << windowCFG.scaleCoef
                 << "\n"
                 << event.mouseWheel.delta
                 << "\n";
            /*
            if (windowCFG.scaleCoef <= 1 and event.mouseWheel.delta == 1)
            {

            } else if (windowCFG.scaleCoef <= 1 and event.mouseWheel.delta == 1)
            {
                
            }
            */
            if (windowCFG.scaleCoef > 1 and windowCFG.scaleCoef < 2000)
            {
                windowCFG.scaleCoef = windowCFG.scaleCoef * (1 + 0.01 * event.mouseWheel.delta);
            }
        }
    }
}
void Win::DrawGrid()
{
    window.draw(axes);
}

void Win::DrawPoints()
{
    {
        int range = pointsCFG.range * (1 / pointsCFG.step) * 2;
        for (int i = 0; i < range; i++)
        {
            sf::Color color = sf::Color::White;
            double x = -pointsCFG.arrayX[i] * windowCFG.scaleCoef + windowCFG.side / 2;
            double y = -pointsCFG.arrayY[i] * windowCFG.scaleCoef + windowCFG.side / 2;

            sf::Vertex point(sf::Vector2f(x, y), color);
            window.draw(&point, 1, sf::Points);
        }
    }
}

void Win::GetDataFromJSON()
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);
    jsonFile.close();

    windowCFG.side = stoi(parsedFile["window"]["side"].dump());
    windowCFG.scaleCoef = windowCFG.side / 20;

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

void Win::SetPointsConfig(string exp)
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);
    pointsCFG.range = stoi(parsedFile["points"]["range"].dump());
    pointsCFG.step = 0.001;
    pointsCFG.expression = exp;
    jsonFile.close();

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;

    double x;
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
        double step = pointsCFG.step;
        for (x = -range; x <= +range; i++, x += step)
        {
            const double y = expression.value();
            pointsCFG.arrayX[i] = x;
            pointsCFG.arrayY[i] = y;
        }
    }
    cout << pointsCFG.arrayX[0] << " "
         << pointsCFG.arrayY[0];
}

void Win::RunWindow()
{
    GetDataFromJSON();
    InitVertexArrays();
    window.create(sf::VideoMode(windowCFG.side, windowCFG.side), "");
    while (window.isOpen())
    {
        CheckEvent();
        // drawing
        window.clear();
        DrawGrid();
        DrawPoints();
        window.display();
    }
}
