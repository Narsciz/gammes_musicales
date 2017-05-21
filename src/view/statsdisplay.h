#ifndef STATSDISPLAY_H
#define STATSDISPLAY_H

//Bibliotheques c++
#include <iostream>

//Bibliotheques Qt
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSizePolicy>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTabWidget>
#include <QVector>
#include <QWidget>

using namespace std;

//Fenetre affichant les statistiques concernant les performances des différents algorithmes lors de leur lancement
class StatsDisplay : public QWidget
{
    Q_OBJECT

private:
    QWidget *centralWidget;

    QTabWidget *tab;
    QWidget *scale;
    QGridLayout *scaleLayout;
    QWidget *note;
    QGridLayout *noteLayout;
    QWidget *totalScale;
    QGridLayout *totalScaleLayout;

    QTableWidget *scaleView;
    QTableWidget *noteView;
    QTableWidget *totalScaleView;

public:
    StatsDisplay();
    void createScaleTab();
    void createNoteTab();
    void createTotalScaleTab();
    QVector<QStringList> loadFile(QString path);
};

#endif // STATSDISPLAY_H
