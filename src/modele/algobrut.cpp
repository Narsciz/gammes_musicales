#include "algobrut.h"

using namespace std;

AlgoBrut::AlgoBrut(vector<Chord*> SA, vector<Scale*> AS)
    : AbstractAlgo(SA, AS)
{
}

/**
 * @brief AlgoBrut::generateSolsRec
 *  Algorithme recursif qui calcule toutes les combinaisons possibles
 *  selon le graphe k-partie filtre (filteredKpartiteGraph) donnee
 *  et les stocke dans le vector possiblesSolutions
 * @param index
 *  Colonne du graphe k-partie
 * @param solutionPossible
 *  Liste stockante la construction de la combinaison courante
 */
void AlgoBrut::generateSolsRec(int index, vector<Scale*> solutionPossible)
{

    // Si le graphe k-parties filtre n'est pas vide
    if ((int)filteredKpartiteGraph.size() > 0) {

        // si on a parcouru tout le graphe en largeur, on a une combinaison
        if (index >= (int)filteredKpartiteGraph.size()) {
            possiblesSolutions.push_back(solutionPossible);
        }
        else {
            vector<Scale*> sol;

            //Pour chaque element (gamme) de la colonne index du graphe
            for (size_t i = 0; i < filteredKpartiteGraph[index].size(); i++) {
                sol = solutionPossible;
                sol.push_back(filteredKpartiteGraph[index][i]);
                generateSolsRec(index + 1, sol);

                /* plus performant mais plus moche
                // solutionPossible.push_back(filteredKpartiteGraph[index][i]);
                // generateSolsRec(index + 1, solutionPossible);
                // solutionPossible.pop_back();
                */
            }
        }
    }
}

/**
 * @brief AlgoBrut::generatePossiblesSolutions
 *  Lance l'algorithme recursif avec les parametres appropries.
 */
void AlgoBrut::generatePossiblesSolutions()
{
    possiblesSolutions.clear();
    vector<Scale*> vide;
    generateSolsRec(0, vide);
}

vector<vector<Scale*> > AlgoBrut::getSols()
{
    return possiblesSolutions;
}

/**
 * @brief AlgoBrut::findLeastsConsecutivesNotesChanges
 *  Contrainte de recherche des suites de gammes ayant le moins
 *  de changement de notes entre gammes consecutives.
 *  Les resultats sont stockes dans le vector results
 */
void AlgoBrut::findLeastsConsecutivesNotesChanges()
{

    clock_t tStart = clock();

    generatePossiblesSolutions();

    results.clear();

    // value stocke la valeur de chaque suite de gammes (on cherche la plus petite valeur)
    vector<int> values;
    int value;

    // on remplit le tableau values
    for (size_t i = 0; i < possiblesSolutions.size(); i++) {
        value = 0;

        // on fait la somme des differences symétriques de notes entre chaque couple de gammes consécutives
        for (size_t j = 0; j < possiblesSolutions[i].size() - 1; j++)
            value += possiblesSolutions[i][j]->notesDifferencesWithScale(possiblesSolutions[i][j + 1]);

        values.push_back(value);
    }

    //on cherche la plus petite valeur possible dans le tableau values
    int minValue = INT_MAX;
    for (size_t i = 0; i < values.size(); i++)
        minValue = min(values[i], minValue);

    // on ajoute dans le résultat retour toutes les occurences de la contrainte optimisée
    for (size_t i = 0; i < values.size(); i++) {

        // Si on a le compte de resultats a afficher
        if (results.size() >= resultsToDisplay)
            break;
        else if (values[i] == minValue)
            results.push_back(possiblesSolutions[i]);
    }

    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    /****** Remplissage du fichier texte qui servira aux statistiques des algoritmes ******/
    QFile file("../stats/noteStats.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << ";1|" << data.size() << "|" << timeTaken;
    }
    file.close();

    QFile pgfPlotsRecording("../assets/plots/algo_brut.dat");
    if (pgfPlotsRecording.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&pgfPlotsRecording);
        out << data.size() << " " << timeTaken << endl;
    }
    pgfPlotsRecording.close();
}

/**
 * @brief AlgoBrut::findLeastsConsecutivesScalesChanges
 *  Contrainte de recherche des suites de gammes ayant le moins
 *  de changement de gammes.
 *  Les resultats sont stockes dans le vector results
 */
void AlgoBrut::findLeastsConsecutivesScalesChanges()
{
    clock_t tStart = clock();

    generatePossiblesSolutions();
    results.clear();
    vector<int> values;
    int value;

    for (size_t i = 0; i < possiblesSolutions.size(); i++) {
        value = 0;
        for (size_t j = 0; j < possiblesSolutions[i].size() - 1; j++)
            if (!possiblesSolutions[i][j]->equals(possiblesSolutions[i][j + 1])) //compare les noms et non les notes (donc si y a des gammes avec les mêmes noms mais des notes différentes, ou l'inverse y a problème)
                value++;
        values.push_back(value);
    }

    int minValue = INT_MAX;
    for (size_t i = 0; i < values.size(); i++)
        minValue = min(minValue, values[i]);

    //vector<vector<Scale*> > res;
    for (size_t i = 0; i < values.size(); i++) {
        // Si on a le compte de resultats a afficher
        if (results.size() >= resultsToDisplay)
            break;
        else if (values[i] == minValue)
            results.push_back(possiblesSolutions[i]);
    }

    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    /****** Remplissage du fichier texte qui servira aux statistiques des algoritmes ******/
    QFile file("../stats/scaleStats.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << ";1|" << data.size() << "|" << timeTaken;
    }
    file.close();

    QFile pgfPlotsRecording("../assets/plots/algo_brut.dat");
    if (pgfPlotsRecording.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&pgfPlotsRecording);
        out << data.size() << " " << timeTaken << endl;
    }
    pgfPlotsRecording.close();
}

/**
 * @brief AlgoBrut::findLeastsTotalScales
 *  Contrainte de recherche des suites de gammes ayant le moins de gammes.
 *  Les resultats sont stockes dans le vector results
 */
void AlgoBrut::findLeastsTotalScales()
{
    clock_t tStart = clock();

    generatePossiblesSolutions();
    results.clear();
    vector<int> values;
    vector<Scale*> distinctsScales; //sert à stocker les différentes gammes de chaque suite de gammes

    for (size_t i = 0; i < possiblesSolutions.size(); i++) {

        for (size_t j = 0; j < possiblesSolutions[i].size(); j++)
            if (!isScaleInScales(possiblesSolutions[i][j], distinctsScales))
                distinctsScales.push_back(possiblesSolutions[i][j]);

        values.push_back(distinctsScales.size());
        distinctsScales.clear();
    }

    int minValue = INT_MAX;
    for (size_t i = 0; i < values.size(); i++)
        minValue = min(minValue, values[i]);

    //vector<vector<Scale*> > res;
    for (size_t i = 0; i < values.size(); i++) {
        // Si on a le compte de resultats a afficher
        if (results.size() >= resultsToDisplay)
            break;
        else if (values[i] == minValue)
            results.push_back(possiblesSolutions[i]);
    }

    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    /****** Remplissage du fichier texte qui servira aux statistiques des algoritmes ******/
    QFile file("../stats/totalScaleStats.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << ";1|" << data.size() << "|" << timeTaken;
    }
    file.close();

    QFile pgfPlotsRecording("../assets/plots/algo_brut.dat");
    if (pgfPlotsRecording.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&pgfPlotsRecording);
        out << data.size() << " " << timeTaken << endl;
    }
    pgfPlotsRecording.close();
}
