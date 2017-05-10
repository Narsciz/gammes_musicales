#include "parametersdisplay.h"
#include "modele/scaledictionary.h"

using namespace std;

ParametersDisplay::ParametersDisplay() : QWidget()
{
    this->mainLayout = new QGridLayout();

    this->parametersBox = new QGroupBox("Paramètre de recherche");
    this->parametersLayout = new QHBoxLayout();
    this->lessScale = new QRadioButton("Le moins de changement de gammes entre deux gammes consécutives");
    this->lessNote = new QRadioButton("Le moins de changement de notes entre deux gammes consécutives");
    this->lessTotalScale = new QRadioButton("Le moins de gammes au total");
    this->lessScale->setChecked(true);
    this->parametersLayout->addWidget(this->lessScale);
    this->parametersLayout->addWidget(this->lessNote);
    this->parametersLayout->addWidget(this->lessTotalScale);
    this->parametersBox->setLayout(this->parametersLayout);

    this->algoBox = new QGroupBox("Algorithmes utilisés");
    this->algoLayout = new QHBoxLayout();
    this->algoBrut = new QRadioButton("Algorithmes bruts");
    this->algoOmega = new QRadioButton("Algorithme bruts avancés");
    this->algoOptiv1 = new QRadioButton("Algorithmes optimisés V1");
    connect(algoBrut, SIGNAL(clicked(bool)), this, SLOT(totalScaleSlot()));
    connect(algoOmega, SIGNAL(clicked(bool)), this, SLOT(totalScaleSlot()));
    connect(algoOptiv1, SIGNAL(clicked(bool)), this, SLOT(totalScaleSlot()));
    this->algoBrut->setChecked(true);
    this->algoLayout->addWidget(this->algoBrut);
    this->algoLayout->addWidget(this->algoOmega);
    this->algoLayout->addWidget(this->algoOptiv1);
    this->algoBox->setLayout(this->algoLayout);

    this->allowedScalesBox = new QGroupBox("Gammes autorisées");
    this->allowedScalesLayout = new QVBoxLayout();
    this->allowedScalesLayout->setAlignment(Qt::AlignTop);
    this->allowedScalesBox->setLayout(this->allowedScalesLayout);

    this->validateButton = new QPushButton("Valider");
    connect(validateButton, SIGNAL(clicked(bool)), this, SLOT(validateSlot()));

    this->mainLayout->addWidget(parametersBox, 0, 0, 1, 3);
    this->mainLayout->addWidget(algoBox, 1, 0, 1, 3);
    this->mainLayout->addWidget(allowedScalesBox, 2, 0, 1, 3);
    this->mainLayout->addWidget(validateButton, 3, 1, 1, 1);

    this->setLayout(this->mainLayout);
    this->setWindowTitle("Paramètres");

    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

void ParametersDisplay::fillLists(QVector<QString> listHSChords, QVector<QString> listHSScales)
{
    for(int i = 0; i < listHSScales.size(); i++)
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
    if(lessTotalScale->isChecked())
        res = 3;
    return res;
}
int ParametersDisplay::getAlgo()
{
    int res;
    if(algoOmega->isChecked())
        res = 1;
    if(algoOptiv1->isChecked())
        res = 2;
    if(algoBrut->isChecked())
        res = 3;
    return res;
}
QVector<QString> ParametersDisplay::getlistAllowedHSscales()
{


    QVector<QString> res;
    for(int i = 0; i<this->listScales.size(); i++)
    {
        if(listScales[i]->isChecked()){
            res.push_back(listScales[i]->text());
//            cout << listScales[i]->text().toStdString() << endl;
        }
    }

    return res;
}

void ParametersDisplay::totalScaleSlot()
{
    if(algoOptiv1->isChecked())
    {
        if(lessTotalScale->isChecked())
            lessScale->setChecked(true);
        lessTotalScale->setDisabled(true);
    }
    else
        lessTotalScale->setDisabled(false);
}

void ParametersDisplay::validateSlot()
{
    this->close();
}
