#include "algobrut.h"

using namespace std;

AlgoBrut::AlgoBrut(vector<Chord*> SA,vector<Scale*> AS):AbstractAlgo(SA,AS)
{

}

void AlgoBrut::generateSolsRec(int index, vector<Scale*> solutionPossible)
{
    if ((int)filteredKpartiteGraph.size()>0){
        if (index >= (int)filteredKpartiteGraph.size())
           possiblesSolutions.push_back(solutionPossible);
        else
        {

            for (size_t i = 0; i < filteredKpartiteGraph[index].size(); i++)
            {
                vector<Scale*> sol = solutionPossible;
                sol.push_back(filteredKpartiteGraph[index][i]);

                generateSolsRec(index + 1, sol);

                /***plus performant mais plus moche***
                solutionPossible.push_back(filteredKpartiteGraph[index][i]);
                generateSolsRec(index + 1, solutionPossible);
                solutionPossible.pop_back();
                **************************************/
            }
        }
    }
}


void AlgoBrut::generatePossiblesSolutions(){
    possiblesSolutions.clear();
    vector<Scale*> vide;
    generateSolsRec(0,vide);
}

vector<vector<Scale*> > AlgoBrut::getSols(){return possiblesSolutions;}

void AlgoBrut::findLeastsConsecutivesNotesChanges()
{
    generatePossiblesSolutions();
    results.clear();

    vector<int> values;
    int value;


    for (size_t i=0; i<possiblesSolutions.size();i++)//on remplit le tableau values
    {
        value = 0;

        //on fait la somme des differences symétriques de notes entre chaque couple de gammes consécutives
        for (size_t j = 0; j<possiblesSolutions[i].size()-1;j++)
            value += possiblesSolutions[i][j]->notesDifferencesWithScale(possiblesSolutions[i][j+1]);
        values.push_back(value);
    }

    int minValue=10000000;
    for (size_t i=0;i<values.size();i++)//on cherche la plus petite valeur possible
        minValue=min(values[i],minValue);

    //vector<vector<Scale*> >res;
    for (size_t i=0;i<values.size();i++)//on ajoute dans le résultat retour toutes les occurences de la contrainte optimisée
        if (values[i]==minValue)
            results.push_back(possiblesSolutions[i]);

//    soluces=res;

}

void AlgoBrut::findLeastsConsecutivesScalesChanges()
{
    generatePossiblesSolutions();
    results.clear();
    vector<int> values;
    int value;

    for (size_t i=0;i<possiblesSolutions.size();i++)
    {
        value=0;
        for (size_t j=0;j<possiblesSolutions[i].size()-1;j++)
            if (!possiblesSolutions[i][j]->equals(possiblesSolutions[i][j+1]))//compare les noms et non les notes (donc si y a des gammes avec les mêmes noms mais des notes différentes, ou l'inverse y a problème)
                value++;
        values.push_back(value);
    }

    int minValue=100000000;
    for (size_t i=0;i<values.size();i++)
        minValue=min(minValue,values[i]);

    //vector<vector<Scale*> > res;
    for (size_t i=0;i<values.size();i++)
        if (values[i]==minValue)
            results.push_back(possiblesSolutions[i]);

    //return res;
}

void AlgoBrut::findLeastsTotalScales()
{
    generatePossiblesSolutions();
    results.clear();
    vector<int> values;
    vector<Scale*> distinctsScales;//sert à stocker les différentes gammes de chaque suite de gammes

    for (size_t i=0;i<possiblesSolutions.size();i++)
    {

        for (size_t j=0;j<possiblesSolutions[i].size();j++)
            if (!isScaleInScales(possiblesSolutions[i][j],distinctsScales))
                distinctsScales.push_back(possiblesSolutions[i][j]);

        values.push_back(distinctsScales.size());
        distinctsScales.clear();
    }

    int minValue=100000000;
    for (size_t i=0;i<values.size();i++)
        minValue=min(minValue,values[i]);

    //vector<vector<Scale*> > res;
    for (size_t i=0;i<values.size();i++)
        if (values[i]==minValue)
            results.push_back(possiblesSolutions[i]);

    //return res;
}
