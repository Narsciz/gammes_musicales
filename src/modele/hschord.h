#ifndef HSCHORD_H
#define HSCHORD_H

//Classes
#include "modele/harmonicstructure.h"

class HSChord : public HarmonicStructure
{
public:
    HSChord();
    HSChord(QString,std::vector<int>, QString alias = "");
    HSChord(QString);
};

#endif // HSCHORD_H
