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
    QVBoxLayout *mainLayout;

    QLabel *name;
    QFrame *line;
    QLabel *pictureDisplayBase;
    QLabel *dieseBase;
    QLabel *notesName;

    QGridLayout *picturesDisplayLayout;
    QVector<QLabel*> picturesDisplay;

    QLabel *packerLabel;
public:
    ChordsView(QString chordName, bool isChord);
    ChordsView(QString name, vector<Note> notesList, bool isChord);
    void constructChordPictureDisplay(QStringList listNote);
    void constructScalePictureDisplay(QStringList listNote);
    QVector<Note> notesSort(vector<Note> notesList);
    QStringList noteToString(QVector<Note> notesList);
};

#endif // CHORDSVIEW_H
