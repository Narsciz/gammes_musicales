#ifndef ALGOBRUTOMEGA_H
#define ALGOBRUTOMEGA_H

#include "modele/algobrut.h"

class AlgoBrutOmega : public AlgoBrut
{
protected:
    int minOmega;
    std::vector<int> omegas;
public:
    AlgoBrutOmega(){}
    AlgoBrutOmega(std::vector<Chord*>,std::vector<Scale*>);

    void generateSolsRec(int,std::vector<Scale*>,int,int);

    void findLeastsConsecutivesNotesChanges();
    void findLeastsConsecutivesScalesChanges();
    void findLeastsTotalScales();


    void filterPossiblesSolutions();



};

#endif // ALGOBRUTOMEGA_H
