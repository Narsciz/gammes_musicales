#include "mainwindow.h"
#include <QApplication>
#include "ut.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    Ut u();

    return  a.exec();
}
