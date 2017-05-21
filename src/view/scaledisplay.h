#ifndef SCALEDISPLAY_H
#define SCALEDISPLAY_H

//Bibliotheques Qt
#include <QGridLayout>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QString>

//Classes
#include "view/chordsview.h"

//Box affichant une gamme
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
