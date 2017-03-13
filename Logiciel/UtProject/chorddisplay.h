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
    Q_OBJECT

private:
    QGridLayout *boxLayout;
    QPushButton *deleteButton;
    QPushButton *viewButton;
    QLabel *chordName;

public:
    ChordDisplay(QString note, QString sh);
    void disableDelete();
    void enableDelete();

public slots:
    void slotDeleteButton();

signals:
    void deleteSignal(ChordDisplay *cd);
};

#endif // CHORDDISPLAY_H
