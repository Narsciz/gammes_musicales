#include "scaledictionary.h"

using namespace std;

/**
 * @brief ScaleDictionary::ScaleDictionary
 */
ScaleDictionary::ScaleDictionary()
{
}

/**
 * @brief ScaleDictionary::contains
 *  Verifie si une structure harmonique d'une gamme est contenue dans le dictionnaire
 * @param s
 * @return
 */
bool ScaleDictionary::contains(HSScale* s)
{
    for (size_t i = 0; i < scales.size(); i++)
        if (scales[i]->getIntervals() == s->getIntervals())
            return true;

    for (size_t i = 0; i < customScales.size(); i++)
        if (customScales[i]->getIntervals() == s->getIntervals())
            return true;

    return false;
}

/**
 * @brief ScaleDictionary::getScalesByTypes
 *  Renvoie toutes les gammes possibles avec les structures harmoniques que le dictionnaire possède
 * @param hsScales
 *  liste des structures harmoniques
 * @return
 */
vector<Scale*> ScaleDictionary::getScalesByTypes(QVector<QString> hsScales)
{
    vector<Scale*> res;
    for (size_t i = 0; i < hsScales.size(); i++)
        for (int j = 0; j < 12; j++)
            res.push_back(new Scale((Note)j, getHSbyName(hsScales[i])));
    return res;
}

/**
 * @brief ScaleDictionary::generateBaseScale
 *  Genere les gammes de bases existantes en musique
 */
void ScaleDictionary::generateBaseScale()
{
    /**/
    getInstance()->add(new HSScale("mh", { 2, 1, 2, 2, 1, 3 }, "Mineure harmonique"));
    getInstance()->add(new HSScale("mm", { 2, 1, 2, 2, 2, 2 }, "Mineure mélodique"));
    getInstance()->add(new HSScale("M", { 2, 2, 1, 2, 2, 2 }, "Majeure"));
    getInstance()->add(new HSScale("Pm", { 3, 2, 2, 3 }, "Pentatonique mineure"));
    getInstance()->add(new HSScale("Pb", { 3, 2, 1, 1, 3 }, "Pentatonique blues"));
    getInstance()->add(new HSScale("PM", { 2, 2, 3, 2 }, "Pentatonique majeure"));
    getInstance()->add(new HSScale("Egpt", { 2, 1, 3, 1, 1, 3 }, "Egyptienne"));
    getInstance()->add(new HSScale("Btk", { 2, 2, 2, 1, 2, 1 }, "Bartok"));
    getInstance()->add(new HSScale("Ton", { 2, 2, 2, 2, 2 }, "Par ton"));
    getInstance()->add(new HSScale("Dim", { 1, 2, 1, 2, 1, 2, 1 }, "Diminuee"));
}

/**
 * @brief ScaleDictionary::generateCustomScale
 *  Genere les gammes personnalisees cree par l'utilisateur
 */
void ScaleDictionary::generateCustomScale()
{

    customScales.clear();
    QString fileContent;
    QFile file("../assets/custom/customScales");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        fileContent = file.readAll();
        file.close();
    }

    QStringList customScalesSplit = fileContent.split(';');
    for (int i = 1; i < customScalesSplit.size(); i++) {
        QStringList currentCustomScale = customScalesSplit[i].split('|');
        QStringList currentCustomIntervals;

        if (currentCustomScale.size() == 3)
            currentCustomIntervals = currentCustomScale[1].split(',');
        else
            return;

        vector<int> intervals;
        for (int i = 0; i < currentCustomIntervals.size(); i++)
            intervals.push_back(currentCustomIntervals[i].toInt());

        addCustom(new HSScale(currentCustomScale[0], intervals, currentCustomScale[2]));
    }
    file.close();
}

/**
 * @brief ScaleDictionary::getHSbyName
 *  Trouve une structure harmonique du dictionnaire par le biais de son nom
 * @param s
 * @return
 */
HSScale* ScaleDictionary::getHSbyName(QString s)
{

    for (size_t i = 0; i < scales.size(); i++)
        if (scales[i]->getName() == s)
            return scales[i];
    for (size_t i = 0; i < customScales.size(); i++)
        if (customScales[i]->getName() == s)
            return customScales[i];

    return NULL;
}

/**
 * @brief ScaleDictionary::getHSnames
 *  Renvoie la liste des noms des structures harmoniques du dictionnaire pour la vue
 * @return
 */
QVector<QString> ScaleDictionary::getHSnames()
{
    QVector<QString> res;
    for (size_t i = 0; i < scales.size(); i++)
        res.push_back(scales[i]->getName());
    for (size_t i = 0; i < customScales.size(); i++)
        res.push_back(customScales[i]->getName());

    return res;
}

/**
 * @brief ScaleDictionary::getCustomHSnames
 *  Renvoie la liste des noms des structures harmoniques personnalisees du dictionnaire pour la vue
 * @return
 */
QVector<QString> ScaleDictionary::getCustomHSnames()
{
    QVector<QString> res;
    for (size_t i = 0; i < customScales.size(); i++)
        res.push_back(customScales[i]->getName());

    return res;
}

/**
 * @brief ScaleDictionary::getBaseHSnames
 *  Renvoie la liste des noms des structures harmoniques de base du dictionnaire pour la vue
 * @return
 */
QVector<QString> ScaleDictionary::getBaseHSnames()
{
    QVector<QString> res;
    for (size_t i = 0; i < scales.size(); i++)
        res.push_back(scales[i]->getName());

    return res;
}

/**
 * @brief ScaleDictionary::getHSalias
 *  Renvoie les alias des structures harmoniques contenu par le dictionnaire
 * @return
 */
QVector<QString> ScaleDictionary::getHSalias()
{
    QVector<QString> res;
    for (size_t i = 0; i < scales.size(); i++)
        res.push_back(scales[i]->getName());
    for (size_t i = 0; i < customScales.size(); i++)
        res.push_back(customScales[i]->getAlias());

    return res;
}

/**
 * @brief ScaleDictionary::getCustomHSalias
 *  Renvoie les alias des structures harmoniques personnalisees contenu par le dictionnaire
 * @return
 */
QVector<QString> ScaleDictionary::getCustomHSalias()
{
    QVector<QString> res;
    for (size_t i = 0; i < customScales.size(); i++)
        res.push_back(customScales[i]->getAlias());

    return res;
}

/**
 * @brief ScaleDictionary::getBaseHSalias
 *  Renvoie les alias des structures harmoniques de base contenu par le dictionnaire
 * @return
 */
QVector<QString> ScaleDictionary::getBaseHSalias()
{
    QVector<QString> res;
    for (size_t i = 0; i < scales.size(); i++)
        res.push_back(scales[i]->getAlias());

    return res;
}

/**
 * @brief ScaleDictionary::getInstance
 * @return
 */
ScaleDictionary* ScaleDictionary::getInstance()
{
    if (INSTANCE == NULL)
        INSTANCE = new ScaleDictionary;
    return INSTANCE;
}

/**
 * @brief ScaleDictionary::getAllScales
 *  Renvoie toutes les gammes (et non les structures harmoniques) que le dictionnaire peut generer
 * @return
 */
vector<Scale*> ScaleDictionary::getAllScales()
{
    vector<Scale*> res;
    for (size_t i = 0; i < scales.size(); i++)
        for (int j = 0; j < 12; j++)
            res.push_back(new Scale((Note)j, scales[i]));
    for (size_t i = 0; i < customScales.size(); i++)
        for (int j = 0; j < 12; j++)
            res.push_back(new Scale((Note)j, customScales[i]));
    return res;
}

/**
 * @brief ScaleDictionary::getBaseScales
 *  Renvoie toutes les gammes de base (et non les structures harmoniques) que le dictionnaire peut generer
 * @return
 */
std::vector<Scale*> ScaleDictionary::getBaseScales()
{
    vector<Scale*> res;
    for (size_t i = 0; i < scales.size(); i++)
        for (int j = 0; j < 12; j++)
            res.push_back(new Scale((Note)j, scales[i]));
    return res;
}

/**
 * @brief ScaleDictionary::getCustomScales
 *  Renvoie toutes les gammes personnalisees (et non les structures harmoniques) que le dictionnaire peut generer
 * @return
 */
std::vector<Scale*> ScaleDictionary::getCustomScales()
{
    vector<Scale*> res;
    for (size_t i = 0; i < customScales.size(); i++)
        for (int j = 0; j < 12; j++)
            res.push_back(new Scale((Note)j, customScales[i]));
    return res;
}

/**
 * @brief ScaleDictionary::add
 * @param h
 */
void ScaleDictionary::add(HSScale* h)
{
    if (!contains(h))
        scales.push_back(h);
}

/**
 * @brief ScaleDictionary::addCustom
 * @param h
 */
void ScaleDictionary::addCustom(HSScale* h)
{
    cout << "addcustom" << endl;
    if (!contains(h)) {
        QFile::remove("../assets/custom/customScales");
        customScales.push_back(h);
        fillCustomTextFile();
    }
}

/**
 * @brief ScaleDictionary::fillCustomTextFile
 *  Serialisation des gammes perso sous la forme :
 *  ;gammeNom|interval1,interval2,...|gammeAlias
 */
void ScaleDictionary::fillCustomTextFile()
{
    QFile file("../assets/custom/customScales");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        for (size_t i = 0; i < customScales.size(); i++) {
            QTextStream out(&file);
            out << ";" << customScales[i]->getName() << "|" << customScales[i]->getSerial() << "|" << customScales[i]->getAlias();
        }
    }
    file.close();
}

/**
 * @brief ScaleDictionary::removeCustom
 * @param h
 */
void ScaleDictionary::removeCustom(HSScale* h)
{
    for (size_t i = 0; i < customScales.size(); i++)
        if (customScales[i] == h) {
            customScales.erase(customScales.begin() + i);
            QFile::remove("../assets/custom/customScales");
            fillCustomTextFile();
        }
}

ScaleDictionary* ScaleDictionary::INSTANCE = NULL;
