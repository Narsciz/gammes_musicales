#include "chorddictionary.h"
#include "chord.h"
using namespace std;

ChordDictionary::ChordDictionary()
{
}

/**
 * @brief ChordDictionary::getInstance
 * @return
 */
ChordDictionary* ChordDictionary::getInstance()
{
    if (INSTANCE == NULL)
        INSTANCE = new ChordDictionary;
    return INSTANCE;
}

/**
 * @brief ChordDictionary::contains
 *  Verifie si une structure harmonique d'un accord est contenue dans le dictionnaire
 * @param c
 * @return
 */
bool ChordDictionary::contains(HSChord* c)
{
    for (size_t i = 0; i < chords.size(); i++)
        if (chords[i]->getIntervals() == c->getIntervals())
            return true;
    for (size_t i = 0; i < customChords.size(); i++)
        if (customChords[i]->getIntervals() == c->getIntervals())
            return true;
    return false;
}

/**
 * @brief ChordDictionary::getSize
 * @return
 */
int ChordDictionary::getSize()
{
    return chords.size();
}

/**
 * @brief ChordDictionary::generateBaseChords
 *  Genere les accords de bases existant en musique
 */
void ChordDictionary::generateBaseChords()
{
    getInstance()->add(new HSChord("M", { 4, 3 }));
    getInstance()->add(new HSChord("+", { 4, 4 }));
    getInstance()->add(new HSChord("m", { 3, 4 }));
    getInstance()->add(new HSChord("2", { 2, 2, 3 }));
    getInstance()->add(new HSChord("m2", { 2, 1, 4 }));
    getInstance()->add(new HSChord("m4", { 3, 2, 2 }));
    getInstance()->add(new HSChord("dim", { 3, 3 }));
    getInstance()->add(new HSChord("sus", { 5, 2 }));
    getInstance()->add(new HSChord("4", { 4, 1, 2 }));
    getInstance()->add(new HSChord("m6", { 3, 4, 2 }));
    getInstance()->add(new HSChord("m(M7)", { 3, 4, 4 }));
    getInstance()->add(new HSChord("7sus", { 5, 2, 3 }));
    getInstance()->add(new HSChord("6", { 4, 3, 2 }));
    getInstance()->add(new HSChord("M7", { 4, 3, 4 }));
    getInstance()->add(new HSChord("m7", { 3, 4, 3 }));
    getInstance()->add(new HSChord("M7(#11)", { 4, 2, 5 }));
    getInstance()->add(new HSChord("M7(b5)", { 4, 2, 5 }));
    getInstance()->add(new HSChord("M7(#5)", { 4, 4, 3 }));
    getInstance()->add(new HSChord("m7(b5)", { 3, 3, 4 }));
    getInstance()->add(new HSChord("m7(b9)", { 1, 2, 4, 3 }));
    getInstance()->add(new HSChord("7", { 4, 3, 3 }));
    getInstance()->add(new HSChord("m(#5)", { 3, 5 }));
    getInstance()->add(new HSChord("dim7", { 3, 3, 3 }));
    getInstance()->add(new HSChord("7(b9)", { 1, 3, 3, 3 }));
    getInstance()->add(new HSChord("7(b5)", { 4, 2, 4 }));
    getInstance()->add(new HSChord("7(#5)", { 4, 4, 2 }));
    getInstance()->add(new HSChord("full", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }));
}

/**
 * @brief ChordDictionary::generateCustomChords
 * Genere les accords personnalises cree par l'utilisateur
 */
void ChordDictionary::generateCustomChords()
{

    customChords.clear();

    QString fileContent;
    QFile file("../assets/custom/customChords");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        fileContent = file.readAll();
        file.close();
    }

    QStringList customChordsSplit = fileContent.split(';');
    for (int i = 1; i < customChordsSplit.size(); i++) {
        QStringList currentCustomChord = customChordsSplit[i].split('|');
        QStringList currentCustomIntervals;

        if (currentCustomChord.size() == 2)
            currentCustomIntervals = currentCustomChord[1].split(',');
        else
            return;

        vector<int> intervals;
        for (int i = 0; i < currentCustomIntervals.size(); i++)
            intervals.push_back(currentCustomIntervals[i].toInt());

        addCustom(new HSChord(currentCustomChord[0], intervals));
    }
    file.close();
}

/**
 * @brief ChordDictionary::getHSnames
 *  Renvoie la liste des noms des structures harmoniques du dictionnaire pour la vue
 * @return
 */
QVector<QString> ChordDictionary::getHSnames()
{
    QVector<QString> res;
    for (size_t i = 0; i < chords.size(); i++)
        res.push_back(chords[i]->getName());
    for (size_t i = 0; i < customChords.size(); i++)
        res.push_back(customChords[i]->getName());
    return res;
}

/**
 * @brief ChordDictionary::getBaseHSnames
 *  Renvoie les noms des structures harmoniques de base du dictionnaire
 * @return
 */
QVector<QString> ChordDictionary::getBaseHSnames()
{
    QVector<QString> res;
    for (size_t i = 0; i < chords.size(); i++)
        res.push_back(chords[i]->getName());
    return res;
}

/**
 * @brief ChordDictionary::getCustomHSnames
 *  Renvoie les noms des structures harmoniques personnalisees du dictionnaire
 * @return
 */
QVector<QString> ChordDictionary::getCustomHSnames()
{
    QVector<QString> res;
    for (size_t i = 0; i < customChords.size(); i++)
        res.push_back(customChords[i]->getName());
    return res;
}

/**
 * @brief ChordDictionary::getHSbyName
 *  Trouve une structure harmonique du dictionnaire par le biais de son nom
 * @param s
 * @return
 */
HSChord* ChordDictionary::getHSbyName(QString s)
{
    //parcours les accords de base
    for (size_t i = 0; i < chords.size(); i++)
        if (chords[i]->getName() == s)
            return chords[i];

    //parcours les accords perso
    for (size_t i = 0; i < customChords.size(); i++)
        if (customChords[i]->getName() == s)
            return customChords[i];

    return NULL;
}

/**
 * @brief ChordDictionary::getChordByIndex
 * @param i
 * @return
 */
HSChord* ChordDictionary::getChordByIndex(int i)
{
    return chords[i];
}

/**
 * @brief ChordDictionary::getAllChords
 *  Renvoie tous les accords (et non les structures harmoniques) que le dictionnaire peut generer
 * @return
 */
vector<Chord*> ChordDictionary::getAllChords()
{
    vector<Chord*> res;
    for (size_t j = 0; j < chords.size(); j++)
        for (int i = 0; i < 12; i++)
            res.push_back(new Chord((Note)i, chords[j]));
    for (size_t j = 0; j < customChords.size(); j++)
        for (int i = 0; i < 12; i++)
            res.push_back(new Chord((Note)i, customChords[j]));
    return res;
}

/**
 * @brief ChordDictionary::getBaseChords
 * @return
 */
std::vector<Chord*> ChordDictionary::getBaseChords()
{
    vector<Chord*> res;
    for (size_t j = 0; j < chords.size(); j++)
        for (int i = 0; i < 12; i++)
            res.push_back(new Chord((Note)i, chords[j]));
    return res;
}

/**
 * @brief ChordDictionary::getCustomChords
 * @return
 */
std::vector<Chord*> ChordDictionary::getCustomChords()
{
    vector<Chord*> res;
    for (size_t j = 0; j < customChords.size(); j++)
        for (int i = 0; i < 12; i++)
            res.push_back(new Chord((Note)i, customChords[j]));
    return res;
}

/**
 * @brief ChordDictionary::add
 *  Ajoute une structure harmonique dans le dictionnaire
 * @param h
 */
void ChordDictionary::add(HSChord* h)
{
    if (!contains(h)) {
        chords.push_back(h);
    }
}

/**
 * @brief ChordDictionary::addCustom
 *  Ajoute une structure harmonique personnalisee dans le dictionnaire
 * @param h
 */
void ChordDictionary::addCustom(HSChord* h)
{
    if (!contains(h)) {
        customChords.push_back(h);
        QFile::remove("../assets/custom/customChords");
        fillCustomTextFile();
    }
}

/**
 * @brief ChordDictionary::fillCustomTextFile
 *  Serialisation des accords perso sous la forme :
 *  ;accordNom|interval1,interval2,...
 */
void ChordDictionary::fillCustomTextFile()
{
    QFile file("../assets/custom/customChords");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        for (size_t i = 0; i < customChords.size(); i++) {
            QTextStream out(&file);
            out << ";" << customChords[i]->getName() << "|" << customChords[i]->getSerial();
        }
    }
    file.close();
}

/**
 * @brief ChordDictionary::removeCustom
 * @param h
 */
void ChordDictionary::removeCustom(HSChord* h)
{
    for (size_t i = 0; i < customChords.size(); i++)
        if (customChords[i] == h) {
            QFile::remove("../assets/custom/customChords");
            customChords.erase(customChords.begin() + i);
            fillCustomTextFile();
        }
}

ChordDictionary* ChordDictionary::INSTANCE = NULL;
