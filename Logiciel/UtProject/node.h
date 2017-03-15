#ifndef NODE_H
#define NODE_H

#include <vector>
#include "scale.h"


class Node
{
public:
    int index;
    int distanceRoot;
    std::vector<Node*> predecessors;
    Scale* g;

    Node();

};

#endif // SOMMET_H
