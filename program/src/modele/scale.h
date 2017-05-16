#ifndef SCALE_H
#define SCALE_H
#include "cs.h"
#include <QString>
#include <QStringList>

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
