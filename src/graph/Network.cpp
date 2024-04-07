#include "Network.h"
#include "../algorithms/Algorithms.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <map>

void Network::read_reservoirsFile(string reservoirFilename) {
    ifstream file(reservoirFilename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << reservoirFilename << endl;
        return;
    }

    string line;
    getline(file,line);

    while (getline(file,line)) {
        istringstream iss(line);
        string Reservoir,Municipality,IdString,Code,Maximum_Delivery_String;

        if (getline (iss, Reservoir, ',') &&
            getline (iss, Municipality, ',') &&
            getline (iss, IdString, ',') &&
            getline (iss, Code, ',') &&
            getline (iss, Maximum_Delivery_String, ',')) {

            double Maximum_Delivery = stod(Maximum_Delivery_String);

            int ID = stoi(IdString);



            //addVertex(Info(Reservoir,Municipality,ID,Code,Maximum_Delivery));
            Vertex* reservoirVertex = new Vertex(Info(Reservoir,Municipality,ID,Code,Maximum_Delivery));
            this->vertexSet.push_back(reservoirVertex);
        }
        else {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
    file.close();
}


void Network::read_citiesFile(string citiesFilename) {
    ifstream file(citiesFilename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << citiesFilename << endl;
        return;
    }

    string line;
    getline(file,line);
    while (getline(file,line)) {
        istringstream iss(line);
        string City,IdString,Code,DemandString,PopulationString;
        if (getline (iss, City, ',') &&
            getline (iss, IdString, ',') &&
            getline (iss, Code, ',') &&
            getline (iss, DemandString, ',') &&
            getline (iss, PopulationString)) {
            /*
            //remove weird formatting & comma from PopulationString
            PopulationString = PopulationString.substr(1); // Remove the first character (leading double quote)
            if (PopulationString.back() == '"') { // Check if the last character is a double quote
                PopulationString.pop_back(); // Remove the last character (trailing double quote)
            }
            PopulationString.replace(PopulationString.find(","), 1, "");
            */

            int Population = stoi(PopulationString);
            int ID = stoi(IdString);
            double Demand = stod(DemandString);


            //addVertex(Info(City,ID,Code,Demand,Population));
            Vertex* cityVertex = new Vertex(Info(City,ID,Code,Demand,Population));
            this->vertexSet.push_back(cityVertex);

        }
        else {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
    file.close();
}


void Network::read_stationsFile(string stationsFilename) {
    ifstream file(stationsFilename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << stationsFilename << endl;
        return;
    }

    string line;
    getline(file,line);
    while (getline(file,line)) {
        istringstream iss(line);
        string IdString, Code,temp;
        if (getline (iss, IdString, ',') &&
            getline (iss, Code, ',') /*&&
            getline (iss, temp, ',') */){


            if(IdString != ""){  //todo- ta aqui um if pq o documento csv acaba com ,,, probs o doc final n tem
                int ID = stoi(IdString);

                //addVertex(Info(ID,Code));
                Vertex* stationVertex = new Vertex(Info(ID,Code));
                this->vertexSet.push_back(stationVertex);
            }

        }
        else {
            cerr << "Error parsing line: " << line << endl;
        }
    }

    file.close();
}


void Network::read_pipesFile(string pipesFilename) {
    ifstream file(pipesFilename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << pipesFilename << endl;
        return;
    }

    string line;
    getline(file, line); // Ignora cabeçalho
    while (getline(file, line)) {
        istringstream iss(line);
        string servicePointA, servicePointB, capacityString, direction;
        if (!(getline(iss, servicePointA, ',') &&
              getline(iss, servicePointB, ',') &&
              getline(iss, capacityString, ',') &&
              getline(iss, direction, ','))) {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }

        double capacity = stod(capacityString);
        bool isUnidirectional = direction == "1";
        double flow = 0;

        addEdge(servicePointA,servicePointB,capacity, isUnidirectional,flow);

    }
    file.close();
}


Network::~Network() {
    for (auto* v : vertexSet) {
        delete v;
    }
}


void Network::build() {
    //calls all reads at once
    //Rever os paths para os ficheiros serem lidos corretamente.

    //this->read_reservoirsFile("Dataset/Reservoirs_Madeira.csv");
    //this->read_citiesFile("Dataset/Cities_Madeira.csv");
    //this->read_stationsFile("Dataset/Stations_Madeira.csv");
    //this->read_pipesFile("Dataset/Pipes_Madeira.csv");
    this->read_reservoirsFile("Dataset/Reservoir.csv");
    this->read_citiesFile("Dataset/Cities.csv");
    this->read_stationsFile("Dataset/Stations.csv");
    this->read_pipesFile("Dataset/Pipes.csv");
}


Vertex *Network:: findVertex(const string &in) const {

    for (Vertex * v : vertexSet){
        //Info vertexInfo = v->getInfo();
        if (v->getInfo().getCode() == in)
            return v;
    }

    return nullptr;
}

bool Network::addVertex(Info &in) {
    if (findVertex(in.getCode()) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in));
    return true;
}


bool Network::addEdge(const string &srcCode, const string &destCode, double w,bool isUniDirectional, double flow) {

    auto v1 = findVertex(srcCode);
    auto v2 = findVertex(destCode);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, isUniDirectional, flow);
    return true;
}


// T2.2
unordered_map<string, double> Network::verifyWaterSupply() {
    unordered_map<string, double> totalCapacities;
    unordered_map<string, double> waterDeficits;

    for (Vertex* reservoirVertex : vertexSet) {
        Info reservoirInfo = reservoirVertex->getInfo();
        if (reservoirInfo.getIsWaterReservour()) {
            for (Edge* edge : reservoirVertex->getAdj()) {
                Vertex* servicePoint = edge->getDest();
                double capacity = edge->getCapacity();
                totalCapacities[servicePoint->getInfo().getCode()] += capacity;
            }
        }
    }

    for (Vertex* cityVertex : vertexSet) {
        Info cityInfo = cityVertex->getInfo();
        if (cityInfo.getIsCity()) {
            double demand = cityInfo.getdemand();
            double totalCapacity = 0.0;

            for (Edge* edge : cityVertex->getIncoming()) {
                Vertex* reservoir = edge->getOrig();
                string reservoirCode = reservoir->getInfo().getCode();
                totalCapacity += totalCapacities[reservoirCode];
            }

            double actualFlow = min(demand, totalCapacity);

            double deficit = demand - actualFlow;

            if (deficit > 0) {
                waterDeficits[cityInfo.getCode()] = deficit;
            }
        }
    }

    return waterDeficits;
}





// T3.1




// T3.2

void Network::temporarilyRemoveStation(const string& stationCode) {
    Vertex* stationVertex = findVertex(stationCode);
    if (stationVertex == nullptr) {
        cerr << "Station with code " << stationCode << " not found!" << endl;
        return;
    }

    stationVertex->removeOutgoingEdges();
}

bool Network::checkDeliveryCapacityAfterRemoval(const string& stationCode) {
    temporarilyRemoveStation(stationCode);

    for (Vertex* cityVertex : vertexSet) {
        if (cityVertex->getInfo().getIsCity()) {
            double demand = cityVertex->getInfo().getdemand();
            double totalCapacity = 0.0;

            for (Edge* edge : cityVertex->getIncoming()) {
                totalCapacity += edge->getCapacity();
            }

            if (demand > totalCapacity) {
                restoreNetwork();
                return false;
            }
        }
    }

    restoreNetwork();
    return true;
}


map<string, double> Network::identifyMostAffectedCities(const string& stationCode) {
    map<string, double> affectedCities;

    temporarilyRemoveStation(stationCode);

    for (Vertex* cityVertex : vertexSet) {
        if (cityVertex->getInfo().getIsCity()) {
            double demand = cityVertex->getInfo().getdemand();
            double totalCapacity = 0.0;

            for (Edge* edge : cityVertex->getIncoming()) {
                totalCapacity += edge->getCapacity();
            }

            double deficit = demand - totalCapacity;

            if (deficit > 0) {
                affectedCities[cityVertex->getInfo().getCode()] = deficit;
            }
        }
    }

    restoreNetwork();

    return affectedCities;
}

void Network::restoreNetwork() {
    build();
}

vector<string> Network::findNotEssentialPumpingStations() {
    vector<string> notEssentialStations;

    for (Vertex* vertex : vertexSet) {
        Info info = vertex->getInfo();
        if (info.getIsPumpingStation() && !info.getIsEssential()) {
            notEssentialStations.push_back(info.getCode());
        }
    }

    return notEssentialStations;
}

double Network::calculateFlowAfterStationRemoval(const string& stationCode, const string& cityCode) {
    Vertex* cityVertex = findVertex(cityCode);

    if (cityVertex == nullptr) {
        cerr << "City with code " << cityCode << " not found!" << endl;
        return 0.0;
    }

    edmondsKarp(this, "MSrc", "MSink");

    double newFlow = 0.0;

    for (Edge* edge : cityVertex->getIncoming()) {
        if (edge->getDest()->getInfo().getCode() != stationCode) {
            newFlow += (edge->getCapacity() - edge->getFlow());
        }
    }

    return newFlow;
}




vector<Vertex *> Network::getVertexSet() {
    return this->vertexSet;
}


double Network::calculateWaterDeficit(const string& cityCode, double oldFlow, double newFlow) {
    Vertex* cityVertex = findVertex(cityCode);

    if (cityVertex == nullptr) {
        cerr << "City with code " << cityCode << " not found!" << endl;
        return 0.0;
    }

    double demand = cityVertex->getInfo().getdemand();

    double waterDeficit = demand - newFlow;

    return waterDeficit;
}

// T3.3 Lidar com impacto de remoção de pipelines a nivel geral ou especifico para uma cidade

unordered_map<string, string> Network::eachPipelineImpact() {
    unordered_map<string, string> impact;
    auto vertexs = vertexSet;

    // Cria uma lista com os flows originais
    unordered_map<string, double> originalFlows;
    for (Vertex* cityVertex : vertexs) {
        if (cityVertex->getInfo().getIsCity()) {
            originalFlows[cityVertex->getInfo().getCode()] = calculateCityMaxFlow(cityVertex);
        }
    }

    for (Vertex* vertex : vertexs) {
        for (Edge* edge : vertex->getAdj()) {
            double originalWeight = edge->getCapacity();


            // Compara o impacto do flow
            for (const auto& [cityCode, originalFlow] : originalFlows) {
                Vertex* cityVertex = findVertex(cityCode);
                double newFlow = calculateCityMaxFlow(cityVertex);
                double flowDifference = originalFlow - newFlow;

                string origId = edge->getOrig()->getInfo().getCode();
                string destId = edge->getDest()->getInfo().getCode();
                string pipeId = origId + "->" + destId;

                if (flowDifference != 0) {
                    if (impact.find(pipeId) == impact.end()) {
                        impact[pipeId] = pipeId + " affects: " + cityVertex->getInfo().getName() + " by going from " + to_string(originalFlow) + " to " + to_string(newFlow) + " resulting in a difference of " + to_string(flowDifference);
                    } else {
                        impact[pipeId] += " | " + cityVertex->getInfo().getName() + " by going from " + to_string(originalFlow) + " to " + to_string(newFlow) + " resulting in a difference of " + to_string(flowDifference);
                    }
                }
            }

            edge->setCapacity(originalWeight);
        }
    }

    return impact;
}


unordered_map<string, string> Network::CityPipelineImpact(Vertex* cityVertex) {
    unordered_map<string, string> impact;
    double originalFlow = calculateCityMaxFlow(cityVertex);

    for (Vertex* vertex : vertexSet) {
        for (Edge* edge : vertex->getAdj()) {
            double originalWeight = edge->getCapacity();
            edge->setCapacity(0.0);

            double newFlow = calculateCityMaxFlow(cityVertex);
            double flowDifference = originalFlow - newFlow;

            string origId = edge->getOrig()->getInfo().getCode();
            string destId = edge->getDest()->getInfo().getCode();
            string pipeId = origId + "->" + destId;

            if (flowDifference != 0) {
                string impactDescription = pipeId + " affects: " + cityVertex->getInfo().getName() + " by going from " + to_string(originalFlow) + " to " + to_string(newFlow) + " resulting in a difference of " + to_string(flowDifference);
                impact[pipeId] = impactDescription;
            }

            edge->setCapacity(originalWeight);
        }
    }

    return impact;
}

void Network::createMasterSource() {
    string masterSourceCode = "MSrc";

    Info info = Info();
    info.setName("Main Source");
    info.setCode("MSrc");


    this->addVertex(info);

    for (auto v: this->vertexSet) {
        if (v->getInfo().getIsWaterReservour()) {
            string wrCode = v->getInfo().getCode();

            double maxDelivery = v->getInfo().getMaximumDelivery();

            double flow = maxDelivery;

            this->addEdge(masterSourceCode, wrCode, maxDelivery, true, flow);
        }
    }

}

void Network::createMasterSink() {
    string masterSinkCode = "MSink";

    Info info = Info();
    info.setName("Main Sink");
    info.setCode("MSink");

    this->addVertex(info);

    for(auto v : this->vertexSet) {
        if(v->getInfo().getIsCity()){
            string dsCode =v->getInfo().getCode();

            double demand = v->getInfo().getdemand();

            double flow = 0;

            this->addEdge(dsCode, masterSinkCode, demand, true, flow);
        }
    }

}

bool Network::removeVertex(string infoCode) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo().getCode() == infoCode) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo().getCode());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

void Network::resetEdmondsKarp() {
    removeVertex("MSrc");
    removeVertex("MSink");

    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
}

void Network::runEdmondsKarp() {
    createMasterSource();
    createMasterSink();

    edmondsKarp(this,"MSrc", "MSink");

}

double Network::calculateCityMaxFlow(Vertex *cityVertex) {
    runEdmondsKarp();
    double flow = 0;

    for(auto e : cityVertex->getIncoming()){
        flow += e->getFlow();
    }

    resetEdmondsKarp();

    return flow;
}

unordered_map<string, Vertex*> Network::getVertices() const {
    unordered_map<string, Vertex*> vertices;
    for (Vertex* vertex : vertexSet) {
        Info info = vertex->getInfo();
        vertices[info.getCode()] = vertex;
    }
    return vertices;
}