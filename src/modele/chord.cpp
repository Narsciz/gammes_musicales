#include "chord.h"

using namespace std;

Chord::Chord(Note f2, HarmonicStructure* hs2) : CS::CS(f2, hs2){
}

Chord::Chord(QString name){

    QStringList splittedName = name.split(':');

    if (splittedName.size() < 2)
        throw std::out_of_range("out of range");
    f = stringToNote(splittedName[0]);

    HarmonicStructure *hs2;
    if ((hs2 = ChordDictionary::getInstance()->getHSbyName(splittedName[1])) != NULL)
            hs = hs2;
    else
    {
        throw std::out_of_range("out of range");
    }
}

vector<Scale*> Chord::candidatesScales()
{
    vector<Scale*> res;
    vector<Scale*> searching_set = ScaleDictionary::getInstance()->getAllScales();

    for (size_t i = 0; i < searching_set.size(); i++)
        if (this->isContainedIn(searching_set[i]))
            res.push_back(searching_set[i]);

    return res;
}
