#include "Network.h"


#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <queue>

template<class T>
void Network<T>::read_reservoirsFile(string reservoirFilename) {
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
            Vertex<T>* reservoirVertex = new Vertex<T>(Info(Reservoir,Municipality,ID,Code,Maximum_Delivery));
            this->vertexSet.push_back(reservoirVertex);
        }
        else {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
    file.close();
}

template<class T>
void Network<T>::read_citiesFile(string citiesFilename) {
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
            Vertex<T>* cityVertex = new Vertex<T>(Info(City,ID,Code,Demand,Population));
            this->vertexSet.push_back(cityVertex);

        }
        else {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
    file.close();
}

template<class T>
void Network<T>::read_stationsFile(string stationsFilename) {
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
                Vertex<T>* stationVertex = new Vertex<T>(Info(ID,Code));
                this->vertexSet.push_back(stationVertex);
            }

            }
        else {
            cerr << "Error parsing line: " << line << endl;
        }
    }

    file.close();
}

template<class T>
void Network<T>::read_pipesFile(string pipesFilename) {
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

template<class T>
Network<T>::~Network() {
    for (auto* v : vertexSet) {
        delete v;
    }
}

template<class T>
void Network<T>::build() {
    //calls all reads at once
    //Rever os paths para os ficheiros serem lidos corretamente.

    this->read_reservoirsFile("Dataset/Reservoirs_Madeira.csv");
    this->read_citiesFile("Dataset/Cities_Madeira.csv");
    this->read_stationsFile("Dataset/Stations_Madeira.csv");
    this->read_pipesFile("Dataset/Pipes_Madeira.csv");
}

template<class T>
Vertex<T> *Network<T>:: findVertex(const string &in) const {
    for (Vertex<T> * v : vertexSet){
        Info vertexInfo = v->getInfo();
        if (vertexInfo.getCode() == in)
            return v;
    }

    return nullptr;
}

template <class T>
bool Network<T>::addVertex(const T &in) {
    Info info = in;
    if (findVertex(info.getCode()) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

template <class T>
bool Network<T>::addEdge(const string &srcCode, const string &destCode, double w,bool isUniDirectional) {

    auto v1 = findVertex(srcCode);
    auto v2 = findVertex(destCode);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, isUniDirectional);
    return true;
}


// T2.2
template<class T>
unordered_map<string, double> Network<T>::verifyWaterSupply() {
    unordered_map<string, double> waterDeficits;

    for (Vertex<T>* cityVertex : vertexSet) {
        Info cityInfo = cityVertex->getInfo();

        if (cityInfo.getIsCity()) {
            double demand = cityInfo.getdemand();
            double totalCapacity = 0.0;

            for (Edge<T>* edge : cityVertex->getIncoming()) {
                totalCapacity += edge->getWeight();
            }

            if (totalCapacity < demand) {
                double deficit = demand - totalCapacity;
                waterDeficits[cityInfo.getCode()] = deficit;
            }
        }
    }

    return waterDeficits;
}




// T3.1

template<class T>
std::vector<std::string> Network<T>::removeReservoir(const std::string& reservoirCode) {
    Vertex<T>* reservoirVertex = findVertex(reservoirCode);
    if (reservoirVertex == nullptr) {
        std::cerr << "Reservoir with code " << reservoirCode << " not found!" << std::endl;
        return std::vector<std::string>();
    }

    std::vector<std::string> affectedDeliverySites;

    for (Vertex<T>* deliverySiteVertex : vertexSet) {
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


template<class T>
bool Network<T>::checkDeliveryCapacity(const T& info) const {
    Vertex<T>* currentVertex = findVertex(info.getCode());
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



// T3.2 - Lidar com a remoção de uma estação de bombeamento específica
template<class T>
void Network<T>::removePumpingStation(const string &stationCode) {
    auto it = vertexSet.begin();
    while (it != vertexSet.end()) {
        Vertex<T> *vertex = *it;
        Info vertexInfo = vertex->getInfo();
        if (vertexInfo.getCode() == stationCode && vertexInfo.getIsCity() == false) {
            vertex->removeOutgoingEdges();
            vertexSet.erase(it);
            delete vertex;
            return;
        }
        it++;
    }
    cerr << "Pumping station with code " << stationCode << " not found or is not a pumping station." << endl;
}

template<class T>
void Network<T>::checkImpactOfRemovingPumpingStation(const string &stationCode) {
    removePumpingStation(stationCode);

    vector<string> affectedCities;
    for (Vertex<T> *cityVertex : vertexSet) {
        Info cityInfo = cityVertex->getInfo();
        if (cityInfo.getIsCity()) {
            double citySupplyDeficit = 0.0;
            if (cityVertex->getAdj().empty()) {
                citySupplyDeficit = cityInfo.getdemand();
                affectedCities.push_back(cityInfo.getCode() + " - Deficit: " + to_string(citySupplyDeficit));
            }
        }
    }

    if (affectedCities.empty()) {
        cout << "Removing pumping station " << stationCode << " does not affect the delivery capacity to any city." << endl;
    } else {
        cout << "Removing pumping station " << stationCode << " affects the delivery capacity to some cities:" << endl;
        for (const string &city : affectedCities) {
            cout << city << endl;
        }
    }

    // adicionar código para recolocar a estação de bombeamento de volta à rede, se necessário

    cout << "Restoring pumping station " << stationCode << " to the network." << endl;
}

// T3.2 - Lidar com o impacto de todas as estações de bombeamento
template<class T>
void Network<T>::checkImpactOfAllPumpingStations() {
    vector<string> affectedCities;
    for (Vertex<T> *pumpingStationVertex : vertexSet) {
        Info stationInfo = pumpingStationVertex->getInfo();
        if (!stationInfo.getIsCity()) {
            string stationCode = stationInfo.getCode();
            removePumpingStation(stationCode);
            for (Vertex<T> *cityVertex : vertexSet) {
                Info cityInfo = cityVertex->getInfo();
                if (cityInfo.getIsCity() && cityVertex->getAdj().empty()) {
                    double citySupplyDeficit = cityInfo.getdemand();
                    affectedCities.push_back(cityInfo.getCode() + " - Deficit: " + to_string(citySupplyDeficit));
                }
            }
            addVertex(stationInfo);
        }
    }

    if (affectedCities.empty()) {
        cout << "Removing all pumping stations does not affect the delivery capacity to any city." << endl;
    } else {
        cout << "Removing all pumping stations affects the delivery capacity to some cities:" << endl;
        for (const string &city : affectedCities) {
            cout << city << endl;
        }
    }
}

template<class T>
unordered_map<string, Vertex<T>*> Network<T>::getVertices() const {
    unordered_map<string, Vertex<T>*> vertices;
    for (Vertex<T>* vertex : vertexSet) {
        Info info = vertex->getInfo();
        vertices[info.getCode()] = vertex;
    }
    return vertices;
}

template<class T>
unordered_map<string, double> Network<T>::pumpingStationImpact(const Info& pumpingStationInfo) const {
    unordered_map<string, double> impact;
    Vertex<T>* pumpingStationVertex = findVertex(pumpingStationInfo.getCode());
    if (pumpingStationVertex == nullptr) {
        cerr << "Pumping station not found!" << endl;
        return impact;
    }
    for (Edge<T>* edge : pumpingStationVertex->getIncoming()) {
        Vertex<T>* cityVertex = edge->getOrig();
        Info cityInfo = cityVertex->getInfo();
        double deficit = cityInfo.getdemand() - edge->getWeight();
        if (deficit > 0) {
            impact[cityInfo.getCode()] = deficit;
        }
    }
    return impact;
}

template<class T>
unordered_map<string, double> Network<T>::allPumpingStationsImpact() const {
    unordered_map<string, double> impact;
    for (Vertex<T>* vertex : vertexSet) {
        Info info = vertex->getInfo();
        if (!info.getIsCity()) {
            continue;
        }
        double totalSupply = 0;
        for (Edge<T>* edge : vertex->getIncoming()) {
            totalSupply += edge->getWeight();
        }
        if (totalSupply < info.getdemand()) {
            impact[info.getCode()] = info.getdemand() - totalSupply;
        }
    }
    return impact;
}
