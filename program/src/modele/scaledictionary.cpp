#include "scaledictionary.h"

using namespace std;

ScaleDictionary::ScaleDictionary()
{

}

bool ScaleDictionary::contains(HSScale * s)
{
    for (size_t i=0;i<scales.size();i++)
        if (scales[i]->getIntervals()==s->getIntervals())
            return true;
    return false;
}

vector<Scale*> ScaleDictionary::getScalesByTypes(QVector<QString> hsScales)//paramètre : liste des structures harmoniques
{
    vector<Scale*> res;
    for (size_t i=0;i<hsScales.size();i++)
        for (int j=0;j<12;j++)
            res.push_back(new Scale((Note)j,getHSbyName(hsScales[i])));
    return res;
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
    getInstance()->add(new HSScale("m",{2,1,2,2,1,3}));
    getInstance()->add(new HSScale("M",{2,2,1,2,2,2}));

    //http://www.solfego.fr/toutes-les-gammes.htm
}


HSScale* ScaleDictionary::getHSbyName(QString s){
    for (size_t i=0;i<scales.size();i++)
        if (scales[i]->getName()==s)
            return scales[i];
    return NULL;
}

QVector<QString> ScaleDictionary::getHSnames(){
    QVector<QString> res;
    for (size_t i=0;i<scales.size();i++)
        res.push_back(scales[i]->getName());
    return res;
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
    for (size_t i=0;i<scales.size();i++)
        for (int j=0;j<12;j++)
            res.push_back(new Scale((Note)j,scales[i]));
    return res;

}

void ScaleDictionary::add(HSScale *h){if (!contains(h)) scales.push_back(h);}
ScaleDictionary *ScaleDictionary::INSTANCE=NULL;
