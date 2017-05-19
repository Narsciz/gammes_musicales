#include "deletechordsscalesview.h"

DeleteChordsScalesView::DeleteChordsScalesView(bool isChord, QWidget *parent) : QWidget(parent)
{
    this->isChord = isChord;

    this->mainLayout = new QGridLayout();

    this->namesLayout = new QVBoxLayout();
    this->viewLayout = new QVBoxLayout();
    this->deleteLayout = new QVBoxLayout();

    constructLayouts();

    this->returnButton = new QPushButton("Retour");

    this->mainLayout->addLayout(namesLayout, 0, 0, 1, 1);
    this->mainLayout->addLayout(viewLayout, 0, 1, 1, 1);
    this->mainLayout->addLayout(deleteLayout, 0, 2, 1, 1);
    this->mainLayout->addWidget(returnButton, 1, 0, 1, 3);

    this->setLayout(mainLayout);
}

void DeleteChordsScalesView::constructLayouts()
{
    constructNameLayout();
    constructViewLayout();
    constructDeleteLayout();
}

void DeleteChordsScalesView::constructNameLayout()
{
    this->HSNames.clear();
    QVector<QString> temp;
    if(isChord)
        temp = ChordDictionary::getInstance()->getCustomHSnames();
    else
    {
        this->ScaleName = ScaleDictionary::getInstance()->getCustomHSnames();
        temp = ScaleDictionary::getInstance()->getCustomHSalias();
    }
    for(int i=0; i<temp.size(); i++)
    {
        this->HSNames.push_back(new QLabel(temp[i]));
        this->namesLayout->addWidget(HSNames.last());
    }
}

void DeleteChordsScalesView::constructViewLayout()
{
    for(int i=0; i<HSNames.size(); i++)
    {
        this->HSView.push_back(new QPushButton("Afficher"));
        this->viewLayout->addWidget(HSView.last());
        connect(HSView.last(), SIGNAL(pressed()), this, SLOT(openViewSlot()));
        connect(HSView.last(), SIGNAL(released()), this, SLOT(closeViewSlot()));
    }
}

void DeleteChordsScalesView::constructDeleteLayout()
{
    for(int i=0; i<HSNames.size(); i++)
    {
        this->HSDelete.push_back(new QPushButton("Supprimer"));
        this->deleteLayout->addWidget(HSDelete.last());
    }
}

void DeleteChordsScalesView::openViewSlot()
{
    QPushButton* temp = (QPushButton *)sender();
    int i = HSView.indexOf(temp);
    cout<<"i = "<<i<<endl<<flush;
    if(isChord)
    {
        cout<<"enter if with isChord true"<<endl<<flush
           <<"Create chord for chordView"<<endl<<flush
          <<"     HSNames[i] = "<<HSNames[i]->text().toStdString()<<endl<<flush;
        chordView = new ChordsView(HSNames[i]->text(), isChord);
    }
    else
        chordView = new ChordsView(ScaleName[i], isChord);
    chordView->show();
}

void DeleteChordsScalesView::closeViewSlot()
{
    chordView->close();
}

void DeleteChordsScalesView::deleteSlot()
{

}
