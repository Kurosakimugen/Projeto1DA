#ifndef PROJETO1DA_MENU_H
#define PROJETO1DA_MENU_H


#include <queue>
#include "../graph/Network.h"

class Menu {
    void nextPage();
    void quit();

public:
    void run();

    void mainPage(Network<Info> network);
    void verifyWaterSupply(Network<Info> network);
    void maxAmountWater(Network<Info> network);
    void maxAmountWater_AllCities(Network<Info> network);
    void maxAmountWater_OneCity(Network<Info> network, Vertex<Info>* CityVertex);

    void insertCityCode(Network<Info> network);

    void reservoirImpact(Network<Info> network);
    void specificReservoirImpact(Network<Info> network);
    void allReservoirsImpact(Network<Info> network);

    void pumpingStationImpact(Network<Info> network);
    void notEssentialPumpingStation(Network<Info> network);
    void specificPumpingStationImpact(Network<Info> network);
    void allPumpingStationsImpact(Network<Info> network);


};


#endif //PROJETO1DA_MENU_H
