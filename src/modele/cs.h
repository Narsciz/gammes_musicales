#ifndef CS_H
#define CS_H

//Bibliotheques c++
#include <string>

//Bibliotheques Qt
#include <QStringList>

//Classes
#include "modele/harmonicstructure.h"
#include "modele/note.h"

class CS
{

protected:
    Note f;
    HarmonicStructure *hs;

public:
    CS(){}

    CS(Note f2, HarmonicStructure *hs2);
    std::vector<Note> getNotes();

    QString getName();
    QString getAlias();

    Note getF();
    void setF(Note f2);
    HarmonicStructure* getHS();
    void setHS(HarmonicStructure *hs2);

    bool ContainsNote(Note,std::vector<Note>);
    bool isContainedIn(CS*);

    static Note stringToNote(QString s);
    static QString noteToString(Note n);

    bool equals(CS*);
    bool sameNotes(CS*);

};

#endif // CS_H
