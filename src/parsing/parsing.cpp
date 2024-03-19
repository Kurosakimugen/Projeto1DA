#include "parsing.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void read_reservoirs(string reservoir) {

    ifstream file(reservoir);

    if (!file.is_open()) {
        cerr << "Error opening file: " << reservoir << endl;
        return;
    }

    string line;
    getline(file,line);
    while (getline(file,line)) {
        istringstream iss(line);
        string Reservoir,MunicipalityId,Code,Maximum_Delivery;
        if (getline (iss, Reservoir, ',') &&
            getline (iss, MunicipalityId, ',') &&
            getline (iss, Code, ',') &&
            getline (iss, Maximum_Delivery, ',')) {
            //adicionar no grafo
        }
        else {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }

}
void read_cities(string cities) {
    ifstream file(cities);

    if (!file.is_open()) {
        cerr << "Error opening file: " << cities << endl;
        return;
    }

    string line;
    getline(file,line);
    while (getline(file,line)) {
        istringstream iss(line);
        string City,Id,Code,Demand,Population;
        if (getline (iss, City, ',') &&
            getline (iss, Id, ',') &&
            getline (iss, Code, ',') &&
            getline (iss, Population, ',')) {
            //adicionar no grafo
        }
        else {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
}

void read_pipes(string pipes){
    ifstream file(pipes);

    if (!file.is_open()) {
        cerr << "Error opening file: " << pipes << endl;
        return;
    }

    string line;
    getline(file,line);
    while (getline(file,line)) {
        istringstream iss(line);
        string ServicePointA, ServicePointB, Capacity, Direction;
        if (getline (iss, ServicePointA, ',') &&
            getline (iss, ServicePointB, ',') &&
            getline (iss, Capacity, ',') &&
            getline (iss, Direction, ','));
        else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
}

void read_stations(string stations) {
    ifstream file(stations);

    if (!file.is_open()) {
        cerr << "Error opening file: " << stations << endl;
        return;
    }

    string line;
    getline(file,line);
    while (getline(file,line)) {
        istringstream iss(line);
        string Id, Code;
        if (getline (iss, Id, ',') &&
            getline (iss, Code, ','));
        else {
            cerr << "Error parsing line: " << line << endl;
        }
    }

}