#include "view/statsdisplay.h"

StatsDisplay::StatsDisplay()
{
    this->setWindowTitle("Statistiques");
    this->setFixedWidth(790);
    this->tab = new QTabWidget(this);
    this->tab->setFixedWidth(790);
    this->tab->setFixedHeight(800);

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
    scaleView = new QTableWidget(2, 7);
    scaleView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scaleLayout->addWidget(scaleView);
    scaleView->setSpan(0, 0, 2, 1);
    scaleView->setSpan(0, 1, 1, 2);
    scaleView->setSpan(0, 3, 1, 2);
    scaleView->setSpan(0, 5, 1, 2);
    scaleView->setCellWidget(0, 0, new QLabel(" Nombre d'Accords Testés "));
    scaleView->setCellWidget(0, 1, new QLabel(" Algorithme Brut "));
    scaleView->setCellWidget(0, 3, new QLabel(" Algorithme Brut Optimisé "));
    scaleView->setCellWidget(0, 5, new QLabel(" Algorithme Optimisé "));

    scaleView->setCellWidget(1, 1, new QLabel(" Nombre de fois "));
    scaleView->setCellWidget(1, 2, new QLabel(" Temps Moyen "));
    scaleView->setCellWidget(1, 3, new QLabel(" Nombre de fois "));
    scaleView->setCellWidget(1, 4, new QLabel(" Temps Moyen "));
    scaleView->setCellWidget(1, 5, new QLabel(" Nombre de fois "));
    scaleView->setCellWidget(1, 6, new QLabel(" Temps Moyen "));;

    QVector<QStringList> loadedFile = loadFile("../stats/scaleStats.txt");

    QVector<double> timeTabBrut;
    QVector<int> nbTabBrut;
    QVector<double> timeTabOmega;
    QVector<int> nbTabOmega;
    QVector<double> timeTabOpti;
    QVector<int> nbTabOpti;

    if(loadedFile.size() > 1)
    {
        for(int i = 1; i<loadedFile.size(); i++)
    {
        if(loadedFile[i][0] == "1")
        {
            if(loadedFile[i][1].toInt()>timeTabBrut.size())
            {
                while(timeTabBrut.size()<loadedFile[i][1].toInt())
                {
                    timeTabBrut.push_back(0);
                    nbTabBrut.push_back(0);
                    timeTabOmega.push_back(0);
                    nbTabOmega.push_back(0);
                    timeTabOpti.push_back(0);
                    nbTabOpti.push_back(0);
                }
            }
            timeTabBrut.replace(loadedFile[i][1].toInt()-1, timeTabBrut[loadedFile[i][1].toInt()-1] + loadedFile[i][2].toDouble());
            nbTabBrut.replace(loadedFile[i][1].toInt()-1, nbTabOmega[loadedFile[i][1].toInt()-1] + 1);
        }
        else
        {
            if(loadedFile[i][0] == "2")
            {
                if(loadedFile[i][1].toInt()>timeTabOmega.size())
                {
                    while(timeTabOmega.size()<loadedFile[i][1].toInt())
                    {
                        timeTabBrut.push_back(0);
                        nbTabBrut.push_back(0);
                        timeTabOmega.push_back(0);
                        nbTabOmega.push_back(0);
                        timeTabOpti.push_back(0);
                        nbTabOpti.push_back(0);
                    }
                }
                timeTabOmega.replace(loadedFile[i][1].toInt()-1, timeTabOmega[loadedFile[i][1].toInt()-1] + loadedFile[i][2].toDouble());
                nbTabOmega.replace(loadedFile[i][1].toInt()-1, nbTabOmega[loadedFile[i][1].toInt()-1] + 1);
            }
            else
            {
                if(loadedFile[i][1].toInt()>timeTabOpti.size())
                {
                    while(timeTabOpti.size()<loadedFile[i][1].toInt())
                    {
                        timeTabBrut.push_back(0);
                        nbTabBrut.push_back(0);
                        timeTabOmega.push_back(0);
                        nbTabOmega.push_back(0);
                        timeTabOpti.push_back(0);
                        nbTabOpti.push_back(0);
                    }
                }
                    timeTabOpti.replace(loadedFile[i][1].toInt()-1, timeTabOpti[loadedFile[i][1].toInt()-1] + loadedFile[i][2].toDouble());
                    nbTabOpti.replace(loadedFile[i][1].toInt()-1, nbTabOpti[loadedFile[i][1].toInt()-1] + 1);
                }
        }
    }
    }

    for(int i=0; i< timeTabBrut.size(); i++)
    {
        if(nbTabBrut[i] != 0 || nbTabOmega[i] != 0 || nbTabOpti[i] != 0)
        {
            int lastRow = scaleView->rowCount();
            scaleView->insertRow(lastRow);
            scaleView->setCellWidget(lastRow, 0, new QLabel(QString::number(i+1)));
            if(nbTabBrut[i] > 0)
            {
                scaleView->setCellWidget(lastRow, 1, new QLabel(QString::number(nbTabBrut[i])));
                scaleView->setCellWidget(lastRow, 2, new QLabel(QString::number(timeTabBrut[i]/nbTabBrut[i])));
            }
            else
            {
                scaleView->setCellWidget(lastRow, 1, new QLabel("-"));
                scaleView->setCellWidget(lastRow, 2, new QLabel("-"));
            }
            if(nbTabOmega[i] > 0)
            {
                scaleView->setCellWidget(lastRow, 3, new QLabel(QString::number(nbTabOmega[i])));
                scaleView->setCellWidget(lastRow, 4, new QLabel(QString::number(timeTabOmega[i]/nbTabOmega[i])));
            }
            else
            {
                scaleView->setCellWidget(lastRow, 3, new QLabel("-"));
                scaleView->setCellWidget(lastRow, 4, new QLabel("-"));
            }
            if(nbTabOpti[i] > 0)
            {
                scaleView->setCellWidget(lastRow, 5, new QLabel(QString::number(nbTabOpti[i])));
                scaleView->setCellWidget(lastRow, 6, new QLabel(QString::number(timeTabOpti[i]/nbTabOpti[i])));
            }
            else
            {
                scaleView->setCellWidget(lastRow, 5, new QLabel("-"));
                scaleView->setCellWidget(lastRow, 6, new QLabel("-"));
            }
        }
    }

    scaleView->resizeColumnsToContents();
}

void StatsDisplay::createNoteTab()
{
    noteView = new QTableWidget(2, 7);
    noteView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    noteLayout->addWidget(noteView);
    noteView->setSpan(0, 0, 2, 1);
    noteView->setSpan(0, 1, 1, 2);
    noteView->setSpan(0, 3, 1, 2);
    noteView->setSpan(0, 5, 1, 2);
    noteView->setCellWidget(0, 0, new QLabel(" Nombre d'Accords Testés "));
    noteView->setCellWidget(0, 1, new QLabel(" Algorithme Brut "));
    noteView->setCellWidget(0, 3, new QLabel(" Algorithme Brut Optimisé "));
    noteView->setCellWidget(0, 5, new QLabel(" Algorithme Optimisé "));

    noteView->setCellWidget(1, 1, new QLabel(" Nombre de fois "));
    noteView->setCellWidget(1, 2, new QLabel(" Temps Moyen "));
    noteView->setCellWidget(1, 3, new QLabel(" Nombre de fois "));
    noteView->setCellWidget(1, 4, new QLabel(" Temps Moyen "));
    noteView->setCellWidget(1, 5, new QLabel(" Nombre de fois "));
    noteView->setCellWidget(1, 6, new QLabel(" Temps Moyen "));;

    QVector<QStringList> loadedFile = loadFile("../stats/noteStats.txt");


    QVector<double> timeTabBrut;
    QVector<int> nbTabBrut;
    QVector<double> timeTabOmega;
    QVector<int> nbTabOmega;
    QVector<double> timeTabOpti;
    QVector<int> nbTabOpti;

    if(loadedFile.size() > 1)
    {
        for(int i = 1; i<loadedFile.size(); i++)
    {
        if(loadedFile[i][0] == "1")
        {
            if(loadedFile[i][1].toInt()>timeTabBrut.size())
            {
                while(timeTabBrut.size()<loadedFile[i][1].toInt())
                {
                    timeTabBrut.push_back(0);
                    nbTabBrut.push_back(0);
                    timeTabOmega.push_back(0);
                    nbTabOmega.push_back(0);
                    timeTabOpti.push_back(0);
                    nbTabOpti.push_back(0);
                }
            }
            timeTabBrut.replace(loadedFile[i][1].toInt()-1, timeTabBrut[loadedFile[i][1].toInt()-1] + loadedFile[i][2].toDouble());
            nbTabBrut.replace(loadedFile[i][1].toInt()-1, nbTabOmega[loadedFile[i][1].toInt()-1] + 1);
        }
        else
        {
            if(loadedFile[i][0] == "2")
            {
                if(loadedFile[i][1].toInt()>timeTabOmega.size())
                {
                    while(timeTabOmega.size()<loadedFile[i][1].toInt())
                    {
                        timeTabBrut.push_back(0);
                        nbTabBrut.push_back(0);
                        timeTabOmega.push_back(0);
                        nbTabOmega.push_back(0);
                        timeTabOpti.push_back(0);
                        nbTabOpti.push_back(0);
                    }
                }
                timeTabOmega.replace(loadedFile[i][1].toInt()-1, timeTabOmega[loadedFile[i][1].toInt()-1] + loadedFile[i][2].toDouble());
                nbTabOmega.replace(loadedFile[i][1].toInt()-1, nbTabOmega[loadedFile[i][1].toInt()-1] + 1);
            }
            else
            {
                if(loadedFile[i][1].toInt()>timeTabOpti.size())
                {
                    while(timeTabOpti.size()<loadedFile[i][1].toInt())
                    {
                        timeTabBrut.push_back(0);
                        nbTabBrut.push_back(0);
                        timeTabOmega.push_back(0);
                        nbTabOmega.push_back(0);
                        timeTabOpti.push_back(0);
                        nbTabOpti.push_back(0);
                    }
                }
                    timeTabOpti.replace(loadedFile[i][1].toInt()-1, timeTabOpti[loadedFile[i][1].toInt()-1] + loadedFile[i][2].toDouble());
                    nbTabOpti.replace(loadedFile[i][1].toInt()-1, nbTabOpti[loadedFile[i][1].toInt()-1] + 1);
                }
        }
    }
    }

    for(int i=0; i< timeTabBrut.size(); i++)
    {
        if(nbTabBrut[i] != 0 || nbTabOmega[i] != 0 || nbTabOpti[i] != 0)
        {
            int lastRow = noteView->rowCount();
            noteView->insertRow(lastRow);
            noteView->setCellWidget(lastRow, 0, new QLabel(QString::number(i+1)));
            if(nbTabBrut[i] > 0)
            {
                noteView->setCellWidget(lastRow, 1, new QLabel(QString::number(nbTabBrut[i])));
                noteView->setCellWidget(lastRow, 2, new QLabel(QString::number(timeTabBrut[i]/nbTabBrut[i])));
            }
            else
            {
                noteView->setCellWidget(lastRow, 1, new QLabel("-"));
                noteView->setCellWidget(lastRow, 2, new QLabel("-"));
            }
            if(nbTabOmega[i] > 0)
            {
                noteView->setCellWidget(lastRow, 3, new QLabel(QString::number(nbTabOmega[i])));
                noteView->setCellWidget(lastRow, 4, new QLabel(QString::number(timeTabOmega[i]/nbTabOmega[i])));
            }
            else
            {
                noteView->setCellWidget(lastRow, 3, new QLabel("-"));
                noteView->setCellWidget(lastRow, 4, new QLabel("-"));
            }
            if(nbTabOpti[i] > 0)
            {
                noteView->setCellWidget(lastRow, 5, new QLabel(QString::number(nbTabOpti[i])));
                noteView->setCellWidget(lastRow, 6, new QLabel(QString::number(timeTabOpti[i]/nbTabOpti[i])));
            }
            else
            {
                noteView->setCellWidget(lastRow, 5, new QLabel("-"));
                noteView->setCellWidget(lastRow, 6, new QLabel("-"));
            }
        }
    }


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

    totalScaleView->setCellWidget(0, 0, new QLabel(" Nombre d'Accords Testés "));
    totalScaleView->setCellWidget(0, 1, new QLabel(" Algorithme Brut "));
    totalScaleView->setCellWidget(0, 3, new QLabel(" Algorithme Brut Optimisé "));

    totalScaleView->setCellWidget(1, 1, new QLabel(" Nombre de fois "));
    totalScaleView->setCellWidget(1, 2, new QLabel(" Temps Moyen "));
    totalScaleView->setCellWidget(1, 3, new QLabel(" Nombre de fois "));
    totalScaleView->setCellWidget(1, 4, new QLabel(" Temps Moyen "));

    QVector<QStringList> loadedFile = loadFile("../stats/totalScaleStats.txt");


    QVector<double> timeTabBrut;
    QVector<int> nbTabBrut;
    QVector<double> timeTabOmega;
    QVector<int> nbTabOmega;

    if(loadedFile.size() > 1)
    {
        for(int i = 1; i<loadedFile.size(); i++)
    {
        if(loadedFile[i][0] == "1")
        {
            if(loadedFile[i][1].toInt()>timeTabBrut.size())
            {
                while(timeTabBrut.size()<loadedFile[i][1].toInt())
                {
                    timeTabBrut.push_back(0);
                    nbTabBrut.push_back(0);
                    timeTabOmega.push_back(0);
                    nbTabOmega.push_back(0);
                }
            }
            timeTabBrut.replace(loadedFile[i][1].toInt()-1, timeTabBrut[loadedFile[i][1].toInt()-1] + loadedFile[i][2].toDouble());
            nbTabBrut.replace(loadedFile[i][1].toInt()-1, nbTabOmega[loadedFile[i][1].toInt()-1] + 1);
        }
        else
        {
            if(loadedFile[i][0] == "2")
            {
                if(loadedFile[i][1].toInt()>timeTabOmega.size())
                {
                    while(timeTabOmega.size()<loadedFile[i][1].toInt())
                    {
                        timeTabBrut.push_back(0);
                        nbTabBrut.push_back(0);
                        timeTabOmega.push_back(0);
                        nbTabOmega.push_back(0);
                    }
                }
                timeTabOmega.replace(loadedFile[i][1].toInt()-1, timeTabOmega[loadedFile[i][1].toInt()-1] + loadedFile[i][2].toDouble());
                nbTabOmega.replace(loadedFile[i][1].toInt()-1, nbTabOmega[loadedFile[i][1].toInt()-1] + 1);
            }
        }
    }
    }

    for(int i=0; i< timeTabBrut.size(); i++)
    {
        if(nbTabBrut[i] != 0 || nbTabOmega[i] != 0)
        {
            int lastRow = totalScaleView->rowCount();
            totalScaleView->insertRow(lastRow);
            totalScaleView->setCellWidget(lastRow, 0, new QLabel(QString::number(i+1)));
            if(nbTabBrut[i] > 0)
            {
                totalScaleView->setCellWidget(lastRow, 1, new QLabel(QString::number(nbTabBrut[i])));
                totalScaleView->setCellWidget(lastRow, 2, new QLabel(QString::number(timeTabBrut[i]/nbTabBrut[i])));
            }
            else
            {
                totalScaleView->setCellWidget(lastRow, 1, new QLabel("-"));
                totalScaleView->setCellWidget(lastRow, 2, new QLabel("-"));
            }
            if(nbTabOmega[i] > 0)
            {
                totalScaleView->setCellWidget(lastRow, 3, new QLabel(QString::number(nbTabOmega[i])));
                totalScaleView->setCellWidget(lastRow, 4, new QLabel(QString::number(timeTabOmega[i]/nbTabOmega[i])));
            }
            else
            {
                totalScaleView->setCellWidget(lastRow, 3, new QLabel("-"));
                totalScaleView->setCellWidget(lastRow, 4, new QLabel("-"));
            }
        }
    }

    totalScaleView->resizeColumnsToContents();
}

QVector<QStringList> StatsDisplay::loadFile(QString path)
{
    QString fileContent;

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
