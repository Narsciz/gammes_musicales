#ifndef CHORDSDISPLAYLAYOUT_H
#define CHORDSDISPLAYLAYOUT_H

//Bibliotheques c++
#include <iostream>
#include <typeinfo>

//Bibliotheques Qt
#include <QGroupBox>
#include <QGridLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QString>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

//Classes
#include "modele/hschord.h"
#include "view/chorddisplay.h"

using namespace std;

//Box affichant les accords choisit par l'utilisateur
class ChordsListDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout *baseLayout;
    QGridLayout *chordsLayout;
    QScrollArea *scrollArea;
    QVector<ChordDisplay*> listChords;

    QWidget *scrolledWidget;

public:
    //Constructeurs
    ChordsListDisplay();//Constructeur par défaut utilisé pour construire un affichage sans accord
    ChordsListDisplay(QString file);//Constructeur utilisé lors de l'importation d'un fichier texte

    //Accesseurs
    QVector<ChordDisplay*> getListChords();
    QVector<QString> getListChordsName();

    //Gestion des Accords
    void addChord(QString note, QString sh); //Ajoute un accord a la suite de ceux déjà choisit par l'utilisateur
    void addChord(QString chord);
    void refresh();
    void enableDeletingChords();
    void disableDeletingChords();
    void removeChordByHs(HSChord *hs);
public slots:
    void slotDeleteChord(ChordDisplay *cd);
};

#endif // CHORDSDISPLAYLAYOUT_H
