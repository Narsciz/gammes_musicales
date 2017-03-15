#ifndef CHORD_H
#define CHORD_H
#include "cs.h"
#include "scale.h"
#include "scaledictionary.h"
class Chord : public CS
{
public:
    Chord(){}
    Chord(Note f2, HarmonicStructure* hs2);
    std::vector<Scale*> CandidatesScales();

};

#endif // CHORD_H
