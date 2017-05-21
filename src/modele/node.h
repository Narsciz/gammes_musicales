#ifndef NODE_H
#define NODE_H

//Bibliotheques c++
#include <iostream>
#include <vector>

//Classes
#include "modele/scale.h"

class Node
{
public:
    int index;
    int distanceRoot;
    std::vector<Node*> predecessors;
    Scale* g;

    Node(){}
    Node(int,int,std::vector<Node*>,Scale*);
    void display();
    Scale * getScale();
};

#endif // SOMMET_H
