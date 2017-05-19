#ifndef ABSTRACTALGO_H
#define ABSTRACTALGO_H

#include <vector>
#include <modele/chord.h>
#include <modele/scale.h>
#include <modele/algo.h>
#include <thread>

class AbstractAlgo
{
protected :

    std::vector<Chord*> data;
    std::vector<Scale*> allowedScales;
    std::vector<std::vector<Scale*> > results;
    std::vector<std::vector<Scale*> > KpartiteGraph;
    std::vector<std::vector<Scale*> > filteredKpartiteGraph;
    int resultsToDisplay = 2;

public:
    AbstractAlgo(){}
    AbstractAlgo(std::vector<Chord*> data, std::vector<Scale*> allowedScales);
    virtual ~AbstractAlgo(){};

    virtual void setLimit(int);

    void callConsecutivesNotesChangesInThread(std::thread&);
    void callConsecutivesScalesChangesInThread(std::thread&);
    void callTotalScalesInThread(std::thread&);

    void filterAllowedChordsInK();
    virtual void findLeastsConsecutivesNotesChanges() = 0;
    virtual void findLeastsConsecutivesScalesChanges() = 0;
    virtual void findLeastsTotalScales()=0;
    std::vector<std::vector<Scale*> > getResults();
    std::vector<std::vector<Scale*> > getFilteredKpartiteGraph();
};

#endif // ABSTRACTALGO_H
