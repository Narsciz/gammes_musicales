#include "algo.h"

using namespace std;

vector<vector<Scale*> > KpartitesScales(vector<Chord*> SA)
{
    vector<vector<Scale*> > Kpartite;
    for (int i=0;i<SA.size();i++)
        Kpartite.push_back(SA[i]->candidatesScales());
    return Kpartite;
}

std::vector<std::vector<Node*> >ScaleToGraph(std::vector<std::vector<Scale*> > Kpartite)
{
    /*
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


    Graph[0][0]=s;
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
    */

}

bool isNoteInNotes(Note n,vector<Note> s)
{

    for (int i=0;i<s.size();i++)
        if (s[i]==n)
            return true;
    return false;

}

bool isScaleInScales(Scale* scale,vector<Scale*> scales)
{
    for (int i=0;i<scales.size();i++)
        if (scales[i]->equals(scale))
            return true;
    return false;
}
