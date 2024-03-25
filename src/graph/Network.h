#ifndef PROJETO1DA_NETWORK_H
#define PROJETO1DA_NETWORK_H

#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include <unordered_map>

using namespace std;

class Network {
private:
    vector<Vertex *> vertexSet; //pode ter de ser com template class, not sure
    vector<Edge*> edgeSet;
    unordered_map<string, Vertex*> vertexMap;


public:
    void read_reservoirsFile(string reservoirFilename);
    void read_citiesFile(string citiesFilename);
    void read_pipesFile(string pipesFilename);
    void read_stationsFile(string stationsFilename);
    void build();
    ~Network(); // para libertar memória


};


#endif //PROJETO1DA_NETWORK_H
