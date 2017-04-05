#include "cs.h"
#include "scaledictionary.h"
#include "chorddictionary.h"
#include <stdexcept>
#include <iostream>
using namespace std;

QString noteToString(Note n);
Note stringToNote(QString s);
CS::CS(Note f2, HarmonicStructure *hs2){
    f=f2;
    hs=hs2;
}

CS::CS(QString name){
    QStringList splittedName=name.split(':');
    cout<<"cs.cpp line 17 : splittedName.size() = " << splittedName.size() << endl << flush;
    if (splittedName.size()<2)
        throw std::out_of_range("out of range");
    f=stringToNote(splittedName[0]);
    HarmonicStructure *hs2;
    if ((hs2=ScaleDictionary::getInstance()->getHSbyName(splittedName[1]))!=NULL)
        hs=hs2;
    else if ((hs2=ChordDictionary::getInstance()->getHSbyName(splittedName[1]))!=NULL)
        hs=hs2;
    else hs=NULL;
}




QString CS::getName(){return noteToString(f)+":"+hs->getName();}

vector<Note> CS::getNotes(){
    vector<Note> n;
    int increment=0;
    int noteSuivante;
    n.push_back(f);
    for(size_t i=0;i<hs->getIntervals().size();i++){
        increment+=hs->getIntervals()[i];
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

HarmonicStructure* CS::getHS(){
    return hs;
}

void CS::setHS(HarmonicStructure *hs2){
    this->hs=hs2;
}


bool CS::ContainsNote(Note note,vector<Note> notes)
{
    for (size_t i=0;i<notes.size();i++)
        if (note==notes[i])
            return true;
    return false;
}

bool CS::isContainedIn(CS* c){//si une note de this n'est pas dans c, return false
    vector<Note> notes1=getNotes();
    vector<Note> notes2=c->getNotes();

    for (size_t i=0;i<notes1.size();i++)
        if (!ContainsNote(notes1[i],notes2))
            return false;
    return true;

}

bool CS::equals(CS * cs)
{
    if (cs->getF()==getF() && cs->getHS()->getName()==getHS()->getName())
            return true;
    else return false;
}

bool CS::sameNotes(CS * cs)
{
    vector<Note> notes1=getNotes();
    vector<Note> notes2=cs->getNotes();
    if (notes1.size()==notes2.size())
    {
        for (size_t i=0;i<notes1.size();i++)
            if (notes1[i]!=notes2[i])
                return false;
        return true;
    }
    return false;
}

Note stringToNote(QString s){

    if (s=="C")
        return C;
    if (s== "C#")
        return Csharp;
    if (s== "D")
        return D;
    if (s== "D#")
        return Dsharp;
    if (s== "E")
        return E;
    if (s== "F")
        return F;
    if (s== "F#")
        return Fsharp;
    if (s== "G")
        return G;
    if (s== "G#")
        return Gsharp;
    if (s== "A")
        return A;
    if (s== "A#")
        return Asharp;
    if (s== "B")
        return B;

    return END_OF_LIST;
}

QString noteToString(Note n)
{
    switch(n)
    {
    case 0:
        return "C";
        break;
    case 1:
        return "C#";
        break;
    case 2:
        return "D";
        break;
    case 3:
        return "D#";
        break;
    case 4:
        return "E";
        break;
    case 5:
        return "F";
        break;
    case 6:
        return "F#";
        break;
    case 7:
        return "G";
        break;
    case 8:
        return "G#";
        break;
    case 9:
        return "A";
        break;
    case 10:
        return "A#";
        break;
    case 11:
        return "B";
        break;
    default :
        return "Er";
    }
}
