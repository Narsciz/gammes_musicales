#ifndef ABSTRACTALGO_H
#define ABSTRACTALGO_H

#include <vector>
#include <modele/chord.h>
#include <modele/scale.h>

class AbstractAlgo
{
private :
    std::vector<Chord*> data;
    std::vector<Scale*> allowedScales;
    std::vector<std::vector<Scale*> > soluces;

public:
    AbstractAlgo(std::vector<Chord*> data, std::vector<Scale*> allowedScales);

    virtual void findLeastsConsecutivesNotesChanges() = 0;
    virtual void findLeastsConsecutivesScalesChanges() = 0;
    virtual void findLeastsTotalScales()=0;
    std::vector<std::vector<Scale*> > getSoluces();
};

#endif // ABSTRACTALGO_H
