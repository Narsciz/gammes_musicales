#include "scalesdisplay.h"

ScalesDisplay::ScalesDisplay(QVector<QString> scaleList)
{
    for(int i=0; i<scaleList.size(); i++)
    {
        this->scaleList.push_back(new ScaleDisplay(scaleList[i]));
    }
}
