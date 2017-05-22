#ifndef CHORDSVIEW_H
#define CHORDSVIEW_H

//Bibliotheques Qt
#include <QFrame>
#include <QStringList>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPixmap>
#include <QPoint>
#include <QVBoxLayout>
#include <QVector>

//Classes
#include "modele/chord.h"
#include "modele/cs.h"

//fenêtre affichant toutes les informations et l'image d'un accord si constructeur appelé avec true, et d'une gamme si appelé avec false
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
    //Constructeurs
    ChordsView(QString chordName, bool isChord);
    ChordsView(QString name, vector<Note> notesList, bool isChord);
    void constructChordPictureDisplay(QStringList listNote);
    void constructScalePictureDisplay(QStringList listNote);

    //Méthodes
    QVector<Note> notesSort(vector<Note> notesList);
    QStringList noteToString(QVector<Note> notesList);
};

#endif // CHORDSVIEW_H
