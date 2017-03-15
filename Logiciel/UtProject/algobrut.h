#ifndef ALGOBRUT_H
#define ALGOBRUT_H

#include <vector>
#include <scale.h>
class AlgoBrut
{
private:
    std::vector<std::vector<Scale*> > solutionsPossibles;
    std::vector<std::vector<Scale*> > KpartiteGraph;
public:
    AlgoBrut(std::vector<std::vector<Scale*> >);

    //ça c'est l'algo brut en dessous v
    void generateSols(int,std::vector<Scale*>);//use : generateSols(0,vector<Scale*> vide)
};

#endif // ALGOBRUT_H
