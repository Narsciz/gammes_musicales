#ifndef CS_H
#define CS_H
#include "note.h"
#include "harmonicstructure.h"

class CS
{
private:
    Note f;
    HarmonicStructure hs;
public:
<<<<<<< HEAD
    CS();

=======
    CS(Note f2, HarmonicStructure hs2);
    vector<Note> getNotes();

    Note getF();
    void setF(Note f2);
    HarmonicStructure getHS();
    void setHS(HarmonicStructure hs2);
>>>>>>> 0cce2723a3a292e66f7021eeb573cb7d77e02eb1
};

#endif // CS_H
