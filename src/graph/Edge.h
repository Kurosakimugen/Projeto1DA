#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Edge {
private:
    Vertex* source;
    Vertex* destiny;
    double capacity;
    bool isDirected;

public:
    Edge(Vertex* src, Vertex* dest, double cap, bool isDir) :
        source(src), destiny(dest), capacity(cap), isDirected(isDir) {}

};

#endif // EDGE_H
