#ifndef HSCHORD_H
#define HSCHORD_H
#include "harmonicstructure.h"

class HSChord : public HarmonicStructure
{
public:
    HSChord();
    HSChord(QString,std::vector<int>);
    HSChord(QString);
};

#endif // HSCHORD_H
