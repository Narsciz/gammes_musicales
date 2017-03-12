#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QGridLayout>
#include <QLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QSpacerItem>
#include <QCoreApplication>

#include "chordslistdisplay.h"
#include "scaleslistdisplay.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    //Layout
    QGridLayout *mainLayout;//Layout principale servant de support aux différents layouts d'affichage
    QGridLayout *chordsLayout;
    QGridLayout *choicesLayout;//Layout affichant l'interface permettant à l'utilisateur de choisir accords et paramètres, "visible" avant lancement de l'algorithme, "hidden" après
    QGridLayout *scalesLayout;
    ChordsListDisplay *cListDisplay;//Layout affichant les accords choisit par l'utilisateur
    ScalesListDisplay *sListDisplay;//Layout affichant les gammes générées, "hidden" avant lancement de l'algorithme, "visible" après lancement

    //Button
    QPushButton *addButton;
    QPushButton *generateButton;

    //ComboBox
    QComboBox *noteComboBox;
    QComboBox *hsComboBox;
    QComboBox *parametersComboBox;

    //Label

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void constructMenuBar();
    void constructLayout();
    void constructChordsLayout();
    void constructChoicesLayout();
    void constructScalesLayout();

    void clearLayout(QLayout *layout, bool deleteWidgets);

public slots :
    void slotAddButton();
    void slotGenerateButton();
};

#endif // MAINWINDOW_H
