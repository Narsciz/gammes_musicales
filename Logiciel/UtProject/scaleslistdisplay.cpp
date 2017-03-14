#include "scaleslistdisplay.h"

ScalesListDisplay::ScalesListDisplay() : QGroupBox()
{
    this->setTitle("Gammes trouvées : ");
    this->scalesFoundLayout = new QGridLayout();
    this->setLayout(this->scalesFoundLayout);
    this->setContentsMargins(0, 5, 0, 0);
    this->scalesFoundLayout->setContentsMargins(0, 10, 0, 0);
    this->scalesFoundLayout->setVerticalSpacing(0);
}

void ScalesListDisplay::constructScalesFoundList(QVector<QVector<QString>> listFoundScales)
{
    for(int i=0; i< listFoundScales.size(); i++)
    {
        this->listScales.push_back(new ScalesDisplay(listFoundScales[i]));
        this->listSaveButtons.push_back(new QPushButton("Enregistrer"));
        this->scalesFoundLayout->addWidget(this->listScales.last(), i, 0, 1, 6);
        this->scalesFoundLayout->addWidget(this->listSaveButtons.last(), i, 6, 1, 1);
    }
}
