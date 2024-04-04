#ifndef EDGE_H
#define EDGE_H


#include "Info.h"

template <class T> class Vertex;
template <class T>
class Edge {
public:
    //Edge(Vertex<T> *orig, Vertex<T> *dest, double w);
    Edge(Vertex<T> *orig, Vertex<T> *dest, double weight, bool isDirected);


    Vertex<T> *getDest() const;
    double getWeight() const;
    Vertex<T> *getOrig() const;

    //Parte do Selected
    bool isSelected() const;
    void setSelected(bool selected);

    //Parte do Reverse
    Edge<T> *getReverse() const;
    void setReverse(Edge<T> *reverse);

    //Parte do Flow
    double getFlow() const;
    void setFlow(double flow);
protected:
    Vertex<T> *dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex<T> *orig;
    Edge<T> *reverse = nullptr;

    double flow; // for flow-related problems
    bool isDirected;
};

#endif // EDGE_H
