#include "scalesdisplay.h"

ScalesDisplay::ScalesDisplay(QString name, QVector<QString> scaleList) : QGroupBox()
{
    this->setTitle(name);
    this->scalesLayout = new QGridLayout();
    this->scalesLayout->setAlignment(Qt::AlignTop);
    this->scalesLayout->setHorizontalSpacing(4);
    for(int i=0; i<scaleList.size(); i++)
    {
        this->scalesList.push_back(new ScaleDisplay(scaleList[i]));
    }
    this->setLayout(scalesLayout);

    //this->setMinimumSize(400, 100);
    this->setContentsMargins(5, 5, 5, 5);

}

void ScalesDisplay::refresh(int width)
{
    int i=0;
    int j=0;
    int k=0;
    int nb = 0;
    while(i<this->scalesList.size())
    {
        if((i*64)+80>width && !nb)
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
        this->scalesLayout->addWidget(this->scalesList[i], j, k, 1, 1);
        k++;
        i++;
    }
}

QVector<QString> ScalesDisplay::getListScale()
{
    QVector<QString> res;
    for(int i=0; i<scalesList.size(); i++)
    {
        res.push_back(scalesList[i]->getName());
    }
    return res;
}
