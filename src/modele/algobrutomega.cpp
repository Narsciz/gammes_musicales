#include "algobrutomega.h"

AlgoBrutOmega::AlgoBrutOmega(vector<Chord*> SA, vector<Scale*> AS)
    : AlgoBrut(SA, AS)
{
}

/**
 * @brief AlgoBrutOmega::generateSolsRec
 *  Algorithme optimise recursif qui calcule toutes les combinaisons possibles
 *  selon le graphe k-partie filtre (filteredKpartiteGraph) donnee
 *  et les stocke dans le vector possiblesSolutions
 * @param index
 *  Colonne du graphe k-partie
 * @param solutionPossible
 *  Combinaison courante
 * @param omega
 *  Valeur de la combinaison courante selon une contrainte
 * @param constraint
 *  Type de la contrainte
 */
void AlgoBrutOmega::generateSolsRec(int index, vector<Scale*> solutionPossible, int omega, int constraint)
{
    // si filteredKpartiteGraph n'est pas vide
    if (filteredKpartiteGraph.size() > 0) {

        if (index >= (int)filteredKpartiteGraph.size()) {
            minOmega = min(minOmega, omega);
            if (omega <= minOmega) {
                omegas.push_back(omega);

                possiblesSolutions.push_back(solutionPossible);
            }
        }
        else {
            for (size_t i = 0; i < filteredKpartiteGraph[index].size(); i++) {
                int value = 0;

                // LeastsConsecutivesNotesChanges
                if (constraint == 0) {
                    if (solutionPossible.size() == 0)
                        value = 0;
                    else
                        value = solutionPossible.back()->notesDifferencesWithScale(filteredKpartiteGraph[index][i]);
                }
                // LeastsConsecutivesScalesChanges
                else if (constraint == 1) {
                    if (solutionPossible.size() == 0)
                        value = 0;
                    else if (solutionPossible.back()->equals(filteredKpartiteGraph[index][i]))
                        value = 0;
                    else
                        value = 1;
                }
                //LeastsTotalScales
                else if (constraint == 2) {
                    if (solutionPossible.size() == 0)
                        value = 1;
                    else if (isScaleInScales(filteredKpartiteGraph[index][i], solutionPossible))
                        value = 0;
                    else
                        value = 1;
                }

                if ((omega + value) <= minOmega) {
                    vector<Scale*> sol = solutionPossible;
                    sol.push_back(filteredKpartiteGraph[index][i]);
                    generateSolsRec(index + 1, sol, omega + value, constraint);
                }

                /***plus performant mais plus moche***
            solutionPossible.push_back(filteredKpartiteGraph[index][i]);
            generateSolsRec(index+1,solutionPossible,omega+value);
            solutionPossible.pop_back();
            **************************************/
            }
        }
    }
}

/**
 * @brief AlgoBrutOmega::findLeastsConsecutivesNotesChanges
 *  Contrainte de recherche des suites de gammes ayant le moins
 *  de changement de notes entre gammes consecutives.
 *  Les resultats sont stockes dans le vector results
 */
void AlgoBrutOmega::findLeastsConsecutivesNotesChanges()
{

    clock_t tStart = clock();

    // Remise a zero des vector de solutions possibles et vraies solutions
    possiblesSolutions.clear();
    results.clear();

    vector<Scale*> vide;
    minOmega = INT_MAX;

    generateSolsRec(0, vide, 0, 0);
    filterPossiblesSolutions();

    minOmega = INT_MAX;
    for (size_t i = 0; i < resultsToDisplay; i++)
        results.push_back(possiblesSolutions[i]);

    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    /****** Remplissage du fichier texte qui servira aux statistiques des algoritmes ******/
    QFile file("../stats/noteStats.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << ";2|" << data.size() << "|" << timeTaken;
    }
    file.close();

    QFile pgfPlotsRecording("../assets/plots/algo_brut_omega.dat");
    if (pgfPlotsRecording.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&pgfPlotsRecording);
        out << data.size() << " " << timeTaken << endl;
    }
    pgfPlotsRecording.close();
}

/**
 * @brief AlgoBrutOmega::findLeastsConsecutivesScalesChanges
 *  Contrainte de recherche des suites de gammes ayant le moins
 *  de changement de gammes consecutives.
 *  Les resultats sont stockes dans le vector results
 */
void AlgoBrutOmega::findLeastsConsecutivesScalesChanges()
{

    clock_t tStart = clock();
    possiblesSolutions.clear();
    results.clear();

    vector<Scale*> vide;
    minOmega = INT_MAX;

    generateSolsRec(0, vide, 0, 1);
    filterPossiblesSolutions();

    minOmega = INT_MAX;
    for (size_t i = 0; i < resultsToDisplay; i++)
        results.push_back(possiblesSolutions[i]);

    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    /****** Remplissage du fichier texte qui servira aux statistiques des algoritmes ******/
    QFile file("../stats/scaleStats.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << ";2|" << data.size() << "|" << timeTaken;
    }
    file.close();

    QFile pgfPlotsRecording("../assets/plots/algo_brut_omega.dat");
    if (pgfPlotsRecording.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&pgfPlotsRecording);
        out << data.size() << " " << timeTaken << endl;
    }
    pgfPlotsRecording.close();
}

/**
 * @brief AlgoBrutOmega::findLeastsTotalScales
 *  Contrainte de recherche des suites de gammes ayant le moins de gammes
 *  Les resultats sont stockes dans le vector results
 */
void AlgoBrutOmega::findLeastsTotalScales()
{

    clock_t tStart = clock();
    possiblesSolutions.clear();
    results.clear();

    vector<Scale*> vide;
    minOmega = INT_MAX;

    generateSolsRec(0, vide, 0, 2);
    filterPossiblesSolutions();

    minOmega = INT_MAX;
    for (size_t i = 0; i < resultsToDisplay; i++)
        results.push_back(possiblesSolutions[i]);

    /****** Remplissage du fichier texte qui servira aux statistiques des algoritmes ******/
    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    QFile file("../stats/totalScaleStats.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << ";2|" << data.size() << "|" << timeTaken;
    }
    file.close();

    QFile pgfPlotsRecording("../assets/plots/algo_brut_omega.dat");
    if (pgfPlotsRecording.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&pgfPlotsRecording);
        out << data.size() << " " << timeTaken << endl;
    }
    pgfPlotsRecording.close();
}

/**
 * @brief AlgoBrutOmega::filterPossiblesSolutions
 *  Filtrage des suites de gammes solutions dont la valeur
 *  par rapport a une contrainte n'est pas minimale
 */
void AlgoBrutOmega::filterPossiblesSolutions()
{

    // Si il existe des suites de gammes solutions
    if (possiblesSolutions.size() > 0) {

        if ((int)possiblesSolutions.size() != (int)omegas.size())
            return;

        vector<vector<Scale*> > filteredPossiblesSolutions;
        for (size_t i = 0; i < omegas.size(); i++) {
            if (omegas[i] <= minOmega)
                filteredPossiblesSolutions.push_back(possiblesSolutions[i]);
        }

        possiblesSolutions = filteredPossiblesSolutions;
    }
}
