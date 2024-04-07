#include <stdexcept>
#include <xmath.h>
#include "Algorithms.h"

void visitAndTest(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual){
// if w isnt visited and there is residual capacity do:

    if (! w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }

}

void augmentFlowOfPath(Vertex *sourceVertex, Vertex *targetVertex, double flow){
    for (auto v = targetVertex; v != sourceVertex;) {
        auto e = v->getPath();
        double edgeflow = e->getFlow();

        if (e->getDest() == v) {
            e->setFlow(edgeflow + flow);
            v = e->getOrig();
        }
        else {
            e->setFlow(edgeflow - flow);
            v = e->getDest();
        }
    }

}

double findMinResidualAlongPath(Vertex *sourceVertex, Vertex *targetVertex){
    double f = INF;
//  find the minimum residual capacity (bottleneck value)
    for (auto v = targetVertex; v != sourceVertex; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getCapacity() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
// Return the minimum residual capacity
    return f;

}

bool findAugmentingPath(Network *network, Vertex *sourceVertex, Vertex *targetVertex){

    for(auto v : network->getVertexSet()) {
        v->setVisited(false);
    }

    sourceVertex->setVisited(true);
    std::queue<Vertex *> q;
    q.push(sourceVertex);

// find an augmenting path w/ BFS
    while( ! q.empty() && ! targetVertex->isVisited()) {
        auto v = q.front();
        q.pop();

        // outgoing edges
        for(auto e: v->getAdj()) {
            visitAndTest(q, e, e->getDest(), e->getCapacity() - e->getFlow());
        }

        // incoming edges
        for(auto e: v->getIncoming()) {
            visitAndTest(q, e, e->getOrig(), e->getFlow());
        }



    }
//if path to target is found returns true
    return targetVertex->isVisited();
}

void edmondsKarp(Network *network, string sourceCode, string targetCode){
    Vertex* sourceVertex = network->findVertex(sourceCode);
    Vertex* targetVertex = network->findVertex(targetCode);

/* validate source and target vertices*/
    if (sourceVertex == nullptr || targetVertex == nullptr || sourceVertex == targetVertex)
        throw std::logic_error("Invalid source and/or target vertex");

/* set flow on all edges to 0 */
    for (auto v : network->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
/* while there is an augmenting path, augment the flow along the path*/
    while( findAugmentingPath(network, sourceVertex, targetVertex) ) {
        double flow = findMinResidualAlongPath(sourceVertex, targetVertex);
        augmentFlowOfPath(sourceVertex, targetVertex, flow);
    }
/* Calculate and save incoming flow for each vertex*/

/*
    for (auto &v : network->getVertexSet()) {

        double incomingFlow = 0;
        for (auto e: v->getIncoming()) {
            incomingFlow += e->getFlow();
        }
        v->setFlow(incomingFlow);
    }
    */
}