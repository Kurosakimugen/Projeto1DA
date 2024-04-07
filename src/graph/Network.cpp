#include "Network.h"

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

            //remove weird formatting & comma from PopulationString
            PopulationString = PopulationString.substr(1); // Remove the first character (leading double quote)
            if (PopulationString.back() == '"') { // Check if the last character is a double quote
                PopulationString.pop_back(); // Remove the last character (trailing double quote)
            }
            PopulationString.replace(PopulationString.find(","), 1, "");


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
            getline (iss, Code, ',') &&
            getline (iss, temp, ',')){


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

        addEdge(servicePointA,servicePointB,capacity, isUnidirectional);

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

    this->read_reservoirsFile("Dataset/Reservoirs_Madeira.csv");
    this->read_citiesFile("Dataset/Cities_Madeira.csv");
    this->read_stationsFile("Dataset/Stations_Madeira.csv");
    this->read_pipesFile("Dataset/Pipes_Madeira.csv");
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


bool Network::addEdge(const string &srcCode, const string &destCode, double w,bool isUniDirectional) {

    auto v1 = findVertex(srcCode);
    auto v2 = findVertex(destCode);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, isUniDirectional);
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
                double capacity = edge->getWeight();
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

vector<string> Network::removeReservoir(const string& reservoirCode) {
    Vertex* reservoirVertex = findVertex(reservoirCode);
    if (reservoirVertex == nullptr) {
        cerr << "Reservoir with code " << reservoirCode << " not found!" << endl;
        return vector<string>();
    }

    vector<string> affectedDeliverySites;

    for (Vertex* deliverySiteVertex : vertexSet) {
        if (deliverySiteVertex != reservoirVertex) {
            deliverySiteVertex->removeEdge(reservoirCode);

            if (!checkDeliveryCapacity(deliverySiteVertex->getInfo())) {
                affectedDeliverySites.push_back(deliverySiteVertex->getInfo().getCode());
            }

            addEdge(deliverySiteVertex->getInfo().getCode(), reservoirCode, 0.0, false);
        }
    }

    return affectedDeliverySites;
}



bool Network::checkDeliveryCapacity(Info info) const {
    Vertex* currentVertex = findVertex(info.getCode());
    if (currentVertex != nullptr) {
        if (currentVertex->getInfo().getIsWaterReservour()) {
            double capacity = currentVertex->getInfo().getCapacity();
            double demand = currentVertex->getInfo().getdemand();
            if (capacity >= demand) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}


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
                totalCapacity += edge->getWeight();
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
                totalCapacity += edge->getWeight();
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

    double newFlow = 0.0;

    for (Edge* edge : cityVertex->getIncoming()) {
        if (edge->getDest()->getInfo().getCode() != stationCode) {
            newFlow += edge->getWeight(); // Adicionar o peso da aresta ao novo fluxo
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
