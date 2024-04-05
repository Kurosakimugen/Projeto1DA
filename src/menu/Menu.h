#ifndef PROJETO1DA_MENU_H
#define PROJETO1DA_MENU_H


#include "../graph/Network.h"

class Menu {
    void nextPage();
    void quit();

public:
    void run();

    void mainPage(Network<Info> network);

    void maxAmountWater(Network<Info> network);
    void maxAmountWater_AllCities(Network<Info> network);
    void maxAmountWater_OneCity(Network<Info> network, Vertex<Info>* CityVertex);

    void insertCityCode(Network<Info> network);



};


#endif //PROJETO1DA_MENU_H
