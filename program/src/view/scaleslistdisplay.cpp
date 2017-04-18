#include "scaleslistdisplay.h"

ScalesListDisplay::ScalesListDisplay() : QGroupBox()
{
    this->setTitle("Gammes trouvées : ");
    this->scalesFoundLayout = new QGridLayout();
    this->setContentsMargins(0, 5, 0, 0);
    this->scalesFoundLayout->setContentsMargins(0, 10, 0, 0);
    this->scalesFoundLayout->setVerticalSpacing(0);

    //this->setLayout(this->scalesFoundLayout);

    this->scrollArea = new QScrollArea();
    this->baseLayout = new QVBoxLayout();
    this->scrolledWidget = new QWidget();
    this->scrolledWidget->setLayout(scalesFoundLayout);

    this->setLayout(baseLayout);
    this->baseLayout->addWidget(scrollArea);
    this->scrollArea->setWidget(scrolledWidget);
    this->scrollArea->setWidgetResizable(true);
}

void ScalesListDisplay::constructScalesFoundList(QVector<QVector<QString> > listFoundScales)
{
    for(int i=0; i< listFoundScales.size(); i++)
    {
        this->listScales.push_back(new ScalesDisplay(listFoundScales[i]));
        this->listSaveButtons.push_back(new QPushButton("Enregistrer"));
        connect(listSaveButtons[i], SIGNAL(clicked()), this, SLOT(saveScaleSlot()));
        this->listExportButtons.push_back(new QPushButton("Exporter"));
        connect(listExportButtons[i], SIGNAL(clicked()), this, SLOT(exportScaleSlot()));
        this->scalesFoundLayout->addWidget(this->listScales.last(), i*2, 0, 2, 6);
        this->scalesFoundLayout->addWidget(this->listSaveButtons.last(), i*2, 6, 1, 1);
        this->scalesFoundLayout->addWidget(this->listExportButtons.last(), (i*2+1), 6, 1, 1);
    }
}

void ScalesListDisplay::saveScaleSlot()
{
    QPushButton* temp = (QPushButton *)sender();
    int i = listSaveButtons.indexOf(temp);
    emit saveScaleSignal(listScales[i]->getListScale());
}
void ScalesListDisplay::exportScaleSlot()
{
    QPushButton* temp = (QPushButton *)sender();
    int i = listExportButtons.indexOf(temp);
    emit exportScaleSignal(listScales[i]->getListScale());
}
