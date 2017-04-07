#include "parametersdisplay.h"

ParametersDisplay::ParametersDisplay() : QWidget()
{
    this->mainLayout = new QGridLayout();

    this->parametersBox = new QGroupBox("Paramètre de recherche");
    this->parametersLayout = new QHBoxLayout();
    this->lessScale = new QRadioButton("Le moins de changement de notes entre deux gammes consécutives");
    this->lessNote = new QRadioButton("Le moins de changement de notes entre deux gammes consécutives");
    this->lessScale->setChecked(true);
    this->parametersLayout->addWidget(this->lessScale);
    this->parametersLayout->addWidget(this->lessNote);
    this->parametersBox->setLayout(this->parametersLayout);

    this->algoBox = new QGroupBox("Algorithmes utilisés");
    this->algoLayout = new QHBoxLayout();
    this->algoBrut = new QRadioButton("Algorithmes bruts");
    this->algoOptiv1 = new QRadioButton("Algorithmes optimisés V1");
    this->algoBrut->setChecked(true);
    this->algoLayout->addWidget(this->algoBrut);
    this->algoLayout->addWidget(this->algoOptiv1);
    this->algoBox->setLayout(this->algoLayout);

    this->allowedChordsBox = new QGroupBox("Accords autorisés");
    this->allowedChordsLayout = new QVBoxLayout();
    this->allowedChordsBox->setLayout(this->allowedChordsLayout);

    this->allowedScalesBox = new QGroupBox("Gammes autorisées");
    this->allowedScalesLayout = new QVBoxLayout();
    this->allowedScalesBox->setLayout(this->allowedScalesLayout);

    this->mainLayout->addWidget(parametersBox, 0, 0, 1, 2);
    this->mainLayout->addWidget(algoBox, 1, 0, 1, 2);
    this->mainLayout->addWidget(allowedChordsBox, 2, 0, 1, 1);
    this->mainLayout->addWidget(allowedScalesBox, 2, 1, 1, 1);

    this->setLayout(this->mainLayout);
    this->setWindowTitle("Paramètres");

    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

void ParametersDisplay::fillLists(QVector<QString> listHSChords, QVector<QString> listHSScales)
{
    for(int i = 0; i<listHSChords.size(); i++)
    {
        this->listChords.push_back(new QCheckBox(listHSChords[i]));
        this->listChords.last()->setChecked(true);
        this->allowedChordsLayout->addWidget(this->listChords.last());
    }
    for(int i = 0; i<listHSScales.size(); i++)
    {
        this->listScales.push_back(new QCheckBox(listHSScales[i]));
        this->listScales.last()->setChecked(true);
        this->allowedScalesLayout->addWidget(this->listScales.last());
    }
}

int ParametersDisplay::getParameter()
{
    int res;
    if(lessScale->isChecked())
        res = 1;
    if(lessNote->isChecked())
        res = 2;
    return res;
}

int ParametersDisplay::getAlgo()
{
    int res;
    if(algoBrut->isChecked())
        res = 1;
    if(algoOptiv1->isChecked())
        res = 2;
    return res;
}

QVector<QString> ParametersDisplay::getlistAllowedScales()
{
    QVector<QString> res;
    for(int i = 0; i<this->listScales.size(); i++)
    {
        if(listScales[i]->isChecked())
            res.push_back(listScales[i]->text());
    }
    return res;
}
