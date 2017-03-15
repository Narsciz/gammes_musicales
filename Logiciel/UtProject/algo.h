#ifndef ALGO_H
#define ALGO_H

#include "chord.h"
#include "scale.h"
#include <vector>

using namespace std;

K-partitesScales(vector<Chord*> SA)
{
    vector<vector<Scale*> > Kpartite;
    for (int i=0;i<SA.size();i++)
        K-partite.push_back(SA[i].candidatesScales());
    return Kpartite;
}

std::vector<std::vector<Node*> >ScaleToGraph(std::vector<std::vector<Scale*> > Kpartite)
{
    vector<vector<Node*> > Graph;

    //génération de la taille graphe (tout est NULL normalement)
    Graph.resize(Kpartite.size()+2);
    for (int i=0;i<Kpartite.size();i++)
        Graph[i+1].resize(Kpartite[i]);
    Graph[0].resize(1);
    Graph.back().resize(1);

    Node* s=new Node();
    s->index=1;
    s->distanceRoot=0;


    Graph[0][0]=this;
    int i=0;
    int j;

    s=new Node();

    while (i<Kpartite.size())
    {
        j=0;
        while(j<Kpartite[i].size())
        {
            s->index++;
            s->distanceRoot=INFINITY;
            s->g=Kpartite[i][j];
            Graph[i][j]=s;
            j++;
            s=new Node();
        }
        i++;
    }

    s->index=-1;//-1 remplace NULL, la flemme de faire un pointeur de int
    s->distanceRoot=INFINITY;
    s->g=NULL;
    Graph[i][0]=s;

}

#endif // ALGO_H

