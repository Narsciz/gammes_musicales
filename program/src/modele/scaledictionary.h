#ifndef SCALEDICTIONARY_H
#define SCALEDICTIONARY_H

#include <vector>
#include "modele/hsscale.h"
#include "modele/scale.h"

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
    void add(HSScale*);
    std::vector<Scale*> getAllScales();
    void generateBaseScale();

};

#endif // SCALEDICTIONARY_H
