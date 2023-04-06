#include "qt_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::setlocale(LC_NUMERIC,"C");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
