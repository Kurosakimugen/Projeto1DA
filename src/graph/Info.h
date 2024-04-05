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
    double capacity;

    // the appropriate one is set to true when reading, the rest stays false
    bool isWaterReservour = false;
    bool isCity = false;
    bool isDeliverySite = false;

public:
    /**
     * @brief Construtor default
     */
    Info();
    /**
     * @brief Construtor utilizado para Water Resevoirs
     * @param name
     * @param municipality
     * @param id
     * @param code
     * @param maximumDelivery
     */
    Info(string name,string municipality,int id,string code, double maximumDelivery);
    /**
     * @brief Construtor para Cities
     * @param name
     * @param id
     * @param code
     * @param demand
     * @param population
     */
    Info(string name,int id,string code,double demand, int population);
    /**
     * @brief Construtor para Delivery Stations
     * @param id
     * @param code
     */
    Info(int id, string code); //DS

    /**
     * @brief Função de getter do code
     * @return Valor do code
     */
    string getCode() const;
    /**
     * @brief Função para dar set ao valor de code
     * @param ncode
     */
    void setCode(string ncode);

    /**
     * @brief Função de getter do Name
     * @return Valor do Name
     */
    string getName();
    /**
     * @brief Função para dar set ao valor do Name
     * @param nName
     */
    void setName(string nName);

    /**
     * @brief Função de getter do Capacity
     * @return Valor do Capacity
     */
    double getCapacity();
    /**
     * @brief Função para dar set ao valor de Capacity
     * @param nCapacity
     */
    void setCapacity(double nCapacity);

    /**
     * @brief Função de getter do Population
     * @return Valor do Population
     */
    double getPopulation();
    /**
     * @brief Função para dar set ao valor de Population
     * @param nPopulation
     */
    void setPopulation(double nPopulation);

    bool operator==(const Info& other) const;

    bool getIsCity();
    double demand;


    bool getIsWaterReservour() const;
};


#endif //PROJETO1DA_INFO_H
