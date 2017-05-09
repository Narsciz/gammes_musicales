#include "view/statsdisplay.h"

StatsDisplay::StatsDisplay()
{
    this->setFixedWidth(531);
    this->tab = new QTabWidget(this);
    this->tab->setFixedWidth(531);

    this->scale = new QWidget();
    this->scaleLayout = new QGridLayout();
    this->scale->setLayout(scaleLayout);
    this->scale->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    this->note = new QWidget();
    this->noteLayout = new QGridLayout();
    this->note->setLayout(noteLayout);
    this->note->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    this->totalScale = new QWidget();
    this->totalScaleLayout = new QGridLayout();
    this->totalScale->setLayout(totalScaleLayout);
    this->totalScale->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    tab->addTab(this->scale, "Gammes Consécutives");
    tab->addTab(this->note, "Changement de notes");
    tab->addTab(this->totalScale, "Gammes Totales");

    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    createScaleTab();
    createNoteTab();
    createTotalScaleTab();
}


void StatsDisplay::createScaleTab()
{
    scaleView = new QTableWidget(2, 5);
    scaleView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scaleLayout->addWidget(scaleView);
    scaleView->setSpan(0, 0, 2, 1);
    scaleView->setSpan(0, 1, 1, 2);
    scaleView->setSpan(0, 3, 1, 2);
    scaleView->setCellWidget(0, 0, new QLabel("Nombre d'Accords Testés"));
    scaleView->setCellWidget(0, 1, new QLabel("Algorithme Brut"));
    scaleView->setCellWidget(0, 3, new QLabel("Algorithme Optimisé"));
    scaleView->setCellWidget(1, 1, new QLabel("Nombre de fois"));
    scaleView->setCellWidget(1, 2, new QLabel("Temps Moyen"));
    scaleView->setCellWidget(1, 3, new QLabel("Nombre de fois"));
    scaleView->setCellWidget(1, 4, new QLabel("Temps Moyen"));

    QVector<QStringList> loadedFile = loadFile("scaleStats.txt");

    scaleView->resizeColumnsToContents();
}

void StatsDisplay::createNoteTab()
{
    noteView = new QTableWidget(2, 5);
    noteView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    noteLayout->addWidget(noteView);
    noteView->setSpan(0, 0, 2, 1);
    noteView->setSpan(0, 1, 1, 2);
    noteView->setSpan(0, 3, 1, 2);
    noteView->setCellWidget(0, 0, new QLabel("Nombre d'Accords Testés"));
    noteView->setCellWidget(0, 1, new QLabel("Algorithme Brut"));
    noteView->setCellWidget(0, 3, new QLabel("Algorithme Optimisé"));
    noteView->setCellWidget(1, 1, new QLabel("Nombre de fois"));
    noteView->setCellWidget(1, 2, new QLabel("Temps Moyen"));
    noteView->setCellWidget(1, 3, new QLabel("Nombre de fois"));
    noteView->setCellWidget(1, 4, new QLabel("Temps Moyen"));

    QVector<QStringList> loadedFile = loadFile("noteStats.txt");

    noteView->resizeColumnsToContents();
}

void StatsDisplay::createTotalScaleTab()
{
    totalScaleView = new QTableWidget(2, 5);
    totalScaleView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    totalScaleLayout->addWidget(totalScaleView);
    totalScaleView->setSpan(0, 0, 2, 1);
    totalScaleView->setSpan(0, 1, 1, 2);
    totalScaleView->setSpan(0, 3, 1, 2);
    totalScaleView->setCellWidget(0, 0, new QLabel("Nombre d'Accords Testés"));
    totalScaleView->setCellWidget(0, 1, new QLabel("Algorithme Brut"));
    totalScaleView->setCellWidget(0, 3, new QLabel("Algorithme Optimisé"));
    totalScaleView->setCellWidget(1, 1, new QLabel("Nombre de fois"));
    totalScaleView->setCellWidget(1, 2, new QLabel("Temps Moyen"));
    totalScaleView->setCellWidget(1, 3, new QLabel("Nombre de fois"));
    totalScaleView->setCellWidget(1, 4, new QLabel("Temps Moyen"));

    QVector<QStringList> loadedFile = loadFile("totalScaleStats.txt");

    /*
    QVector<float> timeTabBrut;
    QVector<int> nbTabBrut;
    QVector<float> timeTabOpti;
    QVector<int> nbTabOpti;

    for(int i = 0; i<loadedFile.size(); i++)
    {
        if(loadedFile[i][0] == "1")
        {
            if(loadedFile[i][0].toInt()>timeTabBrut.size())
            {
                while(timeTabBrut.size()<loadedFile[i][0].toInt())
                {
                    timeTabBrut.push_back(0);
                    nbTabBrut.push_back(0);
                }
            }
            else
            {
                timeTabBrut[loadedFile[i][0].toInt()-1] += loadedFile[i][0].toFloat();
                nbTabBrut[loadedFile[i][0].toInt()-1] +=1;
            }
        }
        else
        {
            if(loadedFile[i][0].toInt()>timeTabOpti.size())
            {
                while(timeTabOpti.size()<loadedFile[i][0].toInt())
                {
                    timeTabOpti.push_back(0);
                    nbTabOpti.push_back(0);
                }
            }
            else
            {
                timeTabOpti[loadedFile[i][0].toInt()-1] += loadedFile[i][0].toFloat();
                nbTabOpti[loadedFile[i][0].toInt()-1] +=1;
            }
        }
    }

    while(nbTabBrut.size() != nbTabOpti.size())
    {
        if(nbTabBrut.size()<nbTabOpti.size())
        {
            timeTabBrut.push_back(0);
            nbTabBrut.push_back(0);
        }
        else
        {
            timeTabOpti.push_back(0);
            nbTabOpti.push_back(0);
        }
    }*/

    totalScaleView->resizeColumnsToContents();
}

QVector<QStringList> StatsDisplay::loadFile(QString path)
{
    QString fileContent = "";

    QFile file(path);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileContent = file.readAll();
        file.close();
    }

    QStringList occurence = fileContent.split(';');
    QVector<QStringList> res;
    for(int i = 0; i<occurence.size(); i++)
    {
        res.push_back(occurence[i].split('|'));
    }
    return res;
}
