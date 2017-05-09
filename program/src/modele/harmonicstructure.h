#ifndef HARMONICSTRUCTURE_H
#define HARMONICSTRUCTURE_H
#include <QString>
#include <vector>

using namespace std;


class HarmonicStructure
{
private:
    QString name;
    QString alias;
    std::vector<int> intervals;

public:
    HarmonicStructure();
    HarmonicStructure(QString,std::vector<int>,QString al="");

    std::vector<int> getIntervals();
    QString getName();
};

#endif // HARMONICSTRUCTURE_H
