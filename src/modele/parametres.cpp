#include "parametres.h"

/**
 * @brief Parametres::Parametres
 * @param view
 */
Parametres::Parametres(ParametersDisplay view)
{
    this->parameter = view.getParameter();
    this->algo = view.getAlgo();
    this->allowedScales = view.getlistAllowedHSscales();
}

/**
 * @brief Parametres::getParameter
 * @return
 */
int Parametres::getParameter()
{
    return this->parameter;
}

/**
 * @brief Parametres::getAlgo
 * @return
 */
int Parametres::getAlgo()
{
    return this->algo;
}

/**
 * @brief Parametres::getAllowedHSscales
 * @return
 */
QVector<QString> Parametres::getAllowedHSscales()
{
    return this->allowedScales;
}
