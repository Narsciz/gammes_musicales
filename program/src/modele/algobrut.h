#ifndef ALGOBRUT_H
#define ALGOBRUT_H

#include <vector>
#include "modele/scale.h"
#include "modele/algo.h"
#include <iostream>
#include "modele/abstractalgo.h"

class AlgoBrut : public AbstractAlgo
{
protected:
    std::vector<std::vector<Scale*> > possiblesSolutions;
public:
    AlgoBrut(){}
    AlgoBrut(std::vector<Chord*>,std::vector<Scale*>);

    //ça c'est l'algo brut en dessous v
    std::vector<std::vector<Scale*> > getSols();
    void generatePossiblesSolutions();
    void generateSolsRec(int, std::vector<Scale*>);//use : generateSols(0,vector<Scale*> vide)
    void findLeastsConsecutivesNotesChanges();
    void findLeastsConsecutivesScalesChanges();
    void findLeastsTotalScales();
};

#endif // ALGOBRUT_H
