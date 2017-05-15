#include "export.h"

using namespace std;

string note_To_String(Note n)
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

string noteToNoteXML(Note n, bool isFirstNote, string type, string duration,
                     int* precedingNoteOctave,
                     Note precedingNote,
                     string scaleName) {

    string note = CS::noteToString(n).toStdString();
    string precNote = CS::noteToString(precedingNote).toStdString();

    string lyric;
    string octave;
    string alter;
    string step;
    string precedingStep;

    stringstream converter;

    // Conversion de char en string pour recuperer la fonda dans step
    converter << note[0];
    converter >> step;

    converter.clear();

    converter << precNote[0];
    converter >> precedingStep;

    converter.clear();

    // Recuperation de l'alteration # ou bemol
    if (note.size() > 1)
        alter = (note[1] == '#') ? "+1" : "-1";
    else alter = "0";

    // Determine l'octave pour la note en fonction
    // de la note precedente
    if (step == "C" && step != precedingStep) {
        *precedingNoteOctave = *precedingNoteOctave + 1;
    }

    octave = to_string(*precedingNoteOctave);

    // Ajout du nom de la gamme si c'est la premiere note de la mesure
    if (isFirstNote) {
        lyric = "<lyric number=\"1\">\n"
                        "<syllabic>single</syllabic>\n"
                        "<text>" + scaleName + "</text>\n"
                    "</lyric>\n";

    }
    else lyric = "";

    // Ecriture au format music xml
    string noteXML ("<note>\n"
                    "<pitch>\n"
                        "<step>" + step + "</step>\n" +
                        ((alter != "0") ? "<alter>" + alter + "</alter>\n" : "") +
                        "<octave>" + octave + "</octave>\n"
                    "</pitch>\n"
                    "<duration>" + duration + "</duration>\n"
                    "<type>" + type + "</type>\n" +
                    lyric +
                "</note>\n");


    return noteXML;

}

//Create a QString XML Midi encoding for the scale s
string generateScalePartMeasure(Scale* s, int measureNumber) {

    stringstream converter;
    string measureXML;
    string measureN;
    string r;

    converter << measureNumber;
    converter >> measureN;

    measureXML = "\n<measure number=\"" + measureN + "\">\n";

    /* Si c'est la premiere mesure, il faut ajouter attributes
     pour ecrire la clef, la signature metrique, ... */
    if(measureNumber == 1)
        measureXML += "<attributes>\n"
                         "<divisions>2</divisions>\n"
                         "<key>\n"
                             "<fifths>0</fifths>\n"
                         "</key>\n"
                         "<time>\n"
                             "<beats>4</beats>\n"
                             "<beat-type>4</beat-type>\n"
                         "</time>\n"
                         "<clef>\n"
                             "<sign>G</sign>\n"
                             "<line>2</line>\n"
                         "</clef>\n"
                     "</attributes>";


    vector<Note> notesFromScale = s->getNotes();
    int index = 0;

    Note precedingNote;
    int* precedingNoteOctave = (int*)malloc(sizeof(int));
    bool endReached = false;

    *precedingNoteOctave = 4;

    for(size_t i = 0; i < 8; i++) {

        // Pour repeter les premieres notes quand une gamme a moins de 8 notes
        index = index % notesFromScale.size();

        if(i == 0) {
            measureXML += noteToNoteXML(notesFromScale[index], true, "eighth", "1",
                                        precedingNoteOctave,
                                        notesFromScale[index],
                                        s->getName().toStdString());

            precedingNote = notesFromScale[index];
        }
        else {
            measureXML += noteToNoteXML(notesFromScale[index], false, "eighth", "1",
                                        precedingNoteOctave,
                                        precedingNote,
                                        s->getName().toStdString());
            precedingNote = notesFromScale[index];
        }

        index++;
    }

    measureXML += "</measure>\n";

    return measureXML;
}

/*
* Generation de la part representant les scales.
* Une mesure par Scale du vector, 8 croches par mesure
* Pour les gammes qui ont moins de 8 notes, les notes sont
* repetees depuis le debut
*/
string generateScalePart(vector<Scale*> scales) {

    //XML Header for the scale part
    string content = "\n<part id=\"Scales\">";

    int i = 1;

    for(Scale* s : scales)
    {
        content += generateScalePartMeasure(s, i);
        i++;
    }

    content += "\n</part>";

    return content;
}

//Create a QString XML Midi encoding for the chord c
string chordXML(Chord c) {
    string r;

    for(Note n : c.getNotes()){
        r += (string)("<note>\n<pitch>\n<step>"
                      + note_To_String(n) +
                      "</step>\n<octave>4</octave>\n</pitch>\n<duration>4</duration>\n<type>whole</type>\n</note>\n");
    }

    return r;
}

//Create and save a XML Midi file path.xml for v, one of the solutions found by the main algorithm.
QString exportMusicXML(vector<Scale*> v1, vector<Chord*> v2)
{
    int i = 1;

    //XML Header
    QString content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                      "<!DOCTYPE score-partwise "
                            "PUBLIC \"-//Recordare//DTD MusicXML 3.0 Partwise//EN\" "
                            "\"http://www.musicxml.org/dtds/partwise.dtd\">\n"
                      "<score-partwise version=\"3.0\">";

    //Part List
    content += "\n<part-list>\n"
                    "<score-part id=\"Scales\">\n"
                        "<part-name>Gammes</part-name>\n"
                    "</score-part>\n"                
                "</part-list>";

    // Scale Part
    content += QString::fromStdString(generateScalePart(v1));


    content += "\n</score-partwise>";

    return content;
}
