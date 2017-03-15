#include "scaledictionary.h"

using namespace std;

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

vector<Scale*> ScaleDictionary::getAllScales()
{
    vector<Scale*> res;
    for (int i=0;i<scales.size();i++)
        for (int j=0;j<12;j++)
        {
            res.push_back(new Scale((Note)j,scales[i]));
        }

}

ScaleDictionary *ScaleDictionary::INSTANCE=NULL;
