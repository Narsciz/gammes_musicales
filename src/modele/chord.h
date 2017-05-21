#ifndef CHORD_H
#define CHORD_H

//Bibliotheques c++
#include <iostream>
#include <stdexcept>

//Bibliotheques Qt
#include <QStringList>

//Classes
#include "modele/chorddictionary.h"
#include "modele/cs.h"
#include "modele/scale.h"
#include "modele/scaledictionary.h"

class Chord : public CS
{
public:
    Chord(){}
    Chord(QString name);
    Chord(Note f2, HarmonicStructure* hs2);
    std::vector<Scale*> candidatesScales();

};

#endif // CHORD_H
