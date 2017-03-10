#include "mainwindow.h"
#include <QApplication>
#include "ut.h"
#include <QMenuBar>
#include <QMenu>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QMainWindow *window = new QMainWindow();


    window->setWindowTitle(QString::fromUtf8("Ut"));
    window->resize(336, 227);

    QWidget *centralWidget = new QWidget(window);
    QMenuBar *menu = new QMenuBar(centralWidget);

    QMenu* menu1 = new QMenu("Fichier");
    menu1->addMenu(new QMenu("Nouveau"));

    QMenu* menu2 = new QMenu("Accords");
    menu2->addMenu(new QMenu("Ajouter"));

    QMenu* menu3 = new QMenu("Gammes");
    menu3->addMenu(new QMenu("Ajouter"));

    QMenu* menu4 = new QMenu("Options");

    menu->addMenu(menu1);
    menu->addMenu(menu2);
    menu->addMenu(menu3);
    menu->addMenu(menu4);

    window->setCentralWidget(centralWidget);

    window->show();
    return app.exec();
}
