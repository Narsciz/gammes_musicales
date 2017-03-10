#ifndef HARMONICSTRUCTURE_H
#define HARMONICSTRUCTURE_H
#include <QString>
#include <vector>

<<<<<<< HEAD
#include <QString>
#include <vector>
=======
using namespace std;
>>>>>>> 0cce2723a3a292e66f7021eeb573cb7d77e02eb1

class HarmonicStructure
{
private:
    QString name;
<<<<<<< HEAD
    std::vector<int> intervals;
=======
    vector<int> harmonic;
>>>>>>> 0cce2723a3a292e66f7021eeb573cb7d77e02eb1
public:
    HarmonicStructure();
    HarmonicStructure(QString,std::vector<int>);
    std::vector<int> getIntervals();
    QString getName();
};

#endif // HARMONICSTRUCTURE_H
