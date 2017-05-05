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

    QGroupBox *algoBox;
    QHBoxLayout *algoLayout;
    QRadioButton *algoBrut;
    QRadioButton *algoOptiv1;

    QGroupBox *allowedChordsBox;
    QVBoxLayout *allowedChordsLayout;
    QVector<QCheckBox*> listChords;

    QGroupBox *allowedScalesBox;
    QVBoxLayout *allowedScalesLayout;
    QVector<QCheckBox*> listScales;

public:
    ParametersDisplay();
    void fillLists(QVector<QString> listHSChords, QVector<QString> listHSScales);
    int getParameter();
    int getAlgo();
    QVector<QString> getlistAllowedHSscales();
};

#endif // PARAMETERSDISPLAY_H
