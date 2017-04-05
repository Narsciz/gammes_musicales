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
    SA.push_back(allowedChords[0]);
    SA.push_back(allowedChords[1]);
    SA.push_back(allowedChords[2]);

    //for (int i=0;i<ChordDictionary::getInstance()->getSize();i++)
      //    qInfo()<<ChordDictionary::getInstance()->getChordByIndex(i)->getName();
    qInfo()<<"suite d'accords :";

    for (int i=0;i<3;i++)
    {
        vector<Note> notes=SA[i]->getNotes();
        qInfo()<<SA[i]->getName();
    }

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
    vector<Scale*> vide;
    qInfo()<<"algo rec:";
    algo.generateSols(0,vide);
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
