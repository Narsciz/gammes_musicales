#include "chordslistdisplay.h"

ChordsListDisplay::ChordsListDisplay() : QGroupBox()
{
    this->setTitle("Accords : ");
    this->setStyleSheet("background-color: rgb(255,255,255)");
    this->chordsLayout = new QGridLayout();

    this->chordsLayout->setAlignment(Qt::AlignTop);
    this->chordsLayout->setHorizontalSpacing(4);

    this->setLayout(this->chordsLayout);
}

QVector<ChordDisplay*> ChordsListDisplay::getListChords()
{
    return this->listChords;
}

void ChordsListDisplay::addChord(QString note, QString sh)
{
    this->listChords.push_back(new ChordDisplay(note, sh));
    QObject::connect(this->listChords.last(), SIGNAL(deleteSignal(ChordDisplay*)), this, SLOT(slotDeleteChord(ChordDisplay*)));
    this->refresh();
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

void ChordsListDisplay::clear()
{

    while(!this->listChords.isEmpty())
    {
        delete this->listChords.takeLast();
    }
    refresh();
}

void ChordsListDisplay::enableDeletingChords()
{
    for(int i=0; i<this->listChords.size(); i++)
    {
        listChords[i]->enableDelete();
    }
}

void ChordsListDisplay::disableDeletingChords()
{
    for(int i=0; i<this->listChords.size(); i++)
    {
        listChords[i]->disableDelete();
    }
}

void ChordsListDisplay::slotDeleteChord(ChordDisplay *cd)
{
    this->listChords.removeOne(cd);
    refresh();
}
