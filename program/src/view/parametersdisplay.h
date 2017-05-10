#ifndef PARAMETERSDISPLAY_H
#define PARAMETERSDISPLAY_H

#include <QGridLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QCheckBox>
#include <QVector>
#include <QString>
#include <QPushButton>
#include <iostream>
class ParametersDisplay : public QWidget
{
    Q_OBJECT
private :
    QGridLayout *mainLayout;

    QGroupBox *parametersBox;
    QHBoxLayout *parametersLayout;
    QRadioButton *lessScale;
    QRadioButton *lessNote;
    QRadioButton *lessTotalScale;

    QGroupBox *algoBox;
    QHBoxLayout *algoLayout;
    QRadioButton *algoBrut;
    QRadioButton *algoOmega;
    QRadioButton *algoOptiv1;

    QGroupBox *allowedScalesBox;
    QVBoxLayout *allowedScalesLayout;
    QVector<QCheckBox*> listScales;

    QPushButton *validateButton;

public:
    ParametersDisplay();
    void fillLists(QVector<QString> listHSChords, QVector<QString> listHSScales);
    int getParameter();
    int getAlgo();
    QVector<QString> getlistAllowedHSscales();

public slots:
   void totalScaleSlot();
   void validateSlot();
};

#endif // PARAMETERSDISPLAY_H
