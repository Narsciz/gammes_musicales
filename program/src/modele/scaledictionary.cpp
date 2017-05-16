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

//paramètre : hsScales, liste des structures harmoniques
vector<Scale*> ScaleDictionary::getScalesByTypes(QVector<QString> hsScales)
{
    vector<Scale*> res;
    for (size_t i=0;i<hsScales.size();i++)
        for (int j=0;j<12;j++)
            res.push_back(new Scale((Note)j, getHSbyName(hsScales[i])));
    return res;
}

void ScaleDictionary::generateBaseScale()
{
    /**/
    getInstance()->add(new HSScale("mh", {2, 1, 2, 2, 1, 3}, "Mineure harmonique"));
    getInstance()->add(new HSScale("mm", {2, 1, 2, 2, 2, 2}, "Mineure mélodique"));
    getInstance()->add(new HSScale("M", {2, 2, 1, 2, 2, 2}, "Majeure"));
    getInstance()->add(new HSScale("Pm", {3, 2, 2, 3}, "Pentatonique mineure"));
    getInstance()->add(new HSScale("Pb", {3, 2, 1, 1, 3}, "Pentatonique blues"));
    getInstance()->add(new HSScale("PM", {2, 2, 3, 2}, "Pentatonique majeure"));
    getInstance()->add(new HSScale("Egpt", {2, 1, 3, 1, 1, 3}, "Egyptienne"));
    getInstance()->add(new HSScale("Btk", {2, 2, 2, 1, 2, 1}, "Bartok"));
    getInstance()->add(new HSScale("Ton", {2, 2, 2, 2, 2}, "Par ton"));
    getInstance()->add(new HSScale("Dim", {1, 2, 1, 2, 1, 2, 1}, "Diminuee"));

}


HSScale* ScaleDictionary::getHSbyName(QString s){

    for (size_t i = 0; i < scales.size(); i++)
        if (scales[i]->getName() == s)
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
    if (INSTANCE == NULL)
        INSTANCE = new ScaleDictionary;
    return INSTANCE;
}

vector<Scale*> ScaleDictionary::getAllScales()
{
    vector<Scale*> res;
    for (size_t i = 0; i<scales.size(); i++)
        for (int j = 0; j < 12; j++)
            res.push_back(new Scale((Note)j, scales[i]));
    return res;

}

void ScaleDictionary::add(HSScale *h) {
    if (!contains(h))
        scales.push_back(h);
}

ScaleDictionary *ScaleDictionary::INSTANCE = NULL;
