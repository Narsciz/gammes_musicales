#ifndef UT_H
#define UT_H
#include "view/mainwindow.h"
#include "modele/scaledictionary.h"
#include "modele/chorddictionary.h"
#include "modele/algobrut.h"
#include "modele/algoopti.h"
#include "modele/algobrutomega.h"
#include "modele/abstractalgo.h"
#include "modele/algo.h"
#include "modele/cs.h"
#include "modele/scale.h"
#include "modele/chord.h"
#include "modele/parametres.h"
#include <thread>
#include <QObject>

class Ut : public QObject
{
    Q_OBJECT

private:
    AbstractAlgo* algo = new AlgoBrut();
    std::thread algoThread;
    std::thread joinThread;
    MainWindow* w;

public:
    Ut(MainWindow* w);

    QVector<QVector<QString> > convertCStoView(std::vector<std::vector<Scale*> >);
    std::vector<Chord*> convertChordstoModel(QVector<QString> cs);
    std::vector<Scale*> convertScalestoModel(QVector<QString> cs);

    QString SaveScale(QVector<QString> listChords, QVector<QString> listScale);
    QVector<QVector<QString> > convertScaleToString(std::vector<std::vector<Scale*> > scalesToConvert);

    void join();

public slots:
    void displayResultsSlot();
    void generateSlot(QVector<QString> listChords);
    void SaveScaleSlot(QVector<QString> listChords, QVector<QString> listScale);
    void ExportScaleSlot(QVector<QString> listChords, QVector<QString> listScale);
    void createChordSlot(QString name, vector<int> hs);
    void createScaleSlot(QString name, vector<int> hs, QString alias);
    void deleteChordSlot(HSChord* hs);
    void deleteScaleSlot(HSScale* hs);

signals:
    void displayResultsSignal();
};

#endif // UT_H
