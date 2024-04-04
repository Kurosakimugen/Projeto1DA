#ifndef PROJETO1DA_NETWORK_H
#define PROJETO1DA_NETWORK_H

#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "Info.h"
#include <unordered_map>

using namespace std;
template <class T>
class Network {
private:
    vector<Vertex<T> *> vertexSet;
    vector<Edge<T>*> edgeSet;
    unordered_map<string, Vertex<T>*> vertexMap;


public:

    void read_reservoirsFile(string reservoirFilename);
    void read_citiesFile(string citiesFilename);
    void read_pipesFile(string pipesFilename);
    void read_stationsFile(string stationsFilename);
    void build();
    ~Network(); // para libertar memória

    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);

    bool removeVertex(const T &in);


};


#endif //PROJETO1DA_NETWORK_H
