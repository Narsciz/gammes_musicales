#ifndef CHORDSDISPLAYLAYOUT_H
#define CHORDSDISPLAYLAYOUT_H

#include <QGroupBox>
#include <QGridLayout>
#include <QVector>
#include <QString>

//temp
#include <iostream>
using namespace std;

#include "chorddisplay.h"

//Layout affichant les accords choisit par l'utilisateur
class ChordsListDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QGridLayout *chordsLayout;
    QVector<ChordDisplay*> listChords;

public:
    //Constructeurs
    ChordsListDisplay();//Constructeur par défaut utilisé pour construire un affichage sans accord
    ChordsListDisplay(QString file);//Constructeur utilisé lors de l'importation d'un fichier texte

    //
    void addChord(QString note, QString sh); //Ajoute un accord a la suite de ceux déjà choisit par l'utilisateur
    void deleteChord(int i); //Supprime l'accord d'indice i dans le vecteur et refresh l'affichage
    void refresh();
};

#endif // CHORDSDISPLAYLAYOUT_H
