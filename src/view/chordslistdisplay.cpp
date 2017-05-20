#include "chordslistdisplay.h"

ChordsListDisplay::ChordsListDisplay() : QGroupBox()
{
    this->setTitle("Accords : ");
    this->chordsLayout = new QGridLayout();

    this->chordsLayout->setAlignment(Qt::AlignTop);
    this->chordsLayout->setHorizontalSpacing(4);

    this->setMinimumSize(446, 100);
    this->setContentsMargins(5, 5, 5, 5);

    this->scrollArea = new QScrollArea();
    this->baseLayout = new QVBoxLayout();
    this->scrolledWidget = new QWidget();
    this->scrolledWidget->setLayout(chordsLayout);

    this->setLayout(baseLayout);
    this->baseLayout->addWidget(scrollArea);
    this->scrollArea->setWidget(scrolledWidget);
    this->scrollArea->setWidgetResizable(true);
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
        if((i*64)+100>this->width() && !nb)
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
    this->repaint();
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

void ChordsListDisplay::removeChordByHs(HSChord *hs)
{
    for(int i = 0; i<listChords.size(); i++)
    {
        QStringList temp = listChords[i]->getName().split(":");
        cout<<"temp[0] = "<<temp[0].toStdString()<<", temp[1] = "<<temp[1].toStdString()<<endl;
        cout<<"hs.getName()"<<hs->getName().toStdString()<<endl;
        if(temp[1] == hs->getName())
        {
            ChordDisplay *temp = listChords[i];
            listChords.remove(i);
            delete temp;
            i--;
        }
    }
    refresh();

}
