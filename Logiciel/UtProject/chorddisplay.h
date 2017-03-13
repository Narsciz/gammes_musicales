#ifndef CHORDDISPLAY_H
#define CHORDDISPLAY_H

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QIcon>
#include <QString>

#include <chord.h>

class ChordDisplay : public QGroupBox
{
private:
    QGridLayout *boxLayout;
    QPushButton *closeButton;
    QLabel *chordName;

public:
    ChordDisplay(QString note, QString hs);
};

#endif // CHORDDISPLAY_H
