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


void ScaleDictionary::generateBaseScale()
{
    getInstance()->add(new HSScale("majeur",{2,2,1,2,2,2,1}));
    //http://www.solfego.fr/toutes-les-gammes.htm
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
            res.push_back(new Scale((Note)j,scales[i]));
    return res;

}

void ScaleDictionary::add(HSScale *h){scales.push_back(h);}
ScaleDictionary *ScaleDictionary::INSTANCE=NULL;
