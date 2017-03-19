#ifndef SCALE_H
#define SCALE_H
#include "cs.h"

class Scale : public CS
{
public:
    Scale(){}
    int notesDifferencesWithScale(Scale*);//pour la contrainte du moins de changement de notes consécutifs entre deux gammes

    Scale(Note f2, HarmonicStructure* hs2);
};

#endif // SCALE_H
