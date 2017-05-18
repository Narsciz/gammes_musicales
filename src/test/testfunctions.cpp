#include "testfunctions.h"
#include "view/mainwindow.h"
#include <time.h>
#include <iomanip>
//#include "checkmemory.h"

using namespace std;

void testAlgo(string algoName, string algoConstraint, int limit)
{
    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    vector<Chord*> suiteAccords;
    vector<Chord*> allowedChords = ChordDictionary::getInstance()->getAllChords();
    vector<Scale*> allowedScales = ScaleDictionary::getInstance()->getAllScales();


    QVector<QString> chords = MainWindow::testFile("../assets/imports/RoundMidnight.txt");

    for(int i = 0; i < chords.size(); i++)
        suiteAccords.push_back(new Chord(chords[i]));

    cout << "Suite d'accords :" << endl << flush;
    for (size_t i = 0; i < suiteAccords.size(); i++)
        cout << suiteAccords[i]->getName().toStdString() << "|" << flush;
    cout << endl << endl << flush;

    clock_t tStart = clock();
    AbstractAlgo *algo;

    if (algoName == "brut")
        algo = new AlgoBrut(suiteAccords, ScaleDictionary::getInstance()->getAllScales());
    else if (algoName == "omega")
        algo = new AlgoBrutOmega(suiteAccords, ScaleDictionary::getInstance()->getAllScales());
    else if (algoName == "optimise"){
        algo = new AlgoOpti(suiteAccords, ScaleDictionary::getInstance()->getAllScales());
        algo->setLimit(limit);
    } else algo = new AlgoBrut(suiteAccords, ScaleDictionary::getInstance()->getAllScales());

    vector<vector<Scale*> > filteredKpartiteGraph = algo->getFilteredKpartiteGraph();

    cout << "Filtered Kpartite Graph : " << endl << flush;
    for (size_t i = 0; i < filteredKpartiteGraph.size(); i++){
        for (size_t j = 0; j < filteredKpartiteGraph[i].size(); j++)
            cout << filteredKpartiteGraph[i][j]->getName().toStdString() << "|" << flush;
        cout << endl << flush;
    }
    cout << endl << flush;

    try
    {
        if (algoConstraint == "consecutivesNotes")
            algo->findLeastsConsecutivesNotesChanges();
        else if (algoConstraint == "consecutivesScales")
            algo->findLeastsConsecutivesScalesChanges();
        else if (algoConstraint == "totalScales")
            algo->findLeastsTotalScales();
    }
    catch (std::bad_alloc& ba)
    {
        cout << "bad_alloc caught: " << ba.what() << '\n';
    }

    vector<vector<Scale*> > results = algo->getResults();

    cout << "Solution :" << endl << flush;
    for (size_t i = 0; i < results.size(); i++)
    {
        QString ligne = "";
        for (size_t j = 0; j < results[i].size(); j++)
            ligne += "|" + results[i][j]->getName();

        cout << ligne.toStdString() << endl << flush;
    }

    cout << endl << flush;

    cout << "Time taken for " << algoName
         << ", " << algoConstraint << " : "
         << setiosflags(ios::fixed) << setprecision(4) << (double)(clock() - tStart)/CLOCKS_PER_SEC << " secs."
            << endl << flush;

}

void displayGAKO(vector<vector<Node*> > GAKO)
{
    for (size_t i = 0; i < GAKO.size(); i++)
    {
        for (size_t j = 0; j < GAKO[i].size(); j++)
        {
            if (GAKO[i][j]->getScale() != NULL)
                GAKO[i][j]->display();
            else cout << "sommet entree ou sortie" << flush;
            cout << "|" << flush;
        }
        cout<<endl<<flush;
    }
}


void testGAKO()
{

    ChordDictionary::getInstance()->generateBaseChords();
    ScaleDictionary::getInstance()->generateBaseScale();
    vector<Chord*> suiteAccords;
    vector<Chord*> allowedChords = ChordDictionary::getInstance()->getAllChords();
    vector<Scale*> allowedScales = ScaleDictionary::getInstance()->getAllScales();
    allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();allowedScales.pop_back();

    for (int i=0;i<4;i++)
        suiteAccords.push_back(allowedChords[i]);

    cout<<"suite d'accords :"<<endl<<flush;
    for (size_t i=0;i<suiteAccords.size();i++)
        cout<<suiteAccords[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    cout<<"gammes autorisées"<<endl<<flush;
    for (size_t i=0;i<allowedScales.size();i++)
        cout<<allowedScales[i]->getName().toStdString()<<"|"<<flush;
    cout<<endl<<flush;

    cout<<"GAKO"<<endl<<flush;
    displayGAKO(AlgoOpti::KpartitesToGAKO(KpartitesScales(suiteAccords)));

}


