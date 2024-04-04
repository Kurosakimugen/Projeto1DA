#ifndef PROJETO1DA_MENU_H
#define PROJETO1DA_MENU_H


#include "../graph/Network.h"

class Menu {
    void nextPage();
    void quit();

public:
    void run();
    void parseCSVFiles(Network<Info> &network);
    //void read_reservoirsFile(Network<Info> &network, string reservoirFilename);


    void mainPage();

};


#endif //PROJETO1DA_MENU_H
