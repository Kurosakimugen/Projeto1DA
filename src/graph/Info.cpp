#include "Info.h"


Info::Info() {
    this->name = "";
    this->code = "";
    this->municipality = "";
    this->id = 0;
    this->population = 0;
    this->maximumDelivery = 0.0;
    this->capacity = 0.0;
    this->demand = 0.0;
}

Info::Info(string name, string municipality, int id, string code, double maximumDelivery) {
    this->isWaterReservour = true;
    this->name = name;
    this->code = code;
    this->municipality = municipality;
    this->id = id;
    this->maximumDelivery = maximumDelivery;

}

Info::Info(string name,int id, string code, double demand, int population) {
    this->isCity = true;
    this->name = name;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

Info::Info(int id, string code) {
    this->id = id;
    this->code = code;
}

double Info::getCapacity() {
    return capacity;
}

string Info::getCode() {
    return code;
}

string Info::getName() {
    return name;
}

double Info::getPopulation() {
    return population;
}

void Info::setCapacity(double nCapacity) {
    capacity = nCapacity;
}

void Info::setCode(std::string ncode) {
    code = ncode;
}

void Info::setName(std::string nName) {
    name = nName;
}

void Info::setPopulation(double nPopulation) {
    population = nPopulation;
}