#ifndef SCALESDISPLAYLAYOUT_H
#define SCALESDISPLAYLAYOUT_H

#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QString>
#include <QScrollArea>
#include <QWidget>
#include <iostream>
#include <QScrollBar>

using namespace std;

#include "scalesdisplay.h"

//Layout affichant les gammes générées, "hidden" avant lancement de l'algorithme, "visible" après lancement
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
    ScalesListDisplay();
    void constructScalesFoundList(QVector<QVector<QString> > listFoundScales);
    void setName(QString name);
    void refresh();

public slots:
    void saveScaleSlot();
    void exportScaleSlot();

signals:
    void saveScaleSignal(QVector<QString>);
    void exportScaleSignal(QVector<QString>);
};

#endif // SCALESDISPLAYLAYOUT_H
