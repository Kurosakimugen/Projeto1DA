#include "Menu.h"


#include "../graph/Network.cpp"
#include <iostream>


using namespace std;

void Menu::nextPage() {
    for (int i = 0; i < 50; i++) {
        cout << '\n';
    }
}
void Menu::quit() {
    exit(0);
}

void Menu::run() {

    Network<Info> network;
    network.build();

    mainPage(network);
}

void Menu::mainPage (Network<Info> network) {
    cout << " _____________________________________________ \n"
            "|                    Main Menu                 |\n"
            "                                               \n"
            " > Calculate Max Amount of Water          [1]  \n"
            " > Unavailable                            [2]  \n"
            "                                               \n"
            " > Quit [q]                                    \n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);

    while(cmd != "q" && cmd!="1" && cmd!="2"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd=="q") quit();

    int operation = stoi(cmd);

    switch (operation) {
        case 1:
            nextPage();
            maxAmountWater(network);
            break;
        case 2:
            nextPage();
            //todo
            break;
    }

}

void Menu::maxAmountWater(Network<Info> network) {
    cout << " _____________________________________________ \n"
            "|       Calculate Max Amount of Water         |\n"
            "                                               \n"
            " > For each city                          [1]  \n"
            " > For a given city                       [2]  \n"
            "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);

    while(cmd != "q" && cmd!="0"  && cmd!="1" && cmd!="2"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd=="q") quit();

    int operation = stoi(cmd);

    switch (operation) {
        case 0:
            nextPage();
            mainPage(network);
            break;
        case 1:
            nextPage();
            maxAmountWater_AllCities(network);
            break;
        case 2:
            nextPage();
            insertCityCode(network);
            break;
    }

}

void Menu::maxAmountWater_AllCities(Network<Info> network) {
    //TODO-POR AQUI O RESULTADO DE NETWORK.EDMONDSKARP PARA TDS AS CITIES E DAR PRINT

    cout << " _____________________________________________ \n"
            "|       Calculate Max Amount of Water         |\n"
            "                                               \n"
            " nothing happens                               \n"
            "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);

    while(cmd != "q" && cmd!="0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd=="q") quit();

    int operation = stoi(cmd);

    if(operation == 0){
        nextPage();
        maxAmountWater(network);
    }
}

void Menu::maxAmountWater_OneCity(Network<Info> network, Vertex<Info>* cityVertex) {
    //TODO-POR AQUI O RESULTADO DE NETWORK.EDMONDSKARP PARA UMA CITY E DAR PRINT

    cout << " _____________________________________________ \n"
            "|       Calculate Max Amount of Water         |\n"
            "                                               \n"
            "  nothing  yet                                 \n"
            "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);

    while(cmd != "q" && cmd!="0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd=="q") quit();

    int operation = stoi(cmd);

    if(operation == 0){
        nextPage();
        maxAmountWater(network);
    }

}

void Menu::insertCityCode(Network<Info> network) {
    cout << " _____________________________________________ \n"
            "|               Insert City Code              |\n"
            "                                               \n"
            " > Type the desired city code                  \n"
            "                                               \n"
            "                 (e.g: C_1)                    \n"
            "                                               \n";

    string cmd;

    getline(cin, cmd);
    Vertex<Info>* cityVertex = network.findVertex(cmd);


    if(cityVertex == nullptr){
        cout<<"ERROR: City code not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            maxAmountWater(network);
        }

        if(cmd=="r"){
            nextPage();
            insertCityCode(network);
        }
    }

    Info cityVertexInfo = cityVertex->getInfo();
    if(!cityVertexInfo.getIsCity()){
        cout<<"ERROR: the given code does not depict a city\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            maxAmountWater(network);
        }

        if(cmd=="r"){
            nextPage();
            insertCityCode(network);
        }
    }

    maxAmountWater_OneCity(network, cityVertex);
}






