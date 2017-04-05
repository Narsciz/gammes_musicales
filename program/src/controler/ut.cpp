#include "controler/ut.h"

Ut::Ut(MainWindow *w)
{

    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();

    this->w = w;
    QObject::connect(this->w, SIGNAL(generateSignal(QVector<QString>,int)), this, SLOT(generateSlot(QVector<QString>, int)));

    w->fillComboBoxHS(ChordDictionary::getInstance()->getHSnames());
}

QVector<QVector<QString> > Ut::convertCStoView(vector<vector<Scale*> > cs){
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

vector<Chord*> Ut::convertCStoModel(QVector<QString> cs){
    vector<Chord*> res;
    for (int i=0;i<cs.size();i++)
    {
            res.push_back(new Chord(cs[i]));
    }
    return res;
}

 void Ut::generateSlot(QVector<QString> listChordsName, int parameter)
 {
    vector<Chord*> listChords = convertCStoModel(listChordsName);
    vector<vector<Scale*>> k = KpartitesScales(listChords);
    AlgoBrut algobrut(k);
    vector<Scale*> vect;
    algobrut.generateSols(0, vect);

    vector<vector<Scale*>> temp = algobrut.findLeastsConsecutivesNotesChanges();


    QVector<QVector<QString>> res = convertCStoView(temp);

    w->constructScaleFoundView(res);
 }
