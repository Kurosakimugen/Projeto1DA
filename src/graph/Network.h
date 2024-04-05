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
    //vector<Edge<T>*> edgeSet;
    //unordered_map<string, Vertex<T>*> vertexMap;

public:

    void read_reservoirsFile(string reservoirFilename);
    void read_citiesFile(string citiesFilename);
    void read_pipesFile(string pipesFilename);
    void read_stationsFile(string stationsFilename);
    void build();
    ~Network(); // para libertar memória

    Vertex<T> *findVertex(const string &in) const;
    bool addVertex(const T &in);
    bool addEdge(const string &srcCode, const string &destCode, double w, bool isUnidirectional);

    bool removeVertex(const T &in);
    std::unordered_map<std::string, double> verifyWaterSupply();


    void verifyWaterCapacity(const string &outputFilename) const;

    vector<string> removeReservoir(const string &reservoirCode);

    bool checkDeliveryCapacity(const T &info) const;

    void removePumpingStation(const string &stationCode);

    void checkImpactOfRemovingPumpingStation(const string &stationCode);

    void checkImpactOfAllPumpingStations();

    unordered_map<string, Vertex<T> *> getVertices() const;

    unordered_map<string, double> pumpingStationImpact(const Info &pumpingStationInfo) const;

    unordered_map<string, double> allPumpingStationsImpact() const;

};


#endif //PROJETO1DA_NETWORK_H
