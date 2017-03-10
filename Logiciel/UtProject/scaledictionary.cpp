#include "scaledictionary.h"

ScaleDictionary::ScaleDictionary()
{

}

bool ScaleDictionary::contains(HSScale * s)
{
    for (int i=0;i<scales.size();i++)
        if (scales[i]==s)
            return true;
    return false;
}

ScaleDictionary *ScaleDictionary::getInstance()
{
    if (INSTANCE==NULL)
        INSTANCE=new ScaleDictionary;
    return INSTANCE;
}

ScaleDictionary *ScaleDictionary::INSTANCE=NULL;
