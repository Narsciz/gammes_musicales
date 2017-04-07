#include "parametres.h"

Parametres::Parametres(ParametersDisplay view)
{
    this->parameter = view.getParameter();
    this->algo = view.getAlgo();
    this->allowedScales = view.getlistAllowedScales();
}

int Parametres::getParameter()
{
    return this->parameter;
}

int Parametres::getAlgo()
{
    return this->algo;
}

QVector<QString> Parametres::getAllowedScales()
{
    return this->allowedScales;
}
