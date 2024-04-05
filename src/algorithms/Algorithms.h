//
// Created by Utilizador on 05/04/2024.
//

#ifndef PROJETO1DA_ALGORITHMS_H
#define PROJETO1DA_ALGORITHMS_H
#include <queue>
#include "../graph/Network.h"

/*Edmonds karp*/

void edmondsKarp(Network<Info> *network, string sourceCode, string targetCode);
void augmentFlowAlongPath(Vertex<Info> *s, Vertex<Info> *t, double flow);
double findMinResidualAlongPath(Vertex<Info> *s, Vertex<Info> *t);
bool findAugmentingPath(Network<Info> *network, Vertex<Info> *s, Vertex<Info> *t);
void testAndVisit(std::queue< Vertex<Info>*> &q, Edge<Info> *e, Vertex<Info> *w, double residual);

/*----------------*/




#endif //PROJETO1DA_ALGORITHMS_H
