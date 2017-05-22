#ifndef SCALESDISPLAY_H
#define SCALESDISPLAY_H

//Bibliotheques Qt
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QVector>

//Classes
#include "scaledisplay.h"

//Box affichant une suite de gammes
class ScalesDisplay : public QGroupBox
{
private:
    QGridLayout *scalesLayout;
    QVector<ScaleDisplay*> scalesList;

public:
    //Constructeur
    ScalesDisplay(QString name, QVector<QString> scaleList);

    //Accesseur
    QVector<QString> getListScale();

    //Méthode
    void refresh(int width);
};

#endif // SCALESDISPLAY_H
