#ifndef EXPORT
#define EXPORT
#include <QString>
#include <iostream>
#include <fstream>
#include <string>
#include "modele/note.h"

string note_To_String(Note n);

//Create a QString XML Midi encoding for the scale s
string scaleMIDI(Scale s);

//Create and save a XML Midi file path.xml for v, one of the solutions found by the main algorithm.
void exportSlot(vector<Scale*> v);

#endif // EXPORT
