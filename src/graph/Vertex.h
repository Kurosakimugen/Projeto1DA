#ifndef PROJETO1DA_VERTEX_H
#define PROJETO1DA_VERTEX_H


#include <vector>
#include "Info.h"
#include "Edge.h"

template <class T> class Edge;
template <class T>
class Vertex {
public:
    Vertex(T inf);//not sure
    bool operator<(Vertex<T>& vertex) const; // // required by MutablePriorityQueue

    T getInfo() const;
    std::vector<Edge<T>*> getAdj() const;

    //Parte do visited
    bool isVisited() const;
    void setVisited(bool visited);

    //Parte do processing
    bool isProcessing() const;
    void setProcessing(bool processing);

    //parte do indegree
    unsigned int getIndegree() const;
    void setIndegree(unsigned int indegree);

    //parte do dist
    double getDist() const;
    void setDist(double dist);

    //parte do path
    Edge<T> *getPath() const;
    void setPath(Edge<T> *path);

    std::vector<Edge<T> *> getIncoming() const;
    void setInfo(T info);
    Edge<T> * addEdge(Vertex<T> *dest, double w);
    bool removeEdge(T in);
    void removeOutgoingEdges();

protected:
    T info;                // info node
    std::vector<Edge<T> *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;

    Edge<T> *path = nullptr;

    std::vector<Edge<T> *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge<T> *edge);
};
#endif //PROJETO1DA_VERTEX_H
