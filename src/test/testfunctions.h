#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include "modele/algo.h"
#include "modele/algobrutomega.h"
#include "modele/algoopti.h"

void testAlgo(std::string,std::string,int limit=INT_MAX);
void testGAKO();
void displayGAKO(std::vector<std::vector<Node*> >);


#endif // TESTFUNCTIONS_H
