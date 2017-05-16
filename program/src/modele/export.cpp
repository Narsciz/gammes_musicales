#include "export.h"

using namespace std;

/*
 * PARAM :
 * n, de type Note (enum), determine le step et l'alteration dans l'element <note>.
 * isFirstNote, booleen qui determine si la note est la premiere de la mesure.
 * type, string qui determine la forme de la note (ronde, blanche, noire, ...).
 * duration, determine la duree de la note.
 * precedingNoteOctave, pointeur sur entier, sert a echelonner les hauteurs
 * pour obtenir une continuite dans la montee des notes.
 * scaleName, string portant le nom de la gamme dont la note fait partie.
 *
 * ACTION : Genere et retourne un element <note> au format MusicXML contenue
 * dans une mesure de la part des gammes.
 *
 */
string generateScalePartNote(Note n, bool isFirstNote, string type,
                                    string duration,
                                    Note precedingNote,
                                    int* precedingNoteOctave,
                                    string scaleName) {

    string note = CS::noteToString(n).toStdString();

    // elements xml enfants de l'element note
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

    converter << CS::noteToString(precedingNote).toStdString()[0];
    converter >> precedingStep;

    // Recuperation de l'alteration # ou bemol
    if (note.size() > 1)
        alter = (note[1] == '#') ? "+1" : "-1";
    else alter = "0";

    // Determine l'octave pour la note en fonction
    // de la note precedente
    if (!isFirstNote && step == "C" && precedingStep != "C") {
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

/*
* Genere une mesure de la part des gammes contenant
* les notes associees a la Scale s.
*/
string generateScalePartMeasure(Scale* s, int measureNumber) {

    stringstream converter;
    string measureXML;
    string measureN;

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

    // Octave de depart qui sera change par generateChordPartNote
    // Sert a echelonner de maniere ascendante les notes
    int* precedingNoteOctave = (int*)malloc(sizeof(int));
    *precedingNoteOctave = 4;

    for(size_t i = 0; i < 8; i++) {

        // Pour repeter les premieres notes quand une gamme a moins de 8 notes
        index = index % notesFromScale.size();

        if(i == 0) {
            measureXML += generateScalePartNote(notesFromScale[index], true, "eighth", "1",
                                                notesFromScale[index],
                                                precedingNoteOctave,
                                                s->getName().toStdString());
        }
        else {
            measureXML += generateScalePartNote(notesFromScale[index], false, "eighth", "1",
                                                precedingNote,
                                                precedingNoteOctave,
                                                s->getName().toStdString());
        }

        precedingNote = notesFromScale[index];
        index++;
    }

    measureXML += "</measure>\n";

    free(precedingNoteOctave);

    return measureXML;
}

/*
* ACTION : Genere et retourne l'element MusicXML <part> representant les scales.
* Une mesure par Scale du vector, 8 croches par mesure
* Pour les gammes qui ont moins de 8 notes, les notes sont
* repetees depuis le debut (pas encore de solution pour celles
* qui ont plus de 8 notes).
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

/*
 * PARAM :
 * n, de type Note (enum), determine le step et l'alteration dans l'element <note>.
 * isFirstNote, booleen qui determine si la note est la premiere de la mesure.
 * type, string qui determine la forme de la note (ronde, blanche, noire, ...).
 * duration, determine la duree de la note.
 * precedingNote, la note precedent la note courante dans l'accord.
 * precedingNoteOctave, pointeur sur entier, sert a echelonner les hauteurs
 * pour obtenir une continuite dans la montee des notes.
 * chordName, string portant le nom de l'accord dont la note fait partie.
 *
 * ACTION : Genere et retourne un element <note> au format MusicXML contenue
 * dans une mesure de la part des accords.
 *
 */
string generateChordPartNote(Note n, bool isFirstNote, string type,
                                    string duration,
                                    Note precedingNote,
                                    int* precedingNoteOctave,
                                    string chordName) {

    string note = CS::noteToString(n).toStdString();

    // elements xml enfants de l'element note
    string lyric;
    string octave;
    string alter;
    string step;
    string chord;

    string precedingStep;
    stringstream converter;

    // Conversion de char en string pour recuperer la fonda dans step
    converter << note[0];
    converter >> step;

    converter.clear();

    converter << CS::noteToString(precedingNote).toStdString()[0];
    converter >> precedingStep;

    // Recuperation de l'alteration # ou bemol
    if (note.size() > 1)
        alter = (note[1] == '#') ? "+1" : "-1";
    else alter = "0";

    // Determine l'octave pour la note en fonction
    // de la note precedente
    if (!isFirstNote && step == "C" && precedingStep != "C") {
        *precedingNoteOctave = *precedingNoteOctave + 1;
    }

    octave = to_string(*precedingNoteOctave);

    // Ajout du nom de la gamme si c'est la premiere note de la mesure
    if (isFirstNote) {
        lyric = "<lyric number=\"1\">\n"
                        "<syllabic>single</syllabic>\n"
                        "<text>" + chordName + "</text>\n"
                    "</lyric>\n";
        chord = "";

    }
    else {
        chord = "<chord/>\n";
        lyric = "";
    }

    // Ecriture au format music xml
    string noteXML ("<note>\n" +
                    chord +
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

/*
 * ACTION : Genere et retourne un elemeent MusicXML <measure>
 * contenant les notes de l'accord c jouees de maniere
 * continue et simultanee sur toute la duree de la mesure
 *
 */
string generateChordPartMeasure(Chord* c, int measureNumber) {

    stringstream converter;
    string measureXML;

    measureXML = "\n<measure number=\"" + to_string(measureNumber) + "\">\n";

    /* Si c'est la premiere mesure, il faut ajouter attributes
     pour ecrire la clef, la signature metrique, ... */
    if(measureNumber == 1)
        measureXML += "<attributes>\n"
                         "<divisions>1</divisions>\n"
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


    vector<Note> notesFromChord = c->getNotes();
    Note precedingNote;

    // Octave de depart qui sera change par generateChordPartNote
    // Sert a echelonner de maniere ascendante les notes
    int* precedingNoteOctave = (int*)malloc(sizeof(int));
    *precedingNoteOctave = 4;

    for(size_t i = 0; i < notesFromChord.size(); i++) {

        if(i == 0) {
            measureXML += generateChordPartNote(notesFromChord[i], true, "whole", "4",
                                                notesFromChord[i],
                                                precedingNoteOctave,
                                                c->getName().toStdString());
        }
        else {
            measureXML += generateChordPartNote(notesFromChord[i], false, "whole", "4",
                                                precedingNote,
                                                precedingNoteOctave,
                                                c->getName().toStdString());
        }

        // Mise a jour de la note precedente
        precedingNote = notesFromChord[i];

    }

    measureXML += "</measure>\n";

    free(precedingNoteOctave);

    return measureXML;
}

/*
 * PARAM :
 * chords, un vecteur de Chord* qui represente les accords
 * pour lesquels vont etre generees les mesures de chord part.
 *
 * ACTION : Genere et retourne un element MusicXML <part>
 * correspondant a la part des accords sur le fichier MusicXML
 * a exporter.
 *
 */
string generateChordPart(vector<Chord*> chords) {

    //XML Header for the chord part
    string content = "\n<part id=\"Chords\">";

    int i = 1;

    for(Chord* c : chords)
    {
        content += generateChordPartMeasure(c, i);
        i++;
    }

    content += "\n</part>";

    return content;
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
                    "<score-part id=\"Chords\">\n"
                        "<part-name>Accords</part-name>\n"
                    "</score-part>\n"
                "</part-list>";

    // Scale Part
    content += QString::fromStdString(generateScalePart(v1));

    // Chord part
    content += QString::fromStdString(generateChordPart(v2));

    content += "\n</score-partwise>";

    return content;
}
