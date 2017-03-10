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

#include "chordsdisplaylayout.h"
#include "scalesdisplaylayout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    //Layout
    QGridLayout *mainLayout;
    QGridLayout *chordsLayout;
    QGridLayout *choicesLayout;
    QGridLayout *scalesLayout;
    ChordsDisplayLayout *cdLayout;
    ScalesDisplayLayout *sdLayout;

    //Button
    QPushButton *addButton;
    QPushButton *generateButton;

    //ComboBox
    QComboBox *noteComboBox;
    QComboBox *hsComboBox;
    QComboBox *parametersComboBox;

    //Label
    QLabel *chordsLabel;
    QLabel *scalesLabel;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void constructMenuBar();
    void constructLayout();
    void constructChordsLayout();
    void constructChoicesLayout();
    void constructScalesLayout();

    void clearLayout(QLayout *layout, bool deleteWidgets);
};

#endif // MAINWINDOW_H
