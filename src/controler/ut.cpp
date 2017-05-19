#include "controler/ut.h"
#include "modele/export.cpp"

Ut::Ut(MainWindow *w)
{

    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    ChordDictionary::getInstance()->generateCustomChords();
    ScaleDictionary::getInstance()->generateCustomScale();

    this->w = w;
    QObject::connect(this->w, SIGNAL(generateSignal(QVector<QString>)), this, SLOT(generateSlot(QVector<QString>)));
    QObject::connect(this->w, SIGNAL(SaveScaleSignal(QVector<QString>,QVector<QString>)), this, SLOT(SaveScaleSlot(QVector<QString>,QVector<QString>)));
    QObject::connect(this->w, SIGNAL(ExportScaleSignal(QVector<QString>,QVector<QString>)), this, SLOT(ExportScaleSlot(QVector<QString>,QVector<QString>)));
    QObject::connect(this,SIGNAL(displayResultsSignal()),this,SLOT(displayResultsSlot()));
    QObject::connect(this->w, SIGNAL(createChordSignal(QString,vector<int>)), this, SLOT(createChordSlot(QString,vector<int>)));
    QObject::connect(this->w, SIGNAL(createScaleSignal(QString,vector<int>, QString)), this, SLOT(createScaleSlot(QString,vector<int>,QString)));
    QObject::connect(this->w, SIGNAL(deleteChordSignal(HSChord*)), this, SLOT(deleteChordSlot(HSChord*)));
    QObject::connect(this->w, SIGNAL(deleteScaleSignal(HSScale*)), this, SLOT(deleteScaleSlot(HSScale*)));

    w->fillComboBoxHS(ChordDictionary::getInstance()->getHSnames());
    w->fillParametersLists(ScaleDictionary::getInstance()->getBaseHSnames(), ScaleDictionary::getInstance()->getCustomHSnames());
    cout<<"end creating ut"<<endl<<flush;
}


void Ut::displayResultsSlot()
{
    w->goToResultsInterface();
    w->constructScaleFoundView(convertScaleToString(algo->getResults()));
    delete algo;
}


QVector<QVector<QString> > Ut::convertCStoView(vector<vector<Scale*> > cs)
{
    QVector<QVector<QString> > res;
    QVector<QString> ligne;
    for (size_t i=0; i<cs.size(); i++)
    {
        for (size_t j=0; j<cs[i].size(); j++)
            ligne.push_back(cs[i][j]->getName());
        res.push_back(ligne);
        ligne.clear();
    }
    return res;
}

vector<Chord*> Ut::convertChordstoModel(QVector<QString> cs)
{
    vector<Chord*> res;
    for (int i=0; i<cs.size(); i++)
    {
        res.push_back(new Chord(cs[i]));
    }
    return res;
}

vector<Scale*> Ut::convertScalestoModel(QVector<QString> cs)
{
    vector<Scale*> res;
    for (int i=0; i<cs.size(); i++)
    {
        res.push_back(new Scale(cs[i]));
    }
    return res;
}

QVector<QVector<QString>> Ut::convertScaleToString(vector<vector<Scale*>> scalesToConvert)
{
    QVector<QVector<QString>> stringScalesToVector;
    QVector<QString> line;
    for(size_t i=0; i<scalesToConvert.size(); i++)
    {

        for(size_t j=0; j<scalesToConvert[i].size(); j++)
        {
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

void Ut::join()
{

    if (algoThread.joinable())
        algoThread.join();
    else return;

    emit displayResultsSignal();

}

void Ut::generateSlot(QVector<QString> listChordsName)
{
    try
    {
        vector<Chord*> listChords = convertChordstoModel(listChordsName);

        ParametersDisplay* parametres = this->w->getParametersDisplay();

        switch(parametres->getAlgo())
        {
        case 1:
            algo = new AlgoBrutOmega(listChords, ScaleDictionary::getInstance()->getScalesByTypes(parametres->getlistAllowedHSscales()));
            algo->setLimit(parametres->getLimit());
            break;
        case 2:
            algo = new AlgoOpti(listChords, ScaleDictionary::getInstance()->getScalesByTypes(parametres->getlistAllowedHSscales()));
            algo->setLimit(parametres->getLimit());
            break;
        case 3:
            algo = new AlgoBrut(listChords, ScaleDictionary::getInstance()->getScalesByTypes(parametres->getlistAllowedHSscales()));
            algo->setLimit(parametres->getLimit());
            break;
        }

        if (algoThread.joinable())
            algoThread.detach();

        switch(parametres->getParameter())
        {
        case 1:
            algo->callConsecutivesScalesChangesInThread(algoThread);
            break;
        case 2:
            algo->callConsecutivesNotesChangesInThread(algoThread);
            break;
        case 3:
            algo->callTotalScalesInThread(algoThread);
            break;
        }

        /**** thread manière 1 *****/
        //detach enlève le lien entre l'objet algoThread et la fonction callThread du modèle, ça permet d'autoriser plusieurs générations d'accords en même temps
        //et ça évite que le programme plante si on quitte le programme sans que tous les threads aient fini de s'éxécuter
        //mais même si on peut lancer plusieurs générations en même temps, seulement les résultats de la dernière pourront être extraites, donc ça sert à rien de spammer le bouton générer (à part si on veut bouffer toute la ram de l'ordi)
        //si c'était possible de plutôt stopper un thread de manière simple, ce serait sûrement mieux, mais c'est compliqué apparemment...
        //du coup il faut appuyer sur le bouton afficher quand l'algo finit pour avoir le résultat
        //fonctionnerait sans bouton afficher si on autorisait le modèle à envoyer un message au controler (appel de fonction ou directement signal) quand l'algo termine
        //algoThread.detach();


        /*** thread manière 2 ******/
        //joinThread est un autre thread qui attend que algoThread finisse (avec un join sur algoThread) et quand il a fini, il emet le signal d'afficher le résultat (displaySignal)
        //il faut le détacher parce qu'on pourra jamais le réutiliser sinon
        //marche bien, mais il faut pas oublier de détacher algoThread aussi plus haut
        Ut* ut = this;

        std::thread(&Ut::join, ut).detach();

        w->constructScaleFoundView(convertScaleToString(algo->getResults()));

    }
    // Exception levee quand un accord est mal ecrit (B7 au lieu de B:7 par exemple)
    catch(out_of_range out_of_range_exception)
    {
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

    QString content = exportMusicXML(listScales, listChords);

    this->w->saveFile(path, content);
}

void Ut::createChordSlot(QString name, vector<int> hs)
{
    ChordDictionary::getInstance()->addCustom(new HSChord(name, hs));
    w->fillComboBoxHS(ChordDictionary::getInstance()->getHSnames());
}

void Ut::createScaleSlot(QString name, vector<int> hs, QString alias)
{
    ScaleDictionary::getInstance()->addCustom(new HSScale(name, hs, alias));
    this->w->slotReturnButton();
    w->fillParametersLists(ScaleDictionary::getInstance()->getBaseHSnames(), ScaleDictionary::getInstance()->getCustomHSnames());
}

void Ut::deleteChordSlot(HSChord* hs)
{
    ChordDictionary::getInstance()->removeCustom(hs);
    w->fillComboBoxHS(ChordDictionary::getInstance()->getHSnames());
}

void Ut::deleteScaleSlot(HSScale* hs)
{
    ScaleDictionary::getInstance()->removeCustom(hs);
    this->w->slotReturnButton();
    w->fillParametersLists(ScaleDictionary::getInstance()->getBaseHSnames(), ScaleDictionary::getInstance()->getCustomHSnames());

}
