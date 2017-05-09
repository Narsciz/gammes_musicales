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
#include <QGroupBox>
#include <QCoreApplication>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <iostream>
#include <QFile>
#include <QSpacerItem>
#include <QTextStream>
#include "view/parametersdisplay.h"
using namespace std;

#include <QVector>

#include "chordslistdisplay.h"
#include "view/statsdisplay.h"
#include "scaleslistdisplay.h"

#include <thread>
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
    QGroupBox *choicesDisplay;
    ScalesListDisplay *sListDisplay;//Layout affichant les gammes générées, "hidden" avant lancement de l'algorithme, "visible" après lancement


    //Button
    QPushButton *addButton;
    QPushButton *generateButton;
    QPushButton *returnButton;
    QPushButton *reinitializeButton;
    QPushButton *parametersButton;

    //ComboBox
    QComboBox *noteComboBox;
    QComboBox *hsComboBox;

    //Label
    QLabel *noteLabel;
    QLabel *hsLabel;

    //FileDialog
    QFileDialog *explorer;

    //Widget
    ParametersDisplay *parametersWindow;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void constructMenuBar();
    void constructLayout();
    void constructChordsLayout();
    void constructChoicesLayout();
    void constructScalesLayout();

    void clearLayout(QLayout *layout, bool deleteWidgets);
    QString openExplorer(int i);
    static QVector<QString> testFile(QString filePath);
    void saveFile(QString filePath, QString fileContent);
    void resizeEvent ( QResizeEvent * event );
    void fillComboBoxHS(QVector<QString> listHS);
    void fillParametersLists(QVector<QString> listHSChords, QVector<QString> listHSScales);
    void constructScaleFoundView(QVector<QVector<QString> > listFoundScales);
    ParametersDisplay *getParametersDisplay();
    void goToResultsInterface();

public slots :
    void slotAddButton();
    void slotGenerateButton();
    void slotReturnButton();
    void slotReinitializeButton();
    void slotParametersButton();
    void slotNewFile();
    void slotImportFile();
    void slotSaveFile();
    void slotCloseFile();
    void slotDebugTestFile();
    void slotSaveScale(QVector<QString> listScale);
    void slotExportScale(QVector<QString> listScale);
    void slotStats();


signals :

    void generateSignal(QVector<QString> listChords);
    void SaveScaleSignal(QVector<QString> listChords, QVector<QString> listScale);
    void ExportScaleSignal(QVector<QString> listChords, QVector<QString> listScale);
};

#endif // MAINWINDOW_H
