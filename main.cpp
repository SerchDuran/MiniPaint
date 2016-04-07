#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Begin the UI creation
    QApplication a(argc, argv);
    MainWindow w; //MainWindow object creation
    w.show();     //show UI
    
    return a.exec();
}
