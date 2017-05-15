#ifndef EXPORT
#define EXPORT
#include <QString>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "modele/cs.h"

string note_To_String(Note n);

//Create a QString XML Midi encoding for the scale s
string scaleMIDI(Scale s);

//Create a QString XML Midi encoding for the chord c
string chordMIDI(Chord c);

//Create and save a XML Midi file path.xml for v1, one of the solutions found by the main algorithm for v2.
void exportSlot(vector<Scale*> v1, vector<Chord*> v2);

string noteToNoteXML(Note n, bool isFirstNote, string type, string duration,
                     int* precedingNoteOctave,
                     Note precedingNote,
                     string scaleName);
string scaleToMusicXML(Scale* s);

string generateScalePartMeasure(Scale* s, int measureNumber);
string generateScalePart(vector<Scale*> scales);


#endif // EXPORT
