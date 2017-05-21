#ifndef SCALE_H
#define SCALE_H

//Bibliotheques Qt
#include <QString>
#include <QStringList>

//Classes
#include "modele/cs.h"


class Scale : public CS
{

public:

    Scale(){}
    Scale(QString name);

    //pour la contrainte du moins de changement de notes consécutifs entre deux gammes
    int notesDifferencesWithScale(Scale*);
    Scale(Note f2, HarmonicStructure* hs2);
};

#endif // SCALE_H
