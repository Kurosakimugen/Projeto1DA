#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(Info in): info(in) {}
/**
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

Edge * Vertex::addEdge(Vertex *d, double w, bool isUnidirectional ) {
    auto newEdge = new Edge(this, d, w, isUnidirectional);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/**
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */

bool Vertex::removeEdge(string infoCode) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        Info destInfo = dest->getInfo();
        if (destInfo.getCode() == infoCode) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/**
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge*edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}


Info Vertex::getInfo() const {
    return this->info;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

//Parte do visited

bool Vertex::isVisited() const {
    return this->visited;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

//Parte do processing

bool Vertex::isProcessing() const {
    return this->processing;
}

void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

//Parte do indegree

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

//Parte do dist

double Vertex::getDist() const {
    return this->dist;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

//Parte do path
Edge *Vertex::getPath() const {
    return this->path;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}


std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setInfo(Info in) {
    this->info = in;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list

    auto it = dest->incoming.begin();

    while (it != dest->incoming.end()) {

        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;

}
