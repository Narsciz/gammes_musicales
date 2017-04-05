#include "chordslistdisplay.h"

ChordsListDisplay::ChordsListDisplay() : QGroupBox()
{
    this->setTitle("Accords : ");
    this->setStyleSheet("background-color: rgb(255,255,255)");
    this->chordsLayout = new QGridLayout();

    this->chordsLayout->setAlignment(Qt::AlignTop);
    this->chordsLayout->setHorizontalSpacing(4);

    this->setMinimumSize(400, 160);
    this->setContentsMargins(10, 10, 10, 10);

    /*this->baseLayout = new QGridLayout();
    this->scrolledWidget = new QWidget();
    this->scrollArea = new QScrollArea();*/

    this->setLayout(this->chordsLayout);

    /*this->baseLayout->addWidget(scrollArea);
    this->scrollArea->setWidget(scrolledWidget);
    this->scrolledWidget->setLayout(chordsLayout);*/
}

QVector<ChordDisplay*> ChordsListDisplay::getListChords()
{
    return this->listChords;
}

QVector<QString> ChordsListDisplay::getListChordsName()
{
    QVector<QString> res;
    for(int i = 0; i<this->listChords.size(); i++)
    {
        res.push_back(listChords[i]->getName());
    }
    return res;
}

void ChordsListDisplay::addChord(QString note, QString sh)
{
    this->listChords.push_back(new ChordDisplay(note, sh));
    QObject::connect(this->listChords.last(), SIGNAL(deleteSignal(ChordDisplay*)), this, SLOT(slotDeleteChord(ChordDisplay*)));
    this->refresh();
}

void ChordsListDisplay::addChord(QString chord)
{
    this->listChords.push_back(new ChordDisplay(chord));
    QObject::connect(this->listChords.last(), SIGNAL(deleteSignal(ChordDisplay*)), this, SLOT(slotDeleteChord(ChordDisplay*)));
    this->refresh();
}

void ChordsListDisplay::refresh()
{
    int i=0;
    int j=0;
    int k=0;
    int nb = 0;
    while(i<this->listChords.size())
    {
        if((i*64)+80>this->width() && !nb)
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
    //this->scrolledWidget->setFixedHeight(93+(j*66));
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
