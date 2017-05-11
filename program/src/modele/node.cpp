#include "node.h"

using namespace std;


Node::Node(int i, int d, vector<Node*> preds, Scale* gg) : index(i), distanceRoot(d), predecessors(preds), g(gg) {}

void Node::display()
{
    cout << g->getName().toStdString() << flush;
}

Scale* Node::getScale()
{
    return g;
}
