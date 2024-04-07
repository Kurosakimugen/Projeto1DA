#ifndef PROJETO1DA_NETWORK_H
#define PROJETO1DA_NETWORK_H

#include <string>
#include <vector>
#include "Edge.h"
#include <unordered_map>

using namespace std;

class Network {
private:
    vector<Vertex *> vertexSet;

public:

    /**
     * Function to read the reservoirs files
     * @param reservoirFilename
     */
    void read_reservoirsFile(string reservoirFilename);

    /**
     * Function to read the cities files
     * @param citiesFilename
     */
    void read_citiesFile(string citiesFilename);

    /**
     * Function to read the pipes files
     * @param pipesFilename
     */
    void read_pipesFile(string pipesFilename);

    /**
     * Function to read the Delivery Stations files
     * @param stationsFilename
     */
    void read_stationsFile(string stationsFilename);

    /**
     * Function to start the graph
     */
    void build();

    /**
     * Function to delete the graph
     */
    ~Network(); // para libertar memória

    /**
     * Function to search a certain vertex
     * @param in
     * @return vertex
     */
    Vertex *findVertex(const string &in) const;

    /**
     * Function to create a vertex
     * @param in
     * @return true if sucessful or false otherwise
     */
    bool addVertex(Info &in);

    /**
     * Function to add an Edge
     * @param srcCode
     * @param destCode
     * @param w
     * @param isUnidirectional
     * @return true if sucessful or false otherwise
     */
    bool addEdge(const string &srcCode, const string &destCode, double w, bool isUnidirectional);

    /**
     * Function to delete an Vertex
     * @param in
     * @return true if sucessful or false otherwise
     */
    bool removeVertex(Info &in);

    /**
     * Function to verify the water suplies
     * @return
     */
    unordered_map<string, double> verifyWaterSupply();

    /**
     * Function to verify the capacity of x
     * @param outputFilename
     */
    void verifyWaterCapacity(const string &outputFilename) const;

    /**
     * Function to remove a certain reservoir
     * @param reservoirCode
     * @return vector
     */
    vector<string> removeReservoir(const string &reservoirCode);

    /**
     * Function to check the capacity of some pipe
     * @param info
     * @return true if sucessful or false otherwise
     */
    bool checkDeliveryCapacity(Info info) const;

    /**
     * Function to remove a pumping station
     * @param stationCode
     */
    void removePumpingStation(const string &stationCode);

    /**
     * Function to check the impact of removing a pumping station
     * @param stationCode
     */
    void checkImpactOfRemovingPumpingStation(const string &stationCode);

    /**
     * Function to check the impact of removing all pumping stations
     */
    void checkImpactOfAllPumpingStations();

    /**
     * Function to get all nodes
     * @return list of nodes
     */
    unordered_map<string, Vertex *> getVertices() const;

    /**
     * Function to check the impact of some pumping station on the system
     * @param pumpingStationInfo
     * @return list of results
     */
    unordered_map<string, double> pumpingStationImpact(const Info &pumpingStationInfo) const;

    /**
     * Function to check the impact of each pumping station
     * @return list of pumping stations impact
     */
    unordered_map<string, double> allPumpingStationsImpact() const;

    double calculateActualFlow(Vertex *cityVertex);


    vector<Vertex *> getReservoirs() const;

    vector<pair<std::string, std::pair<double, double>>> calculateDeliveryCapacity() const;

    double calculateNewFlow(Vertex *cityVertex) const;

    vector<pair<std::string, std::pair<double, double>>> calculateDeliveryCapacity(Vertex *reservoirVertex) const;
};


#endif //PROJETO1DA_NETWORK_H
