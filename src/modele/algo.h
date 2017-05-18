#ifndef ALGO_H
#define ALGO_H

#include "chord.h"
#include "scale.h"
#include "note.h"
#include "node.h"
#include <iostream>
#include <vector>
#include <limits.h>

std::vector<std::vector<Scale*> > KpartitesScales(std::vector<Chord*> SA);
std::vector<std::vector<Node*> >ScaleToGraph(std::vector<std::vector<Scale*> > Kpartite);
bool isNoteInNotes(Note n,std::vector<Note> s);
bool isScaleInScales(Scale* scale,std::vector<Scale*> scales);

#endif // ALGO_H

