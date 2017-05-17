#ifndef SCALEDISPLAY_H
#define SCALEDISPLAY_H

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QIcon>
#include <QString>
#include "view/chordsview.h"

//
class ScaleDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QGridLayout *boxLayout;
    QPushButton *viewButton;
    QLabel *scaleName;
    QLabel *scaleAlias;
    ChordsView *scaleView;

public:
    ScaleDisplay(QString name);
    QString getName();
    QString getAlias();

public slots:
    void slotOpenView();
    void slotCloseView();
};

#endif // SCALEDISPLAY_H
