#ifndef PROJETO1DA_MENU_H
#define PROJETO1DA_MENU_H


#include <queue>
#include "../graph/Network.h"

class Menu {
    /**
     * Function to move to the next page
     */
    void nextPage();
    /**
     * Function to exit the menu
     */
    void quit();

public:
    /**
     * Function to start the menu
     */
    void run();

    /**
     * Function to start the network
     * @param network
     */
    void mainPage(Network network);

    /**
     * Function to start the verify the water suply
     * @param network
     */
    void verifyWaterSupply(Network& network);

    /**
     * Function to start the label of max water amount
     * @param network
     */
    void maxAmountWater(Network network);

    /**
     * Function to start the count of max water amount on all cities
     * @param network
     */
    void maxAmountWater_AllCities(Network network);

    /**
     * Function to start the count of max water amount of a specific city
     * @param network
     * @param CityVertex
     */
    void maxAmountWater_OneCity(Network network, Vertex* CityVertex);

    /**
     * Function to start a city node
     * @param network
     */
    void insertCityCode(Network network, int option);

    /**
     * Function to start the reservoir impact label
     * @param network
     */
    void reservoirImpact(Network network);

    /**
     * Function to start the impact of a certain reservoir
     * @param network
     */
    void specificReservoirImpact(Network network);

    /**
     * Function to start the impact of all reservoirs
     * @param network
     */
    void allReservoirsImpact(Network network);

    /**
     * Function to start the pumping stations impact label
     * @param network
     */
    void pumpingStationImpact(Network network);

    /**
     * Function to start the count of non essential pumping stations
     * @param network
     */
    void notEssentialPumpingStation(Network network);

    /**
     * Function to start the impact check of a certain pumping station
     * @param network
     */
    void specificPumpingStationImpact(Network network);

    /**
     * Function to start the impact check of all pumping stations
     * @param network
     */
    void allPumpingStationsImpact(Network network);

    /**
     * Function to start the label of pipeline failure
     * @param network
     */
    void pipelinefailureimpact(Network network);

    /**
     * Function that start the process for the all pipeline failure
     * @param network
     */
    void AllPipelineImpact(Network network);

    /**
     * Function that start the process for a city check pipeline failure
     * @param network
     */
    void CityPipelineImpact(Network network, Vertex* CityVertex);

    void determineCriticalStationsMenu(Network &network);
};


#endif //PROJETO1DA_MENU_H
