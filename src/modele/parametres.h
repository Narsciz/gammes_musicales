#ifndef PARAMETRES_H
#define PARAMETRES_H

//Bibliotheques Qt
#include <QString>

//Classes
#include "modele/scale.h"
#include "view/parametersdisplay.h"

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
    QVector<QString> getAllowedHSscales();
};

#endif // PARAMETRES_H
