#include "view/mainwindow.h"
#include <QApplication>
#include "controler/ut.h"
#include <QMenuBar>
#include <QMenu>
#include <iostream>
#include <QDebug>
#include "modele/algobrutOmega.h"
#include "modele/algo.h"
using namespace std;


int main(int argc, char *argv[])
{
    //qInfo() <<(int)INFINITY;
    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    vector<Chord*> SA;
    vector<Chord*> allowedChords=ChordDictionary::getInstance()->getAllChords();
    vector<Scale*> allowedScales=ScaleDictionary::getInstance()->getAllScales();
    allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();

    for (int i=0;i<4;i++)
        SA.push_back(allowedChords[i]);

    cout<<"suite d'accords :"<<endl<<flush;
    for (size_t i=0;i<SA.size();i++)
        cout<<SA[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    cout<<"gammes autorisées"<<endl<<flush;
    for (size_t i=0;i<allowedScales.size();i++)
        cout<<allowedScales[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    AlgoBrutOmega algo(SA,ScaleDictionary::getInstance()->getAllScales());
    algo.findLeastsTotalScales();
    vector<vector<Scale*> > contrainte1=algo.getResults();

    cout<<"solution :"<<endl<<flush;
    for (size_t i=0;i<contrainte1.size();i++)
    {
        QString ligne="";
        for (size_t j=0;j<contrainte1[i].size();j++)
            ligne+="|"+contrainte1[i][j]->getName();
        cout<<ligne.toStdString()<<endl<<flush;
    }

    cout<<endl<<flush;

    QApplication app(argc, argv);

    MainWindow *window = new MainWindow();

    Ut controler(window);
    window->show();

    return app.exec();
}
