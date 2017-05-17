#include "parametres.h"

Parametres::Parametres(ParametersDisplay view)
{
    this->parameter = view.getParameter();
    this->algo = view.getAlgo();
    this->allowedScales = view.getlistAllowedHSscales();
}

int Parametres::getParameter()
{
    return this->parameter;
}

int Parametres::getAlgo()
{
    return this->algo;
}

QVector<QString> Parametres::getAllowedHSscales()
{
    return this->allowedScales;
}
