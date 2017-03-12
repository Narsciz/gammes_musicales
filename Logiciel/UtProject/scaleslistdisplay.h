#ifndef SCALESDISPLAYLAYOUT_H
#define SCALESDISPLAYLAYOUT_H

#include <QGroupBox>

//Layout affichant les gammes générées, "hidden" avant lancement de l'algorithme, "visible" après lancement
class ScalesListDisplay : public QGroupBox
{
    Q_OBJECT

public:
    ScalesListDisplay();
};

#endif // SCALESDISPLAYLAYOUT_H
