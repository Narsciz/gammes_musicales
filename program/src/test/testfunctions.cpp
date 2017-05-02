#include "testfunctions.h"

using namespace std;

void testAlgo(string algoName,string algoConstraint)
{
    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    vector<Chord*> SA;
    vector<Chord*> allowedChords=ChordDictionary::getInstance()->getAllChords();
    vector<Scale*> allowedScales=ScaleDictionary::getInstance()->getAllScales();
    allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();

    for (int i=0;i<4;i++)
        SA.push_back(allowedChords[i]);

    cout<<"suite d'accords :"<<endl<<flush;
    for (size_t i=0;i<SA.size();i++)
        cout<<SA[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    cout<<"gammes autorisées"<<endl<<flush;
    for (size_t i=0;i<allowedScales.size();i++)
        cout<<allowedScales[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    AbstractAlgo *algo;

    if (algoName=="brut")
        algo=new AlgoBrut(SA,ScaleDictionary::getInstance()->getAllScales());
    else if (algoName=="omega")
        algo=new AlgoBrutOmega(SA,ScaleDictionary::getInstance()->getAllScales());
    else if (algoName=="optimise")
        algo=new AlgoOpti(SA,ScaleDictionary::getInstance()->getAllScales());

    if (algoConstraint=="consecutivesNotes")
        algo->findLeastsConsecutivesNotesChanges();
    else if (algoConstraint=="consecutivesScales")
        algo->findLeastsConsecutivesScalesChanges();
    else if (algoConstraint=="totalScales")
        algo->findLeastsTotalScales();

    vector<vector<Scale*> > results=algo->getResults();

    cout<<"solution :"<<endl<<flush;
    for (size_t i=0;i<results.size();i++)
    {
        QString ligne="";
        for (size_t j=0;j<results[i].size();j++)
            ligne+="|"+results[i][j]->getName();
        cout<<ligne.toStdString()<<endl<<flush;
    }

    cout<<endl<<flush;

}

void displayGAKO(vector<vector<Node*> > GAKO)
{
    for (size_t i=0;i<GAKO.size();i++)
    {
        for (size_t j=0;j<GAKO[i].size();j++)
        {
            if (GAKO[i][j]->getScale()!=NULL)
                GAKO[i][j]->display();
            else cout<<"sommet entree ou sortie"<<flush;
            cout<<"|"<<flush;
        }
        cout<<endl<<flush;
    }
}


void testGAKO()
{

    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    vector<Chord*> SA;
    vector<Chord*> allowedChords=ChordDictionary::getInstance()->getAllChords();
    vector<Scale*> allowedScales=ScaleDictionary::getInstance()->getAllScales();
    allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();

    for (int i=0;i<4;i++)
        SA.push_back(allowedChords[i]);

    cout<<"suite d'accords :"<<endl<<flush;
    for (size_t i=0;i<SA.size();i++)
        cout<<SA[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    cout<<"gammes autorisées"<<endl<<flush;
    for (size_t i=0;i<allowedScales.size();i++)
        cout<<allowedScales[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    cout<<"GAKO"<<endl<<flush;
    displayGAKO(AlgoOpti::KpartitesToGAKO(KpartitesScales(SA)));

}

void testAlgoOpti()
{
    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    vector<Chord*> SA;
    vector<Chord*> allowedChords=ChordDictionary::getInstance()->getAllChords();
    vector<Scale*> allowedScales=ScaleDictionary::getInstance()->getAllScales();
    allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();

    for (int i=0;i<4;i++)
        SA.push_back(allowedChords[i]);

    cout<<"suite d'accords :"<<endl<<flush;
    for (size_t i=0;i<SA.size();i++)
        cout<<SA[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    cout<<"gammes autorisées"<<endl<<flush;
    for (size_t i=0;i<allowedScales.size();i++)
        cout<<allowedScales[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    AlgoOpti algo(SA,ScaleDictionary::getInstance()->getAllScales());
    algo.findLeastsConsecutivesNotesChanges();
    vector<vector<Scale*> > contrainte1=algo.getResults();

    cout<<"solution :"<<endl<<flush;
    for (size_t i=0;i<contrainte1.size();i++)
    {
        QString ligne="";
        for (size_t j=0;j<contrainte1[i].size();j++)
            ligne+="|"+contrainte1[i][j]->getName();
        cout<<ligne.toStdString()<<endl<<flush;
    }

    cout<<endl<<flush;

}
