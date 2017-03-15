#include "cs.h"
using namespace std;

CS::CS(Note f2, HarmonicStructure hs2){
    f=f2;
    hs=hs2;
}

vector<Note> CS::getNotes(){
    vector<Note> n;
    int increment=0;
    int noteSuivante;
    n.push_back(f);
    for(int i=0;i<hs.getIntervals().size();i++){
        increment+=hs.getIntervals()[i];
        noteSuivante=(f+increment)%12;
        n.push_back((Note)noteSuivante);
    }
    return n;
}

Note CS::getF(){
    return f;
}

void CS::setF(Note f2){
    this->f=f2;
}

HarmonicStructure CS::getHS(){
    return hs;
}

void CS::setHS(HarmonicStructure hs2){
    this->hs=hs2;
}


bool CS::ContainsNote(Note note,vector<Note> notes)
{
    for (int i=0;i<notes.size();i++)
        if (note==notes[i])
            return true;
    return false;
}

bool CS::isContainedIn(CS c){//si une note de this n'est pas dans c, return false
    vector<Note> notes1=getNotes();
    vector<Note> notes2=c.getNotes();

    for (int i=0;i<notes1.size();i++)
        if (!ContainsNote(notes1[i],notes2))
            return false;
    return true;

}
