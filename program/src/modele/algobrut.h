#ifndef ALGOBRUT_H
#define ALGOBRUT_H

#include <vector>
#include "modele/scale.h"
#include "modele/algo.h"

class AlgoBrut
{
private:
    std::vector<std::vector<Scale*> > solutionsPossibles;
    std::vector<std::vector<Scale*> > KpartiteGraph;
public:
    AlgoBrut(std::vector<std::vector<Scale*> >);

    //ça c'est l'algo brut en dessous v
    void generateSols(int,std::vector<Scale*>);//use : generateSols(0,vector<Scale*> vide)
    std::vector<std::vector<Scale*> > findLeastsConsecutivesNotesChanges();
    std::vector<std::vector<Scale*> > findLeastsConsecutivesScalesChanges();
    std::vector<std::vector<Scale*> > findLeastsTotalScales();
};

#endif // ALGOBRUT_H
