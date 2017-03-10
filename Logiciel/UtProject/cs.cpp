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
