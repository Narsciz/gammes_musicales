#ifndef UT_H
#define UT_H
#include "view/mainwindow.h"
#include "modele/scaledictionary.h"
#include "modele/chorddictionary.h"
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
    QVector<QVector<QString> > convertCStoView(std::vector<std::vector<CS*> >);
    std::vector<std::vector<CS*> > convertCStoModel(QVector<QVector<QString> >);

public slots:
    void generateSlot(QVector<QVector<QString> > listChords);
};

#endif // UT_H
