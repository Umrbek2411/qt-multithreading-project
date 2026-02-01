#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.setWindowTitle("Qt Multithreading GUI");
    window.setMinimumSize(500, 300);
    window.show();
    
    return app.exec();
}
