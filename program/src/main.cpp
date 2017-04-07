#include "view/mainwindow.h"
#include <QApplication>
#include "controler/ut.h"
#include <QMenuBar>
#include <QMenu>
#include <iostream>
#include <QDebug>
#include "modele/algobrut.h"
#include "modele/algo.h"
using namespace std;


int main(int argc, char *argv[])
{



    //qInfo() <<(int)INFINITY;
    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    vector<Chord*> SA;
    vector<Chord*> allowedChords=ChordDictionary::getInstance()->getAllChords();
    for (int i=0;i<4;i++)
        SA.push_back(allowedChords[i]);


    //for (int i=0;i<ChordDictionary::getInstance()->getSize();i++)
      //    qInfo()<<ChordDictionary::getInstance()->getChordByIndex(i)->getName();

    qInfo()<<"suite d'accords :";

    for (size_t i=0;i<SA.size();i++)
        qInfo()<<SA[i]->getName();

    qInfo()<<"graphe k-partie :";
    vector<vector<Scale*> > K=KpartitesScales(SA);
    for (size_t i=0;i<K.size();i++)
    {
        QString ligne="";
        for (size_t j=0;j<K[i].size();j++)
            ligne+="|"+K[i][j]->getName();
        qInfo()<<ligne;
    }
    AlgoBrut algo(K);
    qInfo()<<"algo rec:";
    algo.generateSols();
    vector<vector<Scale*> > sols=algo.getSols();

    /*qInfo()<<"liste combinaison :";
    for (int i=0;i<sols.size();i++)
    {
        QString ligne="";
        for (int j=0;j<sols[i].size();j++)
            ligne+="|"+sols[i][j]->getName();
        qInfo()<<ligne;
    }*/

    vector<vector<Scale*> > contrainte1=algo.findLeastsTotalScales();

    qInfo()<<"solution :";
    for (size_t i=0;i<contrainte1.size();i++)
    {
        QString ligne="";
        for (size_t j=0;j<contrainte1[i].size();j++)
            ligne+="|"+contrainte1[i][j]->getName();
        qInfo()<<ligne;
    }


    //vector<Note> notes=


    QApplication app(argc, argv);

    MainWindow *window = new MainWindow();

    Ut controler(window);
    window->show();

    return app.exec();
}
