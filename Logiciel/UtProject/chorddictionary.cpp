#include "chorddictionary.h"

using namespace std;

ChordDictionary::ChordDictionary()
{

}

ChordDictionary* ChordDictionary::getInstance()
{
    if (INSTANCE==NULL)
        INSTANCE=new ChordDictionary;
    return INSTANCE;
}

bool ChordDictionary::contains(HSChord * c)
{
    for (int i=0;i<chords.size();i++)
        if (chords[i]==c)
            return true;
    return false;
}

ChordDictionary* ChordDictionary::INSTANCE = NULL;
