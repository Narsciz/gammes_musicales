#ifndef ALGOOPTI_H
#define ALGOOPTI_H

#include "modele/abstractalgo.h"
#include "modele/node.h"
#include <time.h>
#include <iomanip>
#include <QFile>
#include <QTextStream>
#include <time.h>
#include <iomanip>
#include "./test/testfunctions.h"

class AlgoOpti : public AbstractAlgo
{
protected:
    std::vector<std::vector<Node*> > GAKO;

public:
    AlgoOpti(){}
    AlgoOpti(std::vector<Chord*> data, std::vector<Scale*> allowedScales);
    ~AlgoOpti(){};

    static std::vector<std::vector<Node*> > KpartitesToGAKO(std::vector<std::vector<Scale*> >);
    void findLeastsConsecutivesNotesChanges();
    void findLeastsConsecutivesScalesChanges();
    void findLeastsTotalScales(){}
    void calculatePCCs(std::string);
    void release(Node*, Node*, std::string);
    void releaseList(Node*,Node*,std::string);
    int ponderation(Node*, Node*, std::string);
    void generateSolutions(Node*,std::vector<Scale*>);
};

#endif // ALGOOPTI_H
