#ifndef SCALEDICTIONARY_H
#define SCALEDICTIONARY_H

#include <vector>
#include "hsscale.h"
#include "scale.h"

class ScaleDictionary
{
private:
    static ScaleDictionary* INSTANCE;
    std::vector<HSScale*> scales;
    ScaleDictionary();

public:
    static ScaleDictionary* getInstance();
    HSScale* getScaleByIndex(int);
    bool contains(HSScale*);

    std::vector<Scale*> getAllScales();

};

#endif // SCALEDICTIONARY_H
