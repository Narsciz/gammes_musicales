#include "chord.h"

using namespace std;

Chord::Chord(Note f2, HarmonicStructure* hs2) : CS::CS(f2, hs2){
}

vector<Scale*> Chord::CandidatesScales()
{
    vector<Scale*> res;
    vector<Scale*> searching_set=ScaleDictionary::getInstance()->getAllScales();
    for (int i=0;i<searching_set.size();i++)
        if (this->isContainedIn(searching_set[i]))
            res.push_back(searching_set[i]);
    return res;
}
