#include "harmonicstructure.h"

using namespace std;

HarmonicStructure::HarmonicStructure(QString n,vector<int> i):name(n),intervals(i)
{

}
HarmonicStructure::HarmonicStructure(){}

vector<int> HarmonicStructure::getIntervals(){return intervals;}
QString HarmonicStructure::getName(){return name;}
