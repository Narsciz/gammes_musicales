#ifndef CHORDDISPLAY_H
#define CHORDDISPLAY_H

//Bibliotheques Qt
#include <QGridLayout>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QString>

//Classes
#include "modele/chord.h"
#include "view/chordsview.h"

//Box affichant un accord
class ChordDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QGridLayout *boxLayout;
    QPushButton *deleteButton;
    QPushButton *viewButton;
    QLabel *chordName;
    QString note;
    QString hs;
    ChordsView *chordsView;

public:
    ChordDisplay(QString note, QString sh);
    ChordDisplay(QString chord);
    void disableDelete();
    void enableDelete();
    QString getName();

public slots:
    void slotDeleteButton();
    void slotOpenView();
    void slotCloseView();

signals:
    void deleteSignal(ChordDisplay *cd);
};

#endif // CHORDDISPLAY_H
