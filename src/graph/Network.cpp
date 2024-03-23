#include "Network.h"
#include <fstream>
#include <sstream>
#include <iostream>


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

            //remove wierd formating & comma from PopulationString
            PopulationString = PopulationString.substr(1); // Remove the first character (leading double quote)
            if (PopulationString.back() == '"') { // Check if the last character is a double quote
                PopulationString.pop_back(); // Remove the last character (trailing double quote)
            }
            PopulationString.replace(PopulationString.find(","), 1, "");


            int Population = stoi(PopulationString);
            int ID = stoi(IdString);
            double Demand = stod(DemandString);

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
                Vertex* stationVertex = new Vertex(Info(ID,Code)); //TODO
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
    getline(file,line);
    while (getline(file,line)) {
        istringstream iss(line);
        string ServicePointA, ServicePointB, CapacityString, Direction;
        if (getline (iss, ServicePointA, ',') &&
            getline (iss, ServicePointB, ',') &&
            getline (iss, CapacityString, ',') &&
            getline (iss, Direction, ','));
        else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
    file.close();
}


void Network::build() {
    //calls all reads at once

    this->read_reservoirsFile("Dataset\\Reservoirs_Madeira.csv");
    this->read_citiesFile("Dataset\\Cities_Madeira.csv");
    this->read_stationsFile("Dataset\\Stations_Madeira.csv");
    //todo- pipes read file
}


