#include "algobrut.h"

using namespace std;

AlgoBrut::AlgoBrut(std::vector<std::vector<Scale *> > graph):KpartiteGraph(graph)
{

}


void AlgoBrut::generateSols(int index,vector<Scale*> solutionPossible)
{

    if (index>=KpartiteGraph.size())
        solutionsPossibles.push_back(solutionPossible);
    else
    {
        for (int i=0;i<KpartiteGraph[index].size();i++)
        {
            solutionPossible.push_back(KpartiteGraph[index][i]);
            generateSols(index+1,solutionPossible);
        }

    }
}


vector<vector<Scale*> > AlgoBrut::findLeastsConsecutivesNotesChanges()
{
    vector<int> values;
    int value;
    int minValue=INFINITY;

    for (int i=0;i<solutionsPossibles.size();i++)//on remplit le tableau values
    {
        value=0;
        for (int j=0;j<solutionsPossibles[i].size()-1;j++)//on fait la somme des differences de notes entre chaque couple de gammes consécutives
            value+=solutionsPossibles[i][j]->notesDifferencesWithScale(solutionsPossibles[i][j+1]);
        values.push_back(value);
    }

    for (int i=0;i<values.size();i++)//on cherche la plus petite valeur possible
        minValue=min(values[i],minValue);

    vector<vector<Scale*> >res;
    for (int i=0;i<values.size();i++)
        if (values[i]==minValue)
            res.push_back(solutionsPossibles[i]);
    return res;

}
