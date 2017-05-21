#include "hschord.h"

/**
 * @brief HSChord::HSChord
 */
HSChord::HSChord()
{
}

/**
 * @brief HSChord::HSChord
 * @param n2
 * @param i2
 * @param alias
 */
HSChord::HSChord(QString n2, std::vector<int> i2, QString alias)
    : HarmonicStructure::HarmonicStructure(n2, i2, alias)
{
}
