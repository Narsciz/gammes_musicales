#ifndef CHORD_H
#define CHORD_H
#include "cs.h"

class Chord : public CS
{
public:
    Chord(){}
    Chord(Note f2, HarmonicStructure hs2);
};

#endif // CHORD_H
