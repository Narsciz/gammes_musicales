#ifndef UT_H
#define UT_H
#include "view/mainwindow.h"
#include "modele/scaledictionary.h"
#include "modele/chorddictionary.h"

class Ut
{
private:
    MainWindow *w;


public:
    //Ut(MainWindow w);
    Ut();
    QVector<QVector<QString> > convertCStoView(std::vector<std::vector<CS*> >);
    std::vector<std::vector<CS*> > convertCStoModel(QVector<QVector<QString> >);
};

#endif // UT_H
