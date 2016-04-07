#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //creación de la interfaz

    QApplication a(argc, argv);
    MainWindow w; //instanciamos el objeto de tipo MainWindow
    w.show();     //mostramos la interfaz gráfica
    
    return a.exec();
}
