#include "algoopti.h"

using namespace std;

/**
 * @brief AlgoOpti::AlgoOpti
 *  Constructeur
 * @param SA
 * @param AS
 */
AlgoOpti::AlgoOpti(std::vector<Chord*> SA, std::vector<Scale*> AS)
    : AbstractAlgo(SA, AS)
{
    // Si le filtrage a laisse un graphe non vide, on genere le GAKO
    // Sinon on laisse un GAKO vide (sans sommet entree et sortie)
    if (filteredKpartiteGraph.size() > 0)
        GAKO = KpartitesToGAKO(filteredKpartiteGraph);
}

/**
 * @brief AlgoOpti::findLeastsConsecutivesNotesChanges
 *  Contrainte de recherche des suites de gammes ayant le moins
 *  de changement de notes entre gammes consecutives.
 *  Les resultats sont stockes dans le vector results
 */
void AlgoOpti::findLeastsConsecutivesNotesChanges()
{
    clock_t tStart = clock();

    calculatePCCs("symetrical_difference");
    results.clear();

    vector<Scale*> vide;

    // Si le GAKO n'est pas vide (aucune solution)
    if (GAKO.size() > 0)
        generateSolutions(GAKO.back()[0], vide);

    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    QFile file("../stats/noteStats.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << ";3|" << data.size() << "|" << timeTaken;
    }

    file.close();

    QFile pgfPlotsRecording("../assets/plots/algo_opti.dat");
    if (pgfPlotsRecording.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&pgfPlotsRecording);
        out << data.size() << " " << timeTaken << endl;
    }
    pgfPlotsRecording.close();
}

/**
 * @brief AlgoOpti::findLeastsConsecutivesScalesChanges
 *  Contrainte de recherche des suites de gammes ayant le moins
 *  de gammes consecutives.
 *  Les resultats sont stockes dans le vector results
 */
void AlgoOpti::findLeastsConsecutivesScalesChanges()
{
    clock_t tStart = clock();

    calculatePCCs("binary");
    results.clear();

    vector<Scale*> vide;

    // Si le GAKO n'est pas vide (aucune solution)
    if (GAKO.size() > 0)
        generateSolutions(GAKO.back().back(), vide);

    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    QFile file("../stats/scaleStats.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << ";3|" << data.size() << "|" << timeTaken;
    }
    file.close();

    QFile pgfPlotsRecording("../assets/plots/algo_opti.dat");
    if (pgfPlotsRecording.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&pgfPlotsRecording);
        out << data.size() << " " << timeTaken << endl;
    }
    pgfPlotsRecording.close();
}

/**
 * @brief reverse
 *  Renvoi une liste a l'envers
 * @param v
 * @return
 */
vector<Scale*> reverse(vector<Scale*> v)
{
    vector<Scale*> res;
    for (size_t i = 0; i < v.size(); i++)
        res.push_back(v[v.size() - 1 - i]);

    return res;
}

/**
 * @brief AlgoOpti::generateSolutions
 *  generation recursive des suite de gammes solution
 *  une fois que les PCCs ont ete extraits du GAKO
 * @param currentNode
 * @param solution
 */
void AlgoOpti::generateSolutions(Node* currentNode, vector<Scale*> solution)
{
    if ((int)results.size() > resultsToDisplay)
        return;

    if (currentNode->predecessors.empty()) {
        solution = reverse(solution);
        solution.pop_back();
        results.push_back(solution);
    }
    else {
        solution.push_back(currentNode->g);

        for (size_t i = 0; i < currentNode->predecessors.size(); i++)
            generateSolutions(currentNode->predecessors[i], solution);
    }
}

/**
 * @brief AlgoOpti::calculatePCCs
 *  Calcul des plus courts chemins du GAKO
 * @param ponderation
 *  Type de ponderation
 */
void AlgoOpti::calculatePCCs(string ponderation)
{

    // indice de la k-partie contenant les voisins d'un sommet
    int neighbours;

    // Double boucle pour respecter l'ordre topologique
    for (size_t i = 0; i < GAKO.size(); i++) {

        for (size_t j = 0; j < GAKO[i].size(); j++) {

            // Boucle sur les voisins de GAKO[i][j]
            neighbours = GAKO[i][j]->index;
            if (neighbours >= 0)
                for (size_t k = 0; k < GAKO[neighbours].size(); k++) {
                    releaseList(GAKO[i][j], GAKO[neighbours][k], ponderation);
                }
        }
    }
}

/**
 * @brief AlgoOpti::KpartitesToGAKO
 *  Converti un graphe k-partie en structure representant le GAKO
 * @param Kpartite
 * @return
 */
vector<vector<Node*> > AlgoOpti::KpartitesToGAKO(vector<vector<Scale*> > Kpartite)
{

    vector<vector<Node*> > Graph;
    vector<Node*> nodeList;
    vector<Node*> predecessors; // liste des prédecesseurs toujours vide

    for (size_t i = 0; i < Kpartite.size(); i++) {
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

/**
 * @brief AlgoOpti::ponderation
 *  Calcul de la ponderation d'un arc selon le type de ponderation
 * @param u
 *  Noeud 1 de l'arc
 * @param v
 *  Noeud 2 de l'arc
 * @param type
 *  Type de la ponderation
 * @return int
 *  Valeur de la ponderation
 */
int AlgoOpti::ponderation(Node* u, Node* v, string type)
{

    // fonction de ponderation binaire
    if (type == "binary") {
        if (u->g != NULL && v->g != NULL)
            return (u->getScale()->equals(v->getScale())) ? 0 : 1;
        else
            return 0;
    }
    // fonction de ponderation basee sur la difference symetrique
    else if (type == "symetrical_difference") {
        if (u->g != NULL && v->g != NULL)
            return u->g->notesDifferencesWithScale(v->g);
        else
            return 0;
    }
    else
        return -1;
}

/**
 * @brief AlgoOpti::release
 *  Algorithme relacher, determine si un sommet u est un predecesseur de v
 *  dans le graphe des predecesseurs solution.
 * @param u
 * @param v
 * @param ponderationType
 */
void AlgoOpti::release(Node* u, Node* v, string ponderationType)
{
    if (v->distanceRoot > u->distanceRoot + ponderation(u, v, ponderationType)) {

        v->distanceRoot = u->distanceRoot + ponderation(u, v, ponderationType);

        vector<Node*> newPreds;
        newPreds.push_back(u);
        v->predecessors = newPreds;
    }
}

/**
 * @brief AlgoOpti::releaseList
 *  Algorithme release-list, determine si un sommet u est predecesseur de v
 *  dans le graphe des predecesseurs solutions.
 *  Stocke les solutions multiples.
 * @param u
 * @param v
 * @param ponderationType
 */
void AlgoOpti::releaseList(Node* u, Node* v, string ponderationType)
{
    if (v->distanceRoot > u->distanceRoot + ponderation(u, v, ponderationType)) {

        v->distanceRoot = u->distanceRoot + ponderation(u, v, ponderationType);

        vector<Node*> newPreds;
        newPreds.push_back(u);
        v->predecessors = newPreds;
    }
    else if (v->distanceRoot == u->distanceRoot + ponderation(u, v, ponderationType))
        v->predecessors.push_back(u);
}
