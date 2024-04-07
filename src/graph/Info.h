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

    int id; /*currently ignoring ID's, can be added later if necessary*/

    double maximumDelivery;
    double demand;

    // the appropriate one is set to true when reading, the rest stays false
    bool isWaterReservour = false;
    bool isCity = false;
    bool isDeliverySite = false;
    bool isPumpingStation;
    bool isEssential;

public:
    /**
     * @brief Default Constructor
     */
    Info();

    /**
     * @brief Water Resevoirs Constructor
     * @param name
     * @param municipality
     * @param id
     * @param code
     * @param maximumDelivery
     */
    Info(string name,string municipality,int id,string code, double maximumDelivery);

    /**
     * @brief City Constructor
     * @param name
     * @param id
     * @param code
     * @param demand
     * @param population
     */
    Info(string name,int id,string code,double demand, int population);

    /**
     * @brief Delivery Stations Constructor
     * @param id
     * @param code
     */
    Info(int id, string code); //DS

    /**
     * @brief Function to get the value of the Code
     * @return Code Value
     */
    string getCode() const;

    /**
     * @brief Function to change the value of Code
     * @param ncode
     */
    void setCode(string ncode);

    /**
     * @brief Function to get the value of Name
     * @return Name value
     */
    string getName();

    /**
     * @brief Function to change the value of Name
     * @param nName
     */
    void setName(string nName);

    /**
     * @brief Function to get the value of Population
     * @return Population value
     */
    double getPopulation();

    /**
     * @brief Function to change the value of Population
     * @param nPopulation
     */
    void setPopulation(double nPopulation);

    /**
     * @brief Function to get the value of Demand
     * @return Demand value
     */
    double getdemand();

    /**
     * @brief Function to change the value of Demand
     * @param ndemand
     */
    void setdemand(double ndemand);

    bool operator==(const Info& other) const;

    /**
     * @brief Function to verify if a node is a City or not
     * @return true if it is a city or false if isnt
     */
    bool getIsCity();

    /**
     * @brief Function to verify if a node is a Water Reservour or not
     * @return true if it is a Water Reservour or false if isnt
     */
    bool getIsWaterReservour() const;

    /**
    * Function to get if a node is a pumping station or not
    * @return true if yes or false otherwise
    */
    bool getIsPumpingStation() const;

    /**
    * Function to set if a node is pumpingstation or not
    * @param value
    */
    void setIsPumpingStation(bool value);

    /**
    * Function to know if a node is essential or not
    * @return yes if true or false otherwise
    */
    bool getIsEssential() const;

    /**
    * Function to set if a node is essential or not
    * @param value
    */
    void setIsEssential(bool value);

    /**
     * Function to check if is Delivery site or not
     * @return yes if true or false otherwise
     */
    bool getIsDeliverySite() const;

    /**
     * Function to get the maximum delivery
     * @return value of maximum delivery
     */
    double getMaximumDelivery() const;
};


#endif //PROJETO1DA_INFO_H
