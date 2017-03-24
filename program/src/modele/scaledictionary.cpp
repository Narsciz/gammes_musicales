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
    /*getInstance()->add(new HSScale("Aéolien",{2,1,2,2,1,2}));
    getInstance()->add(new HSScale("Aélien(b5)",{2,1,2,1,2,2}));
    getInstance()->add(new HSScale("Altéré superlocrien",{1,2,1,2,2}));
    getInstance()->add(new HSScale("Arabe",{2,2,1,1,2}));
    getInstance()->add(new HSScale("Bartock",{2,2,2,1,2,1}));
    getInstance()->add(new HSScale("Blues(heptatonique)",{3,2,1,1,3,1}));
    getInstance()->add(new HSScale("Demi-ton tons sans sixte",{1,2,1,2,1,3}));
    getInstance()->add(new HSScale("Dorien",{2,1,2,2,2,1}));
    getInstance()->add(new HSScale("Enigmatique",{1,3,2,2,2,1}));
    getInstance()->add(new HSScale("Espagnole(première forme)",{1,3,2,2,2,1}));
    getInstance()->add(new HSScale("Gitane",{1,3,1,2,2,1}));
    getInstance()->add(new HSScale("Gypsy",{1,3,1,2,1,3}));
    getInstance()->add(new HSScale("Hindou",{2,2,1,2,1,2}));*/
    getInstance()->add(new HSScale("Mineur harmonique",{2,1,2,2,1,3}));
    getInstance()->add(new HSScale("Majeur",{2,2,1,2,2,2}));

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
