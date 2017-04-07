#ifndef PARAMETRES_H
#define PARAMETRES_H

#include "modele/scale.h"
#include "view/parametersdisplay.h"
#include <QString>

class Parametres
{
private:
    int parameter;
    int algo;
    QVector<QString> allowedScales;

public:
    Parametres(ParametersDisplay view);
    int getParameter();
    int getAlgo();
    QVector<QString> getAllowedScales();
};

#endif // PARAMETRES_H
