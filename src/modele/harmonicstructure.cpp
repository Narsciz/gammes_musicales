#include "harmonicstructure.h"

using namespace std;

/**
 * @brief HarmonicStructure::HarmonicStructure
 * @param n
 * @param i
 * @param al
 */
HarmonicStructure::HarmonicStructure(QString n, vector<int> i, QString al)
    : name(n)
    , alias(al)
    , intervals(i)
{
}

/**
 * @brief HarmonicStructure::HarmonicStructure
 */
HarmonicStructure::HarmonicStructure() {}

/**
 * @brief HarmonicStructure::getIntervals
 * @return
 */
vector<int> HarmonicStructure::getIntervals()
{
    return intervals;
}

/**
 * @brief HarmonicStructure::getName
 * @return
 */
QString HarmonicStructure::getName()
{
    return name;
}

/**
 * @brief HarmonicStructure::getAlias
 * @return
 */
QString HarmonicStructure::getAlias()
{
    return alias;
}

/**
 * @brief HarmonicStructure::getSerial
 *  Renvoie la serialisation d'une structure harmonique
 *  pour les accords/gammes personnalisees qui doivent etre stocke sous la forme
 *  interval1,interval2...
 * @return
 */
QString HarmonicStructure::getSerial()
{
    QString res = "";
    for (size_t i = 0; i < intervals.size(); i++) {
        res += QString::number(intervals[i]);
        if (intervals.size() - 1 != i)
            res += ",";
    }
    return res;
}
