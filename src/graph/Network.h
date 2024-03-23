#ifndef PROJETO1DA_NETWORK_H
#define PROJETO1DA_NETWORK_H

#include <string>
#include <vector>
#include "Vertex.h"

using namespace std;

class Network {
private:
    vector<Vertex *> vertexSet; //pode ter de ser com template class, not sure

public:
    void read_reservoirsFile(string reservoirFilename);
    void read_citiesFile(string citiesFilename);
    void read_pipesFile(string pipesFilename);
    void read_stationsFile(string stationsFilename);
    void build();




};


#endif //PROJETO1DA_NETWORK_H
