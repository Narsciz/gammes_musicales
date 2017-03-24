#ifndef HSSCALE_H
#define HSSCALE_H
#include "harmonicstructure.h"

class HSScale : public HarmonicStructure
{
public:
    HSScale();
    HSScale(QString,std::vector<int>);
};

#endif // HSSCALE_H
