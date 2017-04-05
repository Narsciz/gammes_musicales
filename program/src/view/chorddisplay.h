#ifndef CHORDDISPLAY_H
#define CHORDDISPLAY_H

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QIcon>
#include <QString>

#include <QWindow>
#include <QScreen>

#include <modele/chord.h>

class ChordDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QGridLayout *boxLayout;
    QPushButton *deleteButton;
    QPushButton *viewButton;
    QWindow *view;
    QLabel *chordName;
    QString note;
    QString hs;

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
