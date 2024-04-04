#include "Menu.h"

#include "../graph/Network.h"
#include "../graph/Network.cpp"

#include "../graph/Info.h"

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void Menu::nextPage() {
    for (int i = 0; i < 50; i++) {
        cout << '\n';
    }
}
void Menu::quit() {
    exit(0);
}

void Menu::parseCSVFiles(Network<Info> &network) {

    /*
     * read_reservoirsFile(network,"Dataset/Reservoirs_Madeira.csv");
    read_citiesFile("Dataset/Cities_Madeira.csv");
    read_stationsFile("Dataset/Stations_Madeira.csv");
    read_pipesFile("Dataset/Pipes_Madeira.csv");*/
}


void Menu::run() {

    Network<Info> network;

    network.build();

    mainPage();

}

void Menu::mainPage() {
    cout << " _____________________________________________ \n"
            "|                     TITLE                   |\n"
            "                                               \n"
            " > Placeholder                            [1]  \n"
            " > Placeholder                            [2]  \n"
            "                                               \n"
            "                                   > Quit [q]  \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd != "q" && cmd!="1" && cmd!="2"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    int operation = stoi(cmd);

    switch (operation) {
        case 1:
            nextPage();
            //todo
            break;
        case 2:
            nextPage();
            //todo
            break;
    }

}






