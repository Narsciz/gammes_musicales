#include "scale.h"
#include "algo.h"

using namespace std;

Scale::Scale(Note f2, HarmonicStructure* hs2) : CS::CS(f2, hs2){
}

int Scale::notesDifferencesWithScale(Scale* s)// on fait union-intersection des deux gammes, vu que c'est l'opération qu'on avait dit qu'on utiliserait
{
    vector<Note> Union;
    vector<Note> intersection;

    vector<Note> notes1=getNotes();
    vector<Note> notes2=s->getNotes();

    Union=notes1;
    intersection=notes1;
    for (size_t i=0;i<notes2.size();i++)
    {
        if(isNoteInNotes(notes2[i],notes1))
        {
            Union.push_back(notes2[i]);
            for (size_t j=0;j<intersection.size();j++)
                if (intersection[j]==notes2[j])
                    intersection.erase(intersection.begin()+j);
        }
    }

    return Union.size()-intersection.size();
}
