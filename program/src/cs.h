#ifndef CS_H
#define CS_H
#include "note.h"
#include "harmonicstructure.h"

class CS
{
private:
    Note f;
    HarmonicStructure *hs;
public:
    CS(){}

    CS(Note f2, HarmonicStructure *hs2);
    std::vector<Note> getNotes();

    Note getF();
    void setF(Note f2);
    HarmonicStructure* getHS();
    void setHS(HarmonicStructure *hs2);

    bool ContainsNote(Note,std::vector<Note>);
    bool isContainedIn(CS*);

    bool equals(CS*); // comparaison entre 2 gammes/accords, on comparera seulement les noms de HS et de la fondamentale dans un souci de performance, donc il faut faire gaffe à ce qu'il y ait jamais deux structures harmoniques identiques avec des noms différents, et jamais deux HS différentes avec un même nom (faudra sûrement géré ça dans les dicos)
    bool sameNotes(CS*); //bon, du coup j'ai mis cette fonction aussi qui compare les notes plutôt, moins performant, mais on est sûr de les comparer correctement
};

#endif // CS_H
