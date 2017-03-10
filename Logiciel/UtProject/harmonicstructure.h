#ifndef HARMONICSTRUCTURE_H
#define HARMONICSTRUCTURE_H
#include <QString>
#include <vector>


#include <QString>
#include <vector>

using namespace std;


class HarmonicStructure
{
private:
    QString name;

    std::vector<int> intervals;

    vector<int> harmonic;

public:
    HarmonicStructure();
    HarmonicStructure(QString,std::vector<int>);
    std::vector<int> getIntervals();
    QString getName();
};

#endif // HARMONICSTRUCTURE_H
