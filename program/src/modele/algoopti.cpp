#include "algoopti.h"

using namespace std;

AlgoOpti::AlgoOpti(std::vector<Chord*> SA, std::vector<Scale*> AS) : AbstractAlgo(SA,AS)
{
    GAKO = KpartitesToGAKO(KpartiteGraph);
    cout<<"fin constructeur"<<endl;
}

void AlgoOpti::findLeastsConsecutivesNotesChanges()
{
    cout<<"pcc"<<endl;
    calculatePCCs("symetrical_difference");
    results.clear();
    vector<Scale*> vide;
    cout<<"recursion"<<endl;
    generateSolutions(GAKO.back().back(),vide);

}

void AlgoOpti::findLeastsConsecutivesScalesChanges()
{

    calculatePCCs("binary");
    results.clear();
    vector<Scale*> vide;
    generateSolutions(GAKO.back().back(),vide);
}

vector<Scale*> reverse(vector<Scale*> v)
{
    vector<Scale*> res;
    for (size_t i=0;i<v.size();i++)
        res.push_back(v[v.size()-1-i]);
    return res;
}

void AlgoOpti::generateSolutions(Node * currentNode,vector<Scale*> solution)
{
    if (currentNode->predecessors.empty()){
        solution=reverse(solution);
        solution.pop_back();
        results.push_back(solution);
    }
    else
    {
        vector<Scale*> sol=solution;
        sol.push_back(currentNode->g);
        for (size_t i=0;i<currentNode->predecessors.size();i++)
            generateSolutions(currentNode->predecessors[i],sol);
    }
}

void AlgoOpti::calculatePCCs(string ponderation)
{
    // indice de la k-partie contenant les voisins d'un sommet
    int neighbours;

    // Double boucle pour respecter l'ordre topologique
    for(size_t i = 0; i < GAKO.size(); i++) {


        for(size_t j = 0; j < GAKO[i].size(); j++) {

            // Boucle sur les voisins de GAKO[i][j]
            cout<<i<<","<<j<<endl;
            neighbours = GAKO[i][j]->index;
            if (neighbours>=0)
                for(size_t k = 0; k < GAKO[neighbours].size(); k++){cout<<"k:"<<k<<endl;
                    relax(GAKO[i][j], GAKO[neighbours][k], ponderation);
                }

        }
    }
}

vector<vector<Node*> > AlgoOpti::KpartitesToGAKO(vector<vector<Scale*> > Kpartite)
{

    vector<vector<Node*> > Graph;
    vector<Node*> nodeList;
    vector<Node*> predecessors;//liste des prédecesseurs toujours vide

    //node entrée
    vector<Node*> entree;
    entree.push_back(new Node(1,0,predecessors,NULL));
    Graph.push_back(entree);

    for (size_t i=1;i<Kpartite.size();i++){
        nodeList.clear();

        for (size_t j=0;j<Kpartite[i].size();j++)
            nodeList.push_back(new Node(i+1,INT_MAX,predecessors,Kpartite[i][j]));

        Graph.push_back(nodeList);
    }

    //node sortie
    vector<Node*> sortie;
    sortie.push_back(new Node(-1,INT_MAX,predecessors,NULL));
    Graph.push_back(sortie);

    return Graph;
}

int AlgoOpti::ponderation(Node* u, Node* v, string type)
{
    cout<<"ponderation"<<endl;
    // fonction de ponderation binaire
    if(type == "binary") {
        if  (u->g!=NULL && v->g!=NULL)
            return (u->getScale()->sameNotes(v->getScale())) ? 1 : 0;
        else return 0;

    }
    // fonction de ponderation basee sur la difference symetrique
    else if(type == "symetrical_difference") {
        if (u->g!=NULL && v->g!=NULL)
            return u->g->notesDifferencesWithScale(v->g);
        else return 0;
    }
    else return -1;
}

void AlgoOpti::relax(Node* u, Node* v, string ponderationType)
{
    if(v->distanceRoot > u->distanceRoot + ponderation(u, v, ponderationType)) {
        v->distanceRoot = u->distanceRoot + ponderation(u, v, ponderationType);
        vector<Node*> newPreds;
        newPreds.push_back(u);
        v->predecessors=newPreds;
    }
}
