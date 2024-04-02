#include "Edge.h"

template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, double w): orig(orig), dest(dest), weight(w) {}

template <class T>
Vertex<T> * Edge<T>::getDest() const {
    return this->dest;
}

template <class T>
double Edge<T>::getWeight() const {
    return this->weight;
}

template <class T>
Vertex<T> * Edge<T>::getOrig() const {
    return this->orig;
}

//Parte do Reverse
template <class T>
Edge<T> *Edge<T>::getReverse() const {
    return this->reverse;
}
template <class T>
void Edge<T>::setReverse(Edge<T> *reverse) {
    this->reverse = reverse;
}

//Parte do Selected
template <class T>
bool Edge<T>::isSelected() const {
    return this->selected;
}
template <class T>
void Edge<T>::setSelected(bool selected) {
    this->selected = selected;
}

//Parte do Flow
template <class T>
double Edge<T>::getFlow() const {
    return flow;
}
template <class T>
void Edge<T>::setFlow(double flow) {
    this->flow = flow;
}
