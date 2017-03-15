#ifndef CS_H
#define CS_H
#include "note.h"
#include "harmonicstructure.h"

class CS
{
private:
    Note f;
    HarmonicStructure hs;
public:
    CS(){}

    CS(Note f2, HarmonicStructure hs2);
    std::vector<Note> getNotes();

    Note getF();
    void setF(Note f2);
    HarmonicStructure getHS();
    void setHS(HarmonicStructure hs2);

    bool ContainsNote(Note,vector<Note>);
    bool isContainedIn(CS);
};

#endif // CS_H
