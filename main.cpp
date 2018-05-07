#include "mainwindow.h"
#include <QApplication>
#include <random>
#include <ctime>

int main(int argc, char *argv[])
{
    // random seed from current time for generating random weights
    std::srand(std::time(0));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
