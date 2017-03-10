#include "cs.h"

CS::CS(Note f2, HarmonicStructure hs2){
    f=f2;
    hs=hs2;
}

vector<Note> CS::getNotes(){
    vector<Note>* n=new vector<Note>();
    return *n;
}

Note CS::getF(){
    return this->getF();
}

void CS::setF(Note f2){
    this->f=f2;
}

HarmonicStructure CS::getHS(){
    return this->hs;
}

void CS::setHS(HarmonicStructure hs2){
    this->hs=hs2;
}
