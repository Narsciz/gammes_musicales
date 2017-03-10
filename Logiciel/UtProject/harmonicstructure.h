#ifndef HARMONICSTRUCTURE_H
#define HARMONICSTRUCTURE_H

#include <QString>
#include <vector>

class HarmonicStructure
{
private:
    QString name;
    std::vector<int> intervals;
public:
    HarmonicStructure();
    HarmonicStructure(QString,std::vector<int>);
    std::vector<int> getIntervals();
    QString getName();
};

#endif // HARMONICSTRUCTURE_H
