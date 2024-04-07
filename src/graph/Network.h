#ifndef PROJETO1DA_NETWORK_H
#define PROJETO1DA_NETWORK_H

#include <string>
#include <vector>
#include "Edge.h"
#include <unordered_map>
#include <map>

using namespace std;

class Network {
private:
    vector<Vertex *> vertexSet;
    //vector<Vertex *> reserVoirSet;
    //vector<Vertex *> citySet;

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
    bool addEdge(const string &srcCode, const string &destCode, double w, bool isUnidirectional, double flow);

    /**
     * Function to delete an Vertex
     * @param in
     * @return true if sucessful or false otherwise
     */
    bool removeVertex(string infoCode);

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
    //bool checkDeliveryCapacity(Info info) const;

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

    /**
     * Function to get the reservoirs
     * @return list with all reservoirs
     */
    vector<Vertex *> getReservoirs() const;

    /**
     * Function to calculate the delivery capacity
     * @return list with values
     */
    vector<pair<std::string, std::pair<double, double>>> calculateDeliveryCapacity() const;

    /**
     * Function to calculate the delivery capacity
     * @param reservoirVertex
     * @return list with values
     */
    vector<pair<std::string, std::pair<double, double>>> calculateDeliveryCapacity(Vertex *reservoirVertex) const;

    /**
     * Function to get the vertex set
     * @return
     */
    vector<Vertex *> getVertexSet();

    /**
     * Function to calculate the flow after some station is removed
     * @param stationCode
     * @param cityCode
     * @return
     */
    double calculateFlowAfterStationRemoval(const string &stationCode, const string &cityCode);

    /**
     * Function to find which pumping stations are essencial
     * @return
     */
    vector<string> findNotEssentialPumpingStations();

    /**
     * Function to build the network
     */
    void restoreNetwork();

    /**
     * Function to identify which are the most affected cities by a certain station
     * @param stationCode
     * @return List with the results of the tes
     */
    std::map<string, double> identifyMostAffectedCities(const string &stationCode);

    /**
     * Function to check the delivery capacity after a removal of a station
     * @param stationCode
     * @return true if valid or false otherwise
     */
    bool checkDeliveryCapacityAfterRemoval(const string &stationCode);

    /**
     * Function to temporarily remove a station
     * @param stationCode
     */
    void temporarilyRemoveStation(const string &stationCode);

    /**
     * Function to calculate the water deficit of a certain city
     * @param cityCode
     * @param oldFlow
     * @param newFlow
     * @return the difference between the old value and the new value
     */
    double calculateWaterDeficit(const string &cityCode, double oldFlow, double newFlow);
    
    /**
     * Function to create the Master source
     */
    void createMasterSource();

    /**
     * Function to create the Master Sink
     */
    void createMasterSink();

    double calculateCityMaxFlow(Vertex* cityVertex);

    void runEdmondsKarp();
    void resetEdmondsKarp();

    /**
     * Function that calculates the impact of each pipeline removal of the graph
     * @return list with the results
     */
    unordered_map<string, string> eachPipelineImpact() ;

    /**
     * Function that checks which pipeline removal affects the city
     * @param cityver
     * @return list with the results
     */
    unordered_map<string, string> CityPipelineImpact(Vertex *cityver) ;
};


#endif //PROJETO1DA_NETWORK_H
