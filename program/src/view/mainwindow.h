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
using namespace std;

#include <QVector>

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
    QGroupBox *choicesDisplay;
    ScalesListDisplay *sListDisplay;//Layout affichant les gammes générées, "hidden" avant lancement de l'algorithme, "visible" après lancement


    //Button
    QPushButton *addButton;
    QPushButton *generateButton;
    QPushButton *returnButton;
    QPushButton *reinitializeButton;

    //ComboBox
    QComboBox *noteComboBox;
    QComboBox *hsComboBox;
    QComboBox *parametersComboBox;

    //Label
    QLabel *noteLabel;
    QLabel *hsLabel;
    QLabel *parametersLabel;

    //FileDialog
    QFileDialog *explorer;

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
    QVector<QString> testFile(QString filePath);
    void resizeEvent ( QResizeEvent * event );
    void fillComboBoxHS(QVector<QString> listHS);
    void constructScaleFoundView(QVector<QVector<QString>> listFoundScales);

public slots :
    void slotAddButton();
    void slotGenerateButton();
    void slotReturnButton();
    void slotReinitializeButton();
    void slotNewFile();
    void slotImportFile();
    void slotSaveFile();
    void slotCloseFile();
    void slotDebugTestFile();

signals :
    void generateSignal(QVector<QString> listChords, int parameter);
};

#endif // MAINWINDOW_H
