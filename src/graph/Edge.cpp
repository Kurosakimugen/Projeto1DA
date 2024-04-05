#include "Edge.h"


Edge::Edge(Vertex *orig, Vertex *dest, double weight, bool isUnidirectional): orig(orig), dest(dest), weight(weight), isUnidirectional(isUnidirectional) {}


Vertex * Edge::getDest() const {
    return this->dest;
}


double Edge::getWeight() const {
    return this->weight;
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