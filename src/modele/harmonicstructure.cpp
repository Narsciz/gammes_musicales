#include "harmonicstructure.h"

using namespace std;

HarmonicStructure::HarmonicStructure(QString n, vector<int> i, QString al) : name(n), alias(al), intervals(i) {
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

QString HarmonicStructure::getSerial()
{
    QString res="";
    for (size_t i=0;i<intervals.size();i++)
    {
        res += QString::number(intervals[i]);
        if (intervals.size()-1!=i)
            res+=",";
    }
    return res;

}
