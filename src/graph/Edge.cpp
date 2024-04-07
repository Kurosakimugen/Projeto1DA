#include "Edge.h"


Edge::Edge(Vertex *orig, Vertex *dest, double capacity, bool isUnidirectional): orig(orig), dest(dest), capacity(capacity), isUnidirectional(isUnidirectional) {}

Edge::Edge(Vertex *orig, Vertex *dest, double capacity, bool isUnidirectional, double flow): orig(orig), dest(dest), capacity(capacity), isUnidirectional(isUnidirectional), flow(flow) {}

Vertex * Edge::getDest() const {
    return this->dest;
}


double Edge::getCapacity() const {
    return this->capacity;
}

void Edge::setCapacity(double nweight) {
   capacity = nweight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

//Parte do Reverse

Edge *Edge::getReverse() const {
    return this->reverse;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

//Parte do Selected

bool Edge::isSelected() const {
    return this->selected;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

//Parte do Flow

double Edge::getFlow() const {
    return flow;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

bool Edge::getIsUnidirectional() const {
    return isUnidirectional;
}

void Edge::setIsUnidirectional(bool value) {
    isUnidirectional = value;
}


