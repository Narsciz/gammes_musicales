#include "algoopti.h"
#include <time.h>
#include <iomanip>
#include "./test/testfunctions.h"

using namespace std;

AlgoOpti::AlgoOpti(std::vector<Chord*> SA, std::vector<Scale*> AS) : AbstractAlgo(SA,AS)
{
    GAKO = KpartitesToGAKO(filteredKpartiteGraph);
}

void AlgoOpti::findLeastsConsecutivesNotesChanges()
{
    clock_t tStart = clock();

    calculatePCCs("symetrical_difference");
    results.clear();

    vector<Scale*> vide;
    generateSolutions(GAKO.back()[0], vide);

    double timeTaken = (double)(clock() - tStart)/CLOCKS_PER_SEC;
    QFile file("../stats/noteStats.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << ";3|" << data.size() << "|" << timeTaken;
    }
    file.close();
}

void AlgoOpti::findLeastsConsecutivesScalesChanges()
{
    clock_t tStart = clock();

    calculatePCCs("binary");
    results.clear();
    vector<Scale*> vide;
    generateSolutions(GAKO.back().back(),vide);

    double timeTaken = (double)(clock() - tStart)/CLOCKS_PER_SEC;
    QFile file("../stats/scaleStats.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << ";3|" << data.size() << "|" << timeTaken;
    }
    file.close();
}

vector<Scale*> reverse(vector<Scale*> v)
{
    vector<Scale*> res;
    for (size_t i = 0; i < v.size(); i++)
        res.push_back(v[v.size()-1-i]);

    return res;
}

void AlgoOpti::generateSolutions(Node * currentNode, vector<Scale*> solution)
{
    if (results.size() > limit)
        return;

    if (currentNode->predecessors.empty())
    {
        solution = reverse(solution);
        solution.pop_back();
        results.push_back(solution);
    }
    else
    {

        // cout << "Pushed scale = " << ((currentNode->g != NULL) ? currentNode->g->getName().toStdString() : "NULL") << endl << flush;
        solution.push_back(currentNode->g);

        for (size_t i = 0; i < currentNode->predecessors.size(); i++)
            generateSolutions(currentNode->predecessors[i], solution);
    }
}

void AlgoOpti::setLimit(int l)
{
    limit = l;
}

void AlgoOpti::calculatePCCs(string ponderation)
{
    clock_t tStart = clock();

    // indice de la k-partie contenant les voisins d'un sommet
    int neighbours;

    // Double boucle pour respecter l'ordre topologique
    for(size_t i = 0; i < GAKO.size(); i++) {

        for(size_t j = 0; j < GAKO[i].size(); j++) {

            // Boucle sur les voisins de GAKO[i][j]
            neighbours = GAKO[i][j]->index;
            if (neighbours >= 0)
                for(size_t k = 0; k < GAKO[neighbours].size(); k++){
                    relaxList(GAKO[i][j], GAKO[neighbours][k], ponderation);
                }
        }
    }

    cout << "Time taken for " << setiosflags(ios::fixed) << setprecision(4) << (double)(clock() - tStart)/CLOCKS_PER_SEC << " secs."
            << endl << flush;
}

vector<vector<Node*> > AlgoOpti::KpartitesToGAKO(vector<vector<Scale*> > Kpartite)
{

    vector<vector<Node*> > Graph;
    vector<Node*> nodeList;
    vector<Node*> predecessors; // liste des prédecesseurs toujours vide

    for (size_t i = 0; i < Kpartite.size(); i++){
        nodeList.clear();

        // index des voisins est i + 2 car on ajoute le sommet d'entree apres
        // ce qui entraine un decalage des indices par rapport a la structure KPartite
        for (size_t j = 0; j < Kpartite[i].size(); j++)
            nodeList.push_back(new Node(i + 2, INT_MAX, predecessors, Kpartite[i][j]));

        Graph.push_back(nodeList);
    }

    //node entrée
    vector<Node*> entree;
    entree.push_back(new Node(1, 0, predecessors, NULL));
    Graph.insert(Graph.begin(), entree);

    //node sortie
    vector<Node*> sortie;
    sortie.push_back(new Node(-1, INT_MAX, predecessors, NULL));
    Graph.push_back(sortie);

    return Graph;
}

int AlgoOpti::ponderation(Node* u, Node* v, string type)
{

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
        v->predecessors = newPreds;
    }
}

void AlgoOpti::relaxList(Node* u,Node* v,string ponderationType)
{
    if(v->distanceRoot > u->distanceRoot + ponderation(u, v, ponderationType)) {

        v->distanceRoot = u->distanceRoot + ponderation(u, v, ponderationType);

        vector<Node*> newPreds;
        newPreds.push_back(u);
        v->predecessors = newPreds;
    }
    else  if (v->distanceRoot == u->distanceRoot+ponderation(u,v,ponderationType))
        v->predecessors.push_back(u);
}
