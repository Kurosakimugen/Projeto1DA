#include "Edge.h"

Vertex *Edge::getsource() {
    return source;
}

Vertex *Edge::getdestiny() {
    return destiny;
}

bool Edge::getDirected() {
    return isDirected;
}

double Edge::getcapacity() {
    return capacity;
}