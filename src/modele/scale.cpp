#include "scale.h"
#include "algo.h"

using namespace std;

Scale::Scale(Note f2, HarmonicStructure* hs2) : CS::CS(f2, hs2){
}

Scale::Scale(QString name) {

    QStringList splittedName = name.split(':');

    if (splittedName.size() < 2)
        throw std::out_of_range("out of range");

    f = stringToNote(splittedName[0]);

    HarmonicStructure *hs2;

    if ((hs2 = ScaleDictionary::getInstance()->getHSbyName(splittedName[1])) != NULL)
        hs = hs2;
    else throw std::out_of_range("out of range");

}

// on fait union-intersection des deux gammes,
// vu que c'est l'opération qu'on avait dit qu'on utiliserait
int Scale::notesDifferencesWithScale(Scale* scaleToCompare)
{
    // contient les notes de la gamme courante
    // + les notes de scaleToCompare qui ne sont pas dans la gamme courante
    vector<Note> noteSetUnion;

    // ensemble des notes communes aux deux gammes
    vector<Note> notesInCommon;

    vector<Note> noteSet = getNotes();
    vector<Note> noteSetToCompare = scaleToCompare->getNotes();

    noteSetUnion = noteSet;
    for (size_t i = 0; i < noteSetToCompare.size(); i++)
    {
        if(isNoteInNotes(noteSetToCompare[i], noteSet))
            notesInCommon.push_back(noteSetToCompare[i]);

        else noteSetUnion.push_back(noteSetToCompare[i]);
    }

    return noteSetUnion.size() - notesInCommon.size();
}
