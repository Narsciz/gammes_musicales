#include "view/mainwindow.h"
#include <QApplication>
#include "controler/ut.h"
#include <QMenuBar>
#include <QMenu>
#include <iostream>
#include <QDebug>
#include<QStyleFactory>
#include "modele/algobrutomega.h"
#include "modele/algo.h"
#include "test/testfunctions.h"
#include "modele/export.h"
#include <windows.h>

using namespace std;


int main(int argc, char *argv[])
{

//    cout << "TEST ALGO BRUT" << endl << endl << flush;
//    testAlgo("brut", "consecutivesNotes");

//    cout << " ====================================== " << endl;

//    cout << "TEST ALGO BRUT OMEGA" << endl << endl << flush;
//    testAlgo("omega", "consecutivesNotes");

//    cout << " ====================================== " << endl << flush;

//    cout << "TEST ALGO OPTIMISE" << endl << endl << flush;
//    testAlgo("optimise", "consecutivesNotes", 2);

    QApplication app(argc, argv);

    MainWindow *window = new MainWindow();

    Ut controler(window);
    window->show();

    return app.exec();
}

