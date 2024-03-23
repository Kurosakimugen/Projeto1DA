#ifndef PROJETO1DA_INFO_H
#define PROJETO1DA_INFO_H
#include <string>

using namespace std;

class Info {
private:
    string code;
    string name; //Name = City, Name = Reservoir ,Name = NULL
    string municipality;

    double population;

    int id;/*currently ignoring ID's, can be added later if necessary*/

    double maximumDelivery;
    double capacity;
    double demand;

    // the appropriate one is set to true when reading, the rest stays false
    bool isWaterReservour = false;
    bool isCity = false;
    bool isDeliverySite = false;

public:
    Info();
    Info(string name,string municipality,int id,string code, double maximumDelivery); //WR
    Info(string name,int id,string code,double demand, int population); //C
    Info(int id, string code); //DS

    void getCode();
    void setCode();

    void getName();
    void setName();

    void setCapacity();
    void getCapacity();

    void setPopulation();
    void getPopulation();
};


#endif //PROJETO1DA_INFO_H
