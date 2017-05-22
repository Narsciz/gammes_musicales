#ifndef SCALESDISPLAYLAYOUT_H
#define SCALESDISPLAYLAYOUT_H

//Bibliotheques c++
#include <iostream>

//Bibliotheques Qt
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QString>
#include <QVector>
#include <QWidget>

//Classes
#include "view/scalesdisplay.h"

using namespace std;

//Box affichant les gammes générées, "hidden" avant lancement de l'algorithme, "visible" après lancement
class ScalesListDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QGridLayout *scalesFoundLayout;
    QVector<ScalesDisplay*> listScales;
    QVector<QPushButton*> listSaveButtons;
    QVector<QPushButton*> listExportButtons;

    QVBoxLayout *baseLayout;
    QScrollArea *scrollArea;
    QWidget *scrolledWidget;

public:
    //Constructeur
    ScalesListDisplay();
    void constructScalesFoundList(QVector<QVector<QString> > listFoundScales);

    //Accesseur
    void setName(QString name);

    //Méthode
    void refresh();

public slots:
    void saveScaleSlot();
    void exportScaleSlot();

signals:
    void saveScaleSignal(QVector<QString>);
    void exportScaleSignal(QVector<QString>);
};

#endif // SCALESDISPLAYLAYOUT_H
