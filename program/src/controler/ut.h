#ifndef UT_H
#define UT_H
#include "view/mainwindow.h"
#include "modele/scaledictionary.h"
#include "modele/chorddictionary.h"
#include "modele/algobrut.h"
#include "modele/algo.h"
#include "modele/cs.h"
#include "modele/scale.h"
#include "modele/chord.h"
#include <QObject>

class Ut : public QObject
{
    Q_OBJECT
private:
    MainWindow *w;
    ChordDictionary *cd;
    //ScaleDictionary sd;

public:
    Ut(MainWindow *w);
    QVector<QVector<QString> > convertCStoView(std::vector<std::vector<Scale*> >);
    std::vector<Chord*> convertCStoModel(QVector<QString> cs);

public slots:
    void generateSlot(QVector<QString> listChords, int parameter);
};

#endif // UT_H
