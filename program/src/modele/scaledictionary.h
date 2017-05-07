#ifndef SCALEDICTIONARY_H
#define SCALEDICTIONARY_H

#include <vector>
#include "modele/hsscale.h"
#include "modele/scale.h"
#include <QVector>
class ScaleDictionary
{
private:
    static ScaleDictionary* INSTANCE;
    std::vector<HSScale*> scales;

    ScaleDictionary();

public:
    static ScaleDictionary* getInstance();
    vector<Scale*> getScalesByTypes(QVector<QString>);
    HSScale* getScaleByIndex(int);
    HSScale* getHSbyName(QString);
    bool contains(HSScale*);
    void add(HSScale*);
    std::vector<Scale*> getAllScales();
    void generateBaseScale();
    QVector<QString> getHSnames();

};

#endif // SCALEDICTIONARY_H
