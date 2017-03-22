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
    QPushButton *saveButton;

public:
    ScalesDisplay(QVector<QString> scaleList);
    void refresh();
};

#endif // SCALESDISPLAY_H
