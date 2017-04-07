#include "controler/ut.h"

Ut::Ut(MainWindow *w)
{

    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();

    this->w = w;
    QObject::connect(this->w, SIGNAL(generateSignal(QVector<QString>)), this, SLOT(generateSlot(QVector<QString>)));

    w->fillComboBoxHS(ChordDictionary::getInstance()->getHSnames());
    w->fillParametersLists(ChordDictionary::getInstance()->getHSnames(), ScaleDictionary::getInstance()->getHSnames());
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

 void Ut::generateSlot(QVector<QString> listChordsName)
 {
    vector<Chord*> listChords = convertCStoModel(listChordsName);
    vector<vector<Scale*> > k = KpartitesScales(listChords);
    for (int i=0;i<k.size();i++){
        for (int j=0;j<k[i].size();j++)
            cout<<k[i][j]->getName().toStdString()<<"|"<<flush;
        cout<<endl<<flush;
    }
    AlgoBrut algobrut(k);
    algobrut.generateSols();
    vector<vector<Scale*> > SP=algobrut.getSols();

    vector<vector<Scale*>> temp = algobrut.findLeastsTotalScales();


    QVector<QVector<QString>> res = convertCStoView(temp);

    w->constructScaleFoundView(res);

    /*
    Parametres parametres(this->w->getParametersDisplay());
    AbstractAlgo algo;
    switch(parametres.getAlgo())
    {
    case 1: algo = AlgoBrut(convertCStoModel(parametres.getAllowedScales()));
    case 2: algo = AlgoOpti(convertCStoModel(parametres.getAllowedScales()));
    }
    switch(parametres.getParameter())
    {
    case 1: algo.findLeastsConsecutivesNotesChanges();
    case 2: algo.findLeastsConsecutivesScalesChanges();
    }
    w->constructScaleFoundView(algo.getSoluces());
    */
 }
