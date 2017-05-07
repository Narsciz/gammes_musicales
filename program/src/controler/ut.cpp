#include "controler/ut.h"
#include "modele/export.cpp"

Ut::Ut(MainWindow *w)
{

    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();

    this->w = w;
    QObject::connect(this->w, SIGNAL(generateSignal(QVector<QString>)), this, SLOT(generateSlot(QVector<QString>)));
    QObject::connect(this->w, SIGNAL(SaveScaleSignal(QVector<QString>,QVector<QString>)), this, SLOT(SaveScaleSlot(QVector<QString>,QVector<QString>)));
    QObject::connect(this->w, SIGNAL(ExportScaleSignal(QVector<QString>,QVector<QString>)), this, SLOT(ExportScaleSlot(QVector<QString>,QVector<QString>)));

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

vector<Chord*> Ut::convertChordstoModel(QVector<QString> cs){
    vector<Chord*> res;
    for (int i=0;i<cs.size();i++)
    {
            res.push_back(new Chord(cs[i]));
    }
    return res;
}

vector<Scale*> Ut::convertScalestoModel(QVector<QString> cs){
    vector<Scale*> res;
    for (int i=0;i<cs.size();i++)
    {
            res.push_back(new Scale(cs[i]));
    }
    return res;
}

QVector<QVector<QString>> Ut::convertScaleToString(vector<vector<Scale*>> scalesToConvert){
    QVector<QVector<QString>> stringScalesToVector;
    QVector<QString> line;
    for(int i=0; i<scalesToConvert.size();i++){

        for(int j=0; j<scalesToConvert[i].size();j++){
            line.push_back(scalesToConvert[i][j]->getName());
        }
        stringScalesToVector.push_back(line);
        line.clear();
    }

    return stringScalesToVector;
}

QString Ut::SaveScale(QVector<QString> listChords, QVector<QString> listScale)
{
    QString chords = "";
    QString scales = "";
    for(int i = 0; i<listChords.size(); i++)
    {
        chords += "|";
        scales += "|";
        if(listChords[i].size()<listScale[i].size())
        {
            int diff = listScale[i].size() - listChords[i].size();
            for(int j = 0; j<=diff; j++)
            {
                if(j<diff/2)
                {
                    chords += " ";
                }
                if(j == diff/2)
                {
                    chords += listChords[i];
                }
                if(j>diff/2)
                {
                    chords += " ";
                }
            }
            scales += listScale[i];
        }
        else
        {
            if(listChords[i].size()>listScale[i].size())
            {
                int diff = listChords[i].size() - listScale[i].size();
                for(int j = 0; j<=diff; j++)
                {
                    if(j<diff/2)
                    {
                        scales += " ";
                    }
                    if(j == diff/2)
                    {
                        scales += listScale[i];
                    }
                    if(j>diff/2)
                    {
                        scales += " ";
                    }
                }
                chords += listChords[i];
            }
            else
            {
                chords += listChords[i];
                scales += listScale[i];
            }
        }
    }
    chords += "|";
    chords += '\n';
    scales += "|";
    return chords + scales;
}

 void Ut::generateSlot(QVector<QString> listChordsName)
 {
     try {
        vector<Chord*> listChords = convertChordstoModel(listChordsName);

        ParametersDisplay* parametres = this->w->getParametersDisplay();
        AbstractAlgo *algo;
        switch(parametres->getAlgo())
        {
        case 1:
            algo = new AlgoBrut(listChords, ScaleDictionary::getInstance()->getScalesByTypes(parametres->getlistAllowedHSscales()));
            break;
        case 2:
            algo = new AlgoOpti(listChords, ScaleDictionary::getInstance()->getScalesByTypes(parametres->getlistAllowedHSscales()));
            break;
        }

        switch(parametres->getParameter())
        {
        case 1:
            algo->findLeastsConsecutivesNotesChanges();
            break;
        case 2:
            algo->findLeastsConsecutivesScalesChanges();
            break;
        }

        w->constructScaleFoundView(convertScaleToString(algo->getResults()));
     }
     // Exception levee quand un accord est mal ecrit (B7 au lieu de B:7 par exemple)
     catch(out_of_range out_of_range_exception) {
         cout << out_of_range_exception.what() << endl;
     }
 }

 void Ut::SaveScaleSlot(QVector<QString> listChords, QVector<QString> listScale)
 {
     QString path = this->w->openExplorer(2);
     QStringList ext = path.split('.');
     if(ext.last()!="txt")
         path += ".txt";

     QString content = SaveScale(listChords, listScale);

     this->w->saveFile(path, content);
 }
 void Ut::ExportScaleSlot(QVector<QString> listChordsName, QVector<QString> listScaleName)
 {
     QString path = this->w->openExplorer(3);
     QStringList ext = path.split('.');
     if(ext.last()!="xml")
         path += ".xml";

     vector<Chord*> listChords = convertChordstoModel(listChordsName); //Exporter les Chords en MIDI ?
     vector<Scale*> listScales = convertScalestoModel(listScaleName);

     QString content=QString::fromStdString(exportMusicXML(listScales));

     this->w->saveFile(path, content);
 }

