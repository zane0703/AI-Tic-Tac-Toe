#include <QApplication>
#include "mainwindow.h"
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    srand(time(NULL));
    w.show();
    return a.exec();
}
