#ifndef CHORDDICTIONARY_H
#define CHORDDICTIONARY_H

#include <vector>
#include "hschord.h"
#include "chord.h"
#include <QVector>
class ChordDictionary
{
private :
    static ChordDictionary* INSTANCE;
    std::vector<HSChord*> chords;
    ChordDictionary();
public:
    int getSize();
    static ChordDictionary * getInstance();
    HSChord* getChordByIndex(int);
    HSChord* getHSbyName(QString);
    bool contains(HSChord*);
    void add(HSChord*);
    void generateBaseChords();
    std::vector<Chord*> getAllChords();
    QVector<QString> getHSnames();

};

#endif // CHORDDICTIONARY_H
