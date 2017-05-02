#include "abstractalgo.h"

using namespace std;

AbstractAlgo::AbstractAlgo(std::vector<Chord*> data, std::vector<Scale*> allowedScales)
{
    this->data = data;
    this->allowedScales = allowedScales;
    KpartiteGraph=KpartitesScales(data);
    filterAllowedChordsInK();
}

std::vector<std::vector<Scale*> > AbstractAlgo::getResults()
{
    return this->results;
}



void AbstractAlgo::filterAllowedChordsInK()
{
    filteredKpartiteGraph.clear();
    vector<Scale*> ligne;

    for (size_t i=0;i<KpartiteGraph.size();i++)
    {
        for (size_t j=0;j<KpartiteGraph[i].size();j++)
            if (isScaleInScales(KpartiteGraph[i][j],allowedScales))
                ligne.push_back(KpartiteGraph[i][j]);
        filteredKpartiteGraph.push_back(ligne);
        ligne.clear();
    }
    cout<<"filteredKpartiteGraph in constructor:"<<endl<<flush;
    for (size_t i=0;i<filteredKpartiteGraph.size();i++){
        for (size_t j=0;j<filteredKpartiteGraph[i].size();j++)
            cout<<filteredKpartiteGraph[i][j]->getName().toStdString()<<"|"<<flush;
        cout<<endl<<flush;
    }

}
