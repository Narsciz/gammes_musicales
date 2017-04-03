#include "ut.h"

//Ut::Ut(MainWindow w)
Ut::Ut()
{

}
QVector<QVector<QString> > Ut::convertCStoView(vector<vector<CS*> > cs){
    QVector<QVector<QString> > res;
    QVector<QString> ligne;
    for (size_t i=0;i<cs.size();i++){
        for (size_t j=0;j<cs[i].size();j++)
            ligne.push_back(cs[i][j]->getName());
        res.push_back(ligne);
        ligne.clear();
    }
    return res;
}

vector<vector<CS*> > Ut::convertCStoModel(QVector<QVector<QString> > cs){
    vector<vector<CS*> > res;
    vector<CS*> ligne;
    for (int i=0;i<cs.size();i++){
        for (int j=0;j<cs[i].size();j++)
            ligne.push_back(new CS(cs[i][j]));//comme CS est un type "abstrait", il peut y avoir ambiguïté si une structure harmonique de gamme a le même nom que celle d'un accord, si les deux existent, la gamme est selectionnée (parce que c'est le dico de gamme qu'est parcouru en premier dans le constructeur de CS(QString) )
        res.push_back(ligne);
        ligne.clear();
    }
    return res;
}
