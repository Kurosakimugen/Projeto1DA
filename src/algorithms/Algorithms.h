#ifndef PROJETO1DA_ALGORITHMS_H
#define PROJETO1DA_ALGORITHMS_H
#include <queue>
#include "../graph/Network.h"

/*Edmonds karp*/

void edmondsKarp(Network *network, string sourceCode, string targetCode);
void augmentFlowOfPath(Vertex *sourceVertex, Vertex *targetVertex, double flow);
double findMinResidualAlongPath(Vertex *sourceVertex, Vertex *targetVertex);
bool findAugmentingPath(Network *network, Vertex *sourceVertex, Vertex *targetVertex);
void visitAndTest(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);






#endif //PROJETO1DA_ALGORITHMS_H
