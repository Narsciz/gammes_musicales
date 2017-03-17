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
            generateSols(index++,solutionPossible);
        }

    }
}
