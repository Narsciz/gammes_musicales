#include "view/mainwindow.h"
#include <QApplication>
#include "view/ut.h"
#include <QMenuBar>
#include <QMenu>
#include <iostream>
#include <QDebug>
#include "modele/algobrut.h"
using namespace std;
int main(int argc, char *argv[])
{



    //qInfo() <<(int)INFINITY;
    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    vector<Chord*> SA;
    //AlgoBrut algo;



    QApplication app(argc, argv);

    MainWindow *window = new MainWindow();

    window->show();
    return app.exec();
}
