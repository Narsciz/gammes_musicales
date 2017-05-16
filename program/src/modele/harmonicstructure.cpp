#include "harmonicstructure.h"

using namespace std;

HarmonicStructure::HarmonicStructure(QString n, vector<int> i, QString al) : name(n), intervals(i), alias(al) {
}
HarmonicStructure::HarmonicStructure(){}

vector<int> HarmonicStructure::getIntervals() {
    return intervals;
}

QString HarmonicStructure::getName(){
    return name;
}

QString HarmonicStructure::getAlias() {
    return alias;
}
