#include "view/mainwindow.h"
#include <QApplication>
#include "view/ut.h"
#include <QMenuBar>
#include <QMenu>
#include <iostream>
#include <QDebug>
using namespace std;
int main(int argc, char *argv[])
{



    //qInfo() <<(int)INFINITY;
    QApplication app(argc, argv);

    MainWindow *window = new MainWindow();

    window->show();
    return app.exec();
}
