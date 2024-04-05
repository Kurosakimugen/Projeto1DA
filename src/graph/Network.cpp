#include "Network.h"


#include <fstream>
#include <sstream>
#include <iostream>

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


