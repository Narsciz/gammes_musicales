#include "mainwindow.h"
#include <QApplication>
#include "ut.h"
#include <QMenuBar>
#include <QMenu>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    MainWindow *window = new MainWindow();

    window->show();
    return app.exec();
}
