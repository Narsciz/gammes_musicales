#include "scale.h"
#include "algo.h"

using namespace std;

Scale::Scale(Note f2, HarmonicStructure* hs2) : CS::CS(f2, hs2){
}

Scale::Scale(QString name) {

    QStringList splittedName=name.split(':');

    if (splittedName.size()<2)
        throw std::out_of_range("out of range");
    f=stringToNote(splittedName[0]);
    HarmonicStructure *hs2;
    if ((hs2=ScaleDictionary::getInstance()->getHSbyName(splittedName[1]))!=NULL)
        hs=hs2;
    else hs=NULL;

}

int Scale::notesDifferencesWithScale(Scale* s)// on fait union-intersection des deux gammes, vu que c'est l'opération qu'on avait dit qu'on utiliserait
{
    vector<Note> Union;
    vector<Note> intersection;

    vector<Note> notes1=getNotes();
    vector<Note> notes2=s->getNotes();

    cout<<"diff"<<endl;
    Union=notes1;
    for (size_t i=0;i<notes2.size();i++)
    {
        if(isNoteInNotes(notes2[i],notes1))
            intersection.push_back(notes2[i]);
        else Union.push_back(notes2[i]);
    }
    return Union.size()-intersection.size();
}
