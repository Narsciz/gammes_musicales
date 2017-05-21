#ifndef ALGOBRUT_H
#define ALGOBRUT_H

//Bibliotheques c++
#include <iomanip>
#include <iostream>
#include <time.h>
#include <vector>

//Bibliotheques Qt
#include <QFile>
#include <QTextStream>

//Classes
#include "modele/abstractalgo.h"
#include "modele/algo.h"
#include "modele/scale.h"

class AlgoBrut : public AbstractAlgo
{
protected:
    std::vector<std::vector<Scale*> > possiblesSolutions;

public:
    AlgoBrut(){}
    AlgoBrut(std::vector<Chord*>,std::vector<Scale*>);
    ~AlgoBrut(){};

    //ça c'est l'algo brut en dessous v
    std::vector<std::vector<Scale*> > getSols();
    void generatePossiblesSolutions();
    void generateSolsRec(int, std::vector<Scale*>);//use : generateSols(0,vector<Scale*> vide)
    void findLeastsConsecutivesNotesChanges();
    void findLeastsConsecutivesScalesChanges();
    void findLeastsTotalScales();
};

#endif // ALGOBRUT_H
