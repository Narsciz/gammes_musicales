#ifndef HSSCALE_H
#define HSSCALE_H

//Classes
#include "modele/harmonicstructure.h"

class HSScale : public HarmonicStructure
{
public:
    HSScale();
    HSScale(QString,std::vector<int>, QString alias = "");
};

#endif // HSSCALE_H
