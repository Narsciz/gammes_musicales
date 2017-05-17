#ifndef SCALESDISPLAY_H
#define SCALESDISPLAY_H

#include <QVector>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>

#include "scaledisplay.h"

class ScalesDisplay : public QGroupBox
{
private:
    QGridLayout *scalesLayout;
    QVector<ScaleDisplay*> scalesList;

public:
    ScalesDisplay(QString name, QVector<QString> scaleList);
    void refresh(int width);
    QVector<QString> getListScale();
};

#endif // SCALESDISPLAY_H
