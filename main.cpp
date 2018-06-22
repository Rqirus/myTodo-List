#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

/**
*@projectName    myTodo-list
*@brief          brief
*@author         Rqirus
*@date           2018-6-22
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
