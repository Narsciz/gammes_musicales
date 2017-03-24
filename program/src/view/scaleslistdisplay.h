#ifndef SCALESDISPLAYLAYOUT_H
#define SCALESDISPLAYLAYOUT_H

#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QString>

#include "scalesdisplay.h"

//Layout affichant les gammes générées, "hidden" avant lancement de l'algorithme, "visible" après lancement
class ScalesListDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QGridLayout *scalesFoundLayout;
    QVector<ScalesDisplay*> listScales;
    QVector<QPushButton*> listSaveButtons;

public:
    ScalesListDisplay();
    void constructScalesFoundList(QVector<QVector<QString> > listFoundScales);
};

#endif // SCALESDISPLAYLAYOUT_H
