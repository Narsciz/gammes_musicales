#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void menubar();
};

#endif // MAINWINDOW_H
