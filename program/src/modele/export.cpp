#include <string>
#include "modele/note.h"
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

//Create a QString XML Midi encoding for the scale s
string scaleXML(Scale s){
    string r;
    for(Note n : s.getNotes()){
        r+=(string)("<note>\n<pitch>\n<step>"+note_To_String(n)+"</step>\n<octave>4</octave>\n</pitch>\n<duration>4</duration>\n<type>whole</type>\n</note>\n");
    }
    return r;
}

//Create a QString XML Midi encoding for the chord c
string chordXML(Chord c){
    string r;
    for(Note n : c.getNotes()){
        r+=(string)("<note>\n<pitch>\n<step>"+note_To_String(n)+"</step>\n<octave>4</octave>\n</pitch>\n<duration>4</duration>\n<type>whole</type>\n</note>\n");
    }
    return r;
}

//Create and save a XML Midi file path.xml for v, one of the solutions found by the main algorithm.
string exportMusicXML(vector<Scale*> v1,vector<Chord*> v2)
{
    int i=1;
    //XML Header
    string content=(string)("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE score-partwise PUBLIC \"-//Recordare//DTD MusicXML 3.0 Partwise//EN\" \"http://www.musicxml.org/dtds/partwise.dtd\">\n<score-partwise version=\"3.0\">");
    //Part List
    content+=(string)("\n<part-list>\n<score-part id=\"P"+to_string(1)+"\">\n<part-name>Part "+to_string(1)+"</part-name>\n</score-part><score-part id=\"P"+to_string(2)+"\">\n<part-name>Part "+to_string(2)+"</part-name>\n</score-part>\n</part-list>");
    //XML Header for the scale part
    content+=(string)("\n<part id=\"P"+to_string(1)+"\">");
    //XML Header for each scale
    for(Scale* s : v1)
    {
        content+=(string)("\n<measure number=\"1/4\">\n<attributes>\n<divisions>1</divisions>\n<key>\n<fifths>0</fifths>\n</key>\n<time>\n<beats>4</beats>\n<beat-type>4</beat-type>\n</time>\n<clef>\n<sign>G</sign>\n<line>2</line>\n</clef>\n</attributes>");
        content+=scaleXML(*s)+"\n</measure>";
    }
    content+=(string)("\n</part>");

    //XML Header for the chord part
    content+=(string)("\n<part id=\"P"+to_string(2)+"\">");
    //XML Header for each scale
    for(Chord* c : v2)
    {
        content+=(string)("\n<measure number=\"1/4\">\n<attributes>\n<divisions>1</divisions>\n<key>\n<fifths>0</fifths>\n</key>\n<time>\n<beats>4</beats>\n<beat-type>4</beat-type>\n</time>\n<clef>\n<sign>G</sign>\n<line>2</line>\n</clef>\n</attributes>");
        content+=chordXML(*c)+"\n</measure>";
    }
    content+=(string)("\n</part>");

    content+="\n</score-partwise>";
    return content;
}
