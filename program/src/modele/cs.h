#ifndef CS_H
#define CS_H
#include "note.h"
#include "harmonicstructure.h"
#include <string>
#include <QStringList>


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
