#include <QApplication>
#include "mainwindow.hpp"
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //a.setStyle("Fusion");
    srand(time(NULL));
    w.show();
    return a.exec();
}
