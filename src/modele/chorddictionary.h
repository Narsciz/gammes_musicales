#ifndef CHORDDICTIONARY_H
#define CHORDDICTIONARY_H

//Bibliotheques c++
#include <vector>

//Bibliotheques Qt
#include <QFile>
#include <QTextStream>
#include <QVector>

//Classes
#include "modele/hschord.h"

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

    void fillCustomTextFile();




};

#endif // CHORDDICTIONARY_H
