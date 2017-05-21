#include "node.h"

using namespace std;

/**
 * @brief Node::Node
 * @param i
 * @param d
 * @param preds
 * @param gg
 */
Node::Node(int i, int d, vector<Node*> preds, Scale* gg)
    : index(i)
    , distanceRoot(d)
    , predecessors(preds)
    , g(gg)
{
}

/**
 * @brief Node::display
 */
void Node::display()
{
    cout << g->getName().toStdString() << flush;
}

/**
 * @brief Node::getScale
 * @return
 */
Scale* Node::getScale()
{
    return g;
}
