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
    ScalesDisplay(QVector<QString> scaleList);
    void refresh();
    QVector<QString> getListScale();
};

#endif // SCALESDISPLAY_H
