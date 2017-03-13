#ifndef SCALESDISPLAY_H
#define SCALESDISPLAY_H

#include <QVector>
#include <QPushButton>

#include "scaledisplay.h"

class ScalesDisplay
{
private:
    QVector<ScaleDisplay*> scaleList;
    QPushButton *saveButton;

public:
    ScalesDisplay(QVector<QString> scaleList);
};

#endif // SCALESDISPLAY_H
