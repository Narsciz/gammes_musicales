#ifndef PARAMETERSDISPLAY_H
#define PARAMETERSDISPLAY_H

//Bibliotheques c++
#include <iostream>

//Bibliotheques Qt
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

//fenêtre permettant à l'utilisateur de choisir les parametres de calculs qui seront utilisés
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
    QVector<QString> listScalesName;
    QVector<QCheckBox*> listScales;
    QCheckBox *allChecked;

    QGroupBox *allowedCustomScalesBox;
    QVBoxLayout *allowedCustomScalesLayout;
    QVector<QString> listCustomScalesName;
    QVector<QCheckBox*> listCustomScales;
    QCheckBox *allCustomChecked;

    QLabel *maxSolutionLabel;
    QSpinBox *maxSolutionDisplayed;

    QPushButton *validateButton;

public:
    //Constructeur
    ParametersDisplay();
    void fillLists(QVector<QString> listHSScales, QVector<QString> listAlias, QVector<QString> listHSCustomScales, QVector<QString> listCustomAlias);

    //Accesseurs
    int getParameter();
    int getAlgo();
    int getLimit();
    QVector<QString> getlistAllowedHSscales();

    //Méthode
    void clearLayout(QLayout *layout, bool deleteWidgets = true);

public slots:
   void totalScaleSlot();
   void validateSlot();
   void AllCheckedSlot();
   void CustomAllCheckedSlot();
};

#endif // PARAMETERSDISPLAY_H
