#ifndef CHORDDICTIONARY_H
#define CHORDDICTIONARY_H

#include <vector>
#include "hschord.h"
#include <QVector>
#include <QFile>

class Chord;
class ChordDictionary
{
private :
    static ChordDictionary* INSTANCE;
    std::vector<HSChord*> chords;
    std::vector<HSChord*> customChords;
    ChordDictionary();

public:
    int getSize();
    static ChordDictionary * getInstance();

    HSChord* getChordByIndex(int);

    HSChord* getHSbyName(QString);

    bool contains(HSChord*);

    void add(HSChord*);
    void addCustom(HSChord*);
    void removeCustom(HSChord*);

    void generateBaseChords();
    void generateCustomChords();

    std::vector<Chord*> getAllChords();
    std::vector<Chord*> getBaseChords();
    std::vector<Chord*> getCustomChords();

    QVector<QString> getHSnames();
    QVector<QString> getBaseHSnames();
    QVector<QString> getCustomHSnames();




};

#endif // CHORDDICTIONARY_H
