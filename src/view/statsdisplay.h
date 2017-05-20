#ifndef STATSDISPLAY_H
#define STATSDISPLAY_H

#include <QTabWidget>
#include <QWidget>
#include <QSizePolicy>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QFile>
#include <iostream>
#include <QMessageBox>

using namespace std;

class StatsDisplay : public QWidget
{
    Q_OBJECT

private:
    QWidget *centralWidget;

    QTabWidget *tab;
    QWidget *scale;
    QGridLayout *scaleLayout;
    QWidget *note;
    QGridLayout *noteLayout;
    QWidget *totalScale;
    QGridLayout *totalScaleLayout;

    QTableWidget *scaleView;
    QTableWidget *noteView;
    QTableWidget *totalScaleView;

public:
    StatsDisplay();
    void createScaleTab();
    void createNoteTab();
    void createTotalScaleTab();
    QVector<QStringList> loadFile(QString path);
};

#endif // STATSDISPLAY_H
