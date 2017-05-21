#include "chord.h"

using namespace std;

/**
 * @brief Chord::Chord
 *  Constructeur d'accord
 * @param f2
 *  Fondamentale de l'accord
 * @param hs2
 *  Structure harmonique de l'accord
 */
Chord::Chord(Note f2, HarmonicStructure* hs2)
    : CS::CS(f2, hs2)
{
}

/**
 * @brief Chord::Chord
 *  Constructeur d'accord parametre par un QString sous la forme "fondamentale:nomHS"
 *  Cherche dans le dictionnaire l'existence de cet accord
 * @param name
 * @throws out_of_range_exception
 *  Lorsqu'un accord n'existe pas dans le dictionnaire.
 */
Chord::Chord(QString name)
{

    QStringList splittedName = name.split(':');

    if (splittedName.size() < 2)
        throw std::out_of_range("out of range");
    f = stringToNote(splittedName[0]);

    HarmonicStructure* hs2;
    if ((hs2 = ChordDictionary::getInstance()->getHSbyName(splittedName[1])) != NULL)
        hs = hs2;
    else {
        throw std::out_of_range("out of range");
    }
}

/**
 * @brief Chord::candidatesScales
 *  Trouve les gammes qui contiennent l'accord this
 * @return
 */
vector<Scale*> Chord::candidatesScales()
{
    vector<Scale*> res;
    vector<Scale*> searching_set = ScaleDictionary::getInstance()->getAllScales();

    for (size_t i = 0; i < searching_set.size(); i++)
        if (this->isContainedIn(searching_set[i]))
            res.push_back(searching_set[i]);

    return res;
}
