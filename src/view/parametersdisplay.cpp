#include "parametersdisplay.h"
#include "modele/scaledictionary.h"

using namespace std;

ParametersDisplay::ParametersDisplay() : QWidget()
{
    this->mainLayout = new QGridLayout();

    this->parametersBox = new QGroupBox("Paramètre de recherche");
    this->parametersLayout = new QHBoxLayout();
    this->lessScale = new QRadioButton("Le moins de changement de gammes");
    this->lessNote = new QRadioButton("Le moins de changement de notes entre gammes consécutives");
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

    this->maxSolutionLabel = new QLabel("Nombre de Solutions Affichées : ");
    this->maxSolutionLabel->setHidden(true);
    this->maxSolutionDisplayed = new QSpinBox();
    this->maxSolutionDisplayed->setRange(1, 200);
    this->maxSolutionDisplayed->setValue(200);
    this->maxSolutionDisplayed->setHidden(true);

    this->allowedScalesBox = new QGroupBox("Gammes de bases autorisées");
    this->allowedScalesLayout = new QVBoxLayout();
    this->allowedScalesLayout->setAlignment(Qt::AlignTop);
    this->allowedScalesBox->setLayout(this->allowedScalesLayout);
    this->allChecked = new QCheckBox("Tout cocher");
    connect(this->allChecked, SIGNAL(toggled(bool)), this, SLOT(AllCheckedSlot()));

    this->allowedCustomScalesBox = new QGroupBox("Gammes personnalisées autorisées");
    this->allowedCustomScalesLayout = new QVBoxLayout();
    this->allowedCustomScalesLayout->setAlignment(Qt::AlignTop);
    this->allowedCustomScalesBox->setLayout(this->allowedCustomScalesLayout);
    this->allCustomChecked = new QCheckBox("Tout cocher");
    connect(this->allCustomChecked, SIGNAL(toggled(bool)), this, SLOT(CustomAllCheckedSlot()));

    this->validateButton = new QPushButton("Valider");
    connect(validateButton, SIGNAL(clicked(bool)), this, SLOT(validateSlot()));

    this->mainLayout->addWidget(parametersBox, 0, 0, 1, 2);
    this->mainLayout->addWidget(algoBox, 1, 0, 1, 2);
    this->mainLayout->addWidget(maxSolutionLabel, 2, 0, 1, 1);
    this->mainLayout->addWidget(maxSolutionDisplayed, 2, 1, 1, 1);
    this->mainLayout->addWidget(allowedScalesBox, 3, 0, 1, 1);
    this->mainLayout->addWidget(allowedCustomScalesBox, 3, 1, 1, 1);
    this->mainLayout->addWidget(allChecked, 4, 0, 1, 1);
    this->mainLayout->addWidget(allCustomChecked, 4, 1, 1, 1);
    this->mainLayout->addWidget(validateButton, 5, 0, 1, 2);

    this->setLayout(this->mainLayout);
    this->setWindowTitle("Paramètres");

    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

void ParametersDisplay::fillLists(QVector<QString> listHSScales, QVector<QString> listHSCustomScales)
{
    clearLayout(this->allowedScalesLayout);
    this->listScales.clear();
    this->listScalesName.clear();

    for(int i = 0; i < listHSScales.size(); i++)
    {
        this->listScales.push_back(new QCheckBox(listHSScales[i]));
        if(this->listScales.last()->text() == "M" || this->listScales.last()->text() == "mh")
            this->listScales.last()->setChecked(true);
        this->allowedScalesLayout->addWidget(this->listScales.last());
    }
    clearLayout(this->allowedCustomScalesLayout);
    this->listCustomScales.clear();
    this->listCustomScalesName.clear();
    for(int i = 0; i < listHSCustomScales.size(); i++)
    {
        this->listCustomScales.push_back(new QCheckBox(listHSCustomScales[i]));
        this->allowedCustomScalesLayout->addWidget(this->listCustomScales.last());
    }
    //this->allowedCustomScalesLayout->update();
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
int ParametersDisplay::getLimit()
{
    return this->maxSolutionDisplayed->value();
}

QVector<QString> ParametersDisplay::getlistAllowedHSscales()
{
    QVector<QString> res;
    for(int i = 0; i<this->listScales.size(); i++)
    {
        if(listScales[i]->isChecked())
        {
            res.push_back(listScales[i]->text());
        }
    }
    for(int i = 0; i<this->listCustomScales.size(); i++)
    {
        if(listCustomScales[i]->isChecked())
        {
            res.push_back(listCustomScales[i]->text());
        }
    }

    return res;
}

void ParametersDisplay::clearLayout(QLayout *layout, bool deleteWidgets)
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

void ParametersDisplay::totalScaleSlot()
{
    if(algoOptiv1->isChecked())
    {
        if(lessTotalScale->isChecked())
            lessScale->setChecked(true);
        lessTotalScale->setDisabled(true);
        this->maxSolutionLabel->setHidden(false);
        this->maxSolutionDisplayed->setHidden(false);
    }
    else
    {
        lessTotalScale->setDisabled(false);
        this->maxSolutionLabel->setHidden(true);
        this->maxSolutionDisplayed->setHidden(true);
    }
}

void ParametersDisplay::validateSlot()
{
    this->close();
}
void ParametersDisplay::AllCheckedSlot()
{
    for(int i=0; i<this->listScales.size(); i++)
    {
        if(this->allChecked->isChecked())
            this->listScales[i]->setChecked(true);
        else
            this->listScales[i]->setChecked(false);
    }
}

void ParametersDisplay::CustomAllCheckedSlot()
{
    for(int i=0; i<this->listCustomScales.size(); i++)
    {
        if(this->allCustomChecked->isChecked())
            this->listCustomScales[i]->setChecked(true);
        else
            this->listCustomScales[i]->setChecked(false);
    }
}
