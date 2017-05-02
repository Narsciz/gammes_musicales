#ifndef ABSTRACTALGO_H
#define ABSTRACTALGO_H

#include <vector>
#include <modele/chord.h>
#include <modele/scale.h>
#include <modele/algo.h>

class AbstractAlgo
{
protected :
    std::vector<Chord*> data;
    std::vector<Scale*> allowedScales;
    std::vector<std::vector<Scale*> > results;
    std::vector<std::vector<Scale*> > KpartiteGraph;
    std::vector<std::vector<Scale*> > filteredKpartiteGraph;

public:
    AbstractAlgo(){}
    AbstractAlgo(std::vector<Chord*> data, std::vector<Scale*> allowedScales);


    void filterAllowedChordsInK();
    virtual void findLeastsConsecutivesNotesChanges() = 0;
    virtual void findLeastsConsecutivesScalesChanges() = 0;
    virtual void findLeastsTotalScales()=0;
    std::vector<std::vector<Scale*> > getResults();
};

#endif // ABSTRACTALGO_H
