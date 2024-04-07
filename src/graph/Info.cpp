#include "Info.h"


Info::Info() {
    this->name = "";
    this->code = "";
    this->municipality = "";
    this->id = 0;
    this->population = 0;
    this->maximumDelivery = 0.0;
    this->demand = 0.0;
}

Info::Info(string name, string municipality, int id, string code, double maximumDelivery) {
    this->isWaterReservour = true;
    this->name = name;
    this->code = code;
    this->municipality = municipality;
    this->id = id;
    this->maximumDelivery = maximumDelivery;

    //default
    this->population = 0;
    this->demand = 0.0;

}

Info::Info(string name,int id, string code, double demand, int population) {
    this->isCity = true;
    this->name = name;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;


    //default
    this->municipality = "";
    this->maximumDelivery = 0.0;

}

Info::Info(int id, string code) {
    this->id = id;
    this->code = code;

    //default
    this->name = "";
    this->municipality = "";
    this->population = 0;
    this->maximumDelivery = 0.0;

    this->demand = 0.0;
}

bool Info::operator==(const Info& other) const {
    return this->code == other.code;
    //return (this->code == other.code && this->name == other.name && this->municipality == other.municipality && this->municipality == other.municipality &&this->municipality == other.municipality &&this->municipality == other.municipality &&this->municipality == other.municipality && ) ;
}

/*
double Info::getCapacity() {
    return capacity;
}
*/
string Info::getCode() const{
    return code;
}

string Info::getName() {
    return name;
}

double Info::getPopulation() {
    return population;
}
/*
void Info::setCapacity(double nCapacity) {
    capacity = nCapacity;
}
*/
void Info::setCode(std::string ncode) {
    code = ncode;
}

void Info::setName(std::string nName) {
    name = nName;
}

void Info::setPopulation(double nPopulation) {
    population = nPopulation;
}

bool Info::getIsCity() {
    return isCity;
}

bool Info::getIsWaterReservour() const{
    return isWaterReservour;
}

void Info::setdemand(double ndemand) {
    demand = ndemand;
}

double Info::getdemand() {
    return demand;
}

/*
double Info::get
 () const{
    return flow;
}

void Info::setFlow(double nflow){
    flow = nflow;
}
 */

bool Info::getIsPumpingStation() const {
    return isPumpingStation;
}

void Info::setIsPumpingStation(bool value) {
    isPumpingStation = value;
}

bool Info::getIsEssential() const {
    return isEssential;
}

void Info::setIsEssential(bool value) {
    isEssential = value;
}

bool Info::getIsDeliverySite() const {
    return isDeliverySite;
}

double Info::getMaximumDelivery() const {
    return maximumDelivery;
}
