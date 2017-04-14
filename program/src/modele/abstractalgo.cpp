#include "abstractalgo.h"

AbstractAlgo::AbstractAlgo(std::vector<Chord*> data, std::vector<Scale*> allowedScales)
{
    this->data = data;
    this->allowedScales = allowedScales;
}

std::vector<std::vector<Scale*> > AbstractAlgo::getResults()
{
    return this->results;
}
