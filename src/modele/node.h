#ifndef NODE_H
#define NODE_H

#include <vector>
#include "scale.h"
#include <iostream>

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
