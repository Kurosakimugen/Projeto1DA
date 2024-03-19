#ifndef PROJETO1DA_INFO_H
#define PROJETO1DA_INFO_H
#include <string>

using namespace std;

class Info {
private:
    string Code;
    string Name; //Name = City, Name = Reservoir ,Name = NULL
    double Capacity; //Capacity = Demand, Capacity = Maximum_Delivery, Capacity = NULL
    int Population; //Population = NULL, Population = NULL

public:
    Info(string Code, string Name,double Capacity, int Population);

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
