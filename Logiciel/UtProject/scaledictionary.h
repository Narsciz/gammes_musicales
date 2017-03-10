#ifndef SCALEDICTIONARY_H
#define SCALEDICTIONARY_H

#include <vector>
#include "hsscale.h"

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



};

#endif // SCALEDICTIONARY_H
