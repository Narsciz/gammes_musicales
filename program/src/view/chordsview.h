#ifndef CHORDSVIEW_H
#define CHORDSVIEW_H


#include <QFrame>
#include <QStringList>
#include <QGridLayout>
#include <QPoint>
#include <QLabel>
#include <QGroupBox>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>

#include "modele/chord.h"

class ChordsView : public QFrame
{
private:
    QGridLayout *mainLayout;

    QLabel *name;
    QFrame *line;
    QLabel *pictureDisplayBase;
    QLabel *notesName;

    QVector<QLabel*> picturesDisplay;

public:
    ChordsView(QString chordName);
    void constructPictureDisplay(QStringList listNote);
    QVector<Note> notesSort(vector<Note> notesList);
    QStringList noteToString(QVector<Note> notesList);
};

#endif // CHORDSVIEW_H
