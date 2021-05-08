#include <QApplication>
#include "mainwindow.h"
//
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.setWindowTitle("Поиск по машинам");
    window.show();
    return a.exec();
}
