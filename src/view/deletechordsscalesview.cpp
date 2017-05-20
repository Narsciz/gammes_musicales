#include "deletechordsscalesview.h"

DeleteChordsScalesView::DeleteChordsScalesView(bool isChord, QWidget *parent) : QWidget(parent)
{
    this->isChord = isChord;

    this->setMinimumSize(250, 100);

    this->mainLayout = new QGridLayout();

    if(isChord)
        if(ChordDictionary::getInstance()->getCustomHSnames().size()>0)
            constructLayouts();
        else
            this->mainLayout->addWidget(new QLabel("Aucun accord personalisé"), 0, 0, 1, 3);
    else
        if(ScaleDictionary::getInstance()->getCustomHSnames().size()>0)
            constructLayouts();
        else
            this->mainLayout->addWidget(new QLabel("Aucune gamme personalisée"), 0, 0, 1, 3);

    this->returnButton = new QPushButton("Retour");
    connect(returnButton, SIGNAL(pressed()), this, SLOT(close()));

    this->mainLayout->addWidget(returnButton, 1, 0, 1, 3);

    this->setLayout(mainLayout);
}

void DeleteChordsScalesView::clearLayout(QLayout *layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void DeleteChordsScalesView::constructLayouts()
{
    constructNameLayout();
    constructViewLayout();
    constructDeleteLayout();
}

void DeleteChordsScalesView::constructNameLayout()
{
    this->namesLayout = new QVBoxLayout();
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
    this->mainLayout->addLayout(namesLayout, 0, 0, 1, 1);
}

void DeleteChordsScalesView::constructViewLayout()
{
    this->viewLayout = new QVBoxLayout();
    this->HSView.clear();
    for(int i=0; i<HSNames.size(); i++)
    {
        this->HSView.push_back(new QPushButton("Afficher"));
        this->viewLayout->addWidget(HSView.last());
        connect(HSView.last(), SIGNAL(pressed()), this, SLOT(openViewSlot()));
        connect(HSView.last(), SIGNAL(released()), this, SLOT(closeViewSlot()));
    }
    this->mainLayout->addLayout(viewLayout, 0, 1, 1, 1);
}

void DeleteChordsScalesView::constructDeleteLayout()
{
    this->deleteLayout = new QVBoxLayout();
    this->HSDelete.clear();
    for(int i=0; i<HSNames.size(); i++)
    {
        this->HSDelete.push_back(new QPushButton("Supprimer"));
        this->deleteLayout->addWidget(HSDelete.last());
        connect(HSDelete.last(), SIGNAL(clicked(bool)), this, SLOT(deleteSlot()));
    }
    this->mainLayout->addLayout(deleteLayout, 0, 2, 1, 1);
}

void DeleteChordsScalesView::openViewSlot()
{
    QPushButton* temp = (QPushButton *)sender();
    int i = HSView.indexOf(temp);
    cout<<"i = "<<i<<endl<<flush;
    if(isChord)
    {
        chordView = new ChordsView("C:"+HSNames[i]->text(), isChord);
    }
    else
        chordView = new ChordsView("C:"+ScaleName[i], isChord);
    chordView->show();
}

void DeleteChordsScalesView::closeViewSlot()
{
    chordView->close();
}

void DeleteChordsScalesView::deleteSlot()
{
    QPushButton* temp = (QPushButton *)sender();
    int i = HSDelete.indexOf(temp);

    if(isChord)
        this->mainLayout->addWidget(new QLabel("Aucun accord personalisé"), 0, 0, 1, 3);
    else
        this->mainLayout->addWidget(new QLabel("Aucune gamme personalisée"), 0, 0, 1, 3);


    if(isChord)
        emit deleteChordSignal(ChordDictionary::getInstance()->getHSbyName(HSNames[i]->text()));
    else
        emit deleteScaleSignal(ScaleDictionary::getInstance()->getHSbyName(ScaleName[i]));

    clearLayout(viewLayout);
    clearLayout(namesLayout);
    clearLayout(deleteLayout);
    constructLayouts();
}

