#ifndef EXPORT
#define EXPORT
#include <QString>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "modele/cs.h"
#include "modele/scale.h"
#include "modele/chord.h"

//Create and save a XML Midi file path.xml for v1, one of the solutions found by the main algorithm for v2.
void exportSlot(vector<Scale*>, vector<Chord*>);

string generateScalePartNote(Note, bool, string, string, Note, int*, string);
string generateScalePartMeasure(Scale*, int);
string generateScalePart(vector<Scale*>);

string generateChordPartNote(Note, bool, string, string, Note, int*, string);
string generateChordPartMeasure(Chord*, int);
string generateChordPart(vector<Chord*>);

#endif // EXPORT
