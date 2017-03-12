#include "chordslistdisplay.h"

ChordsListDisplay::ChordsListDisplay() : QGroupBox()
{
    this->setTitle("Accords : ");
    this->setStyleSheet("background-color: rgb(255,255,255)");
    this->chordsLayout = new QGridLayout();
    this->setLayout(this->chordsLayout);
}

void ChordsListDisplay::addChord(QString note, QString sh)
{
    ChordDisplay *chord = new ChordDisplay(note, sh);
    this->listChords.push_back(chord);
    this->refresh();
}

void ChordsListDisplay::deleteChord(int i)
{

}

void ChordsListDisplay::refresh()
{
    /*
    for(int i=0; i<this->listChords.size(); i++)
        this->chordsLayout->removeWidget(this->listChords[i]);
    delete this->chordsLayout;
    this->chordsLayout = new QGridLayout();*/
    int i=0;
    int j=0;
    int k=0;
    int nb = 0;
    while(i<listChords.size())
    {
        if((i*60)+120>this->width() && !nb)
        {
            nb = k;
            k = 0;
            j++;
        }
        else
        {
            if(k>0 && k==nb)
            {
                k = 0;
                j++;
            }
        }
        this->chordsLayout->addWidget(this->listChords[i], j, k, 1, 1);
        k++;
        i++;
    }
}
