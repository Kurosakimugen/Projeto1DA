#include "Menu.h"
#include "../algorithms/Algorithms.h"
//#include "../graph/Network.cpp"
#include <iostream>
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

void Menu::run() {

    Network network;
    network.build();

    mainPage(network);
}


void Menu::mainPage(Network network) {
    cout << " _____________________________________________ \n"
            "|                 Main Menu                   |\n"
            "                                               \n"
            " > Calculate Max Amount of Water          [1]  \n"
            " > Verify Water Supply                    [2]  \n"
            " > Load Optimization                      [3]  \n"
            " > Reservoir Impact                       [4]  \n"
            " > Pumping Station Impact                 [5]  \n"
            " > Pipeline Failure Impact                [6]  \n"
            "                                               \n"
            " > Quit [q]                                    \n"
            " _____________________________________________ \n";


    string cmd;
    getline(cin, cmd);

    while (cmd != "q" && cmd != "1" && cmd != "2" && cmd != "3" && cmd != "4" && cmd != "5" && cmd != "6") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    int operation = stoi(cmd);

    switch (operation) {
        case 1:
            nextPage();
            maxAmountWater(network);
            break;
        case 2:
            nextPage();
            verifyWaterSupply(network);
            break;
        case 4:
            nextPage();
            reservoirImpact(network);
            break;
        case 5:
            nextPage();
            pumpingStationImpact(network);
            break;
        case 6:
            nextPage();
            //todo
            break;
    }
}

// T2.1
void Menu::maxAmountWater(Network network) {
    cout << " _____________________________________________ \n"
            "|       Calculate Max Amount of Water         |\n"
            "                                               \n"
            " > For each city                          [1]  \n"
            " > For a given city                       [2]  \n"
            "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

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

// T2.1
void Menu::maxAmountWater_AllCities(Network network) {
    //TODO-POR AQUI O RESULTADO DE NETWORK.EDMONDSKARP PARA TDS AS CITIES E DAR PRINT

    cout << " _____________________________________________ \n"
            "|       Calculate Max Amount of Water         |\n"
            "                                               \n"
            " nothing happens                               \n"
            "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

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

// T2.1
void Menu::maxAmountWater_OneCity(Network network, Vertex* cityVertex) {
    //TODO-POR AQUI O RESULTADO DE NETWORK.EDMONDSKARP PARA UMA CITY E DAR PRINT

    //WR sao sources
    //C are sinks, neste caso so ha uma sink
    //maxflow is the sum of all bottleneck values of the sink

    string targetCode = cityVertex->getInfo().getCode();
    double maxFlow = 0;

    for(auto v : network.getVertexSet()){
        if(v->getInfo().getIsWaterReservour()){
            string sourceCode = v->getInfo().getCode();
            edmondsKarp(&network,sourceCode,targetCode);

            double maxFlowContender = 0;

            for(auto e : cityVertex->getIncoming()){
                maxFlowContender += e->getFlow();
            }

            if(maxFlowContender > maxFlow) maxFlow = maxFlowContender;
        }

    }




    cout << " _____________________________________________ \n"
            "|       Calculate Max Amount of Water         |\n"
            "                                               \n"
            "  city's max flow is:         "<< maxFlow <<"  \n"
            "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

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

// T2.1
void Menu::insertCityCode(Network network) {
    cout << " _____________________________________________ \n"
            "|               Insert City Code              |\n"
            "                                               \n"
            " > Type the desired city code                  \n"
            "                                               \n"
            "                 (e.g: C_1)                    \n"
            " _____________________________________________ \n";

    string cmd;

    getline(cin, cmd);
    Vertex* cityVertex = network.findVertex(cmd);


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


// T2.2
void Menu::verifyWaterSupply(Network& network) {
    cout << " _____________________________________________ \n"
            "|        Verify Water Supply                    |\n"
            "                                               \n";

    auto waterDeficits = network.verifyWaterSupply();

    if (waterDeficits.empty()) {
        cout << "All cities are supplied with enough water.\n";
    } else {
        cout << "The following cities are facing water supply deficits:\n";
        for (const auto& [cityCode, deficit] : waterDeficits) {
            cout << "City Code: " << cityCode << ", Water Deficit: " << deficit << endl;
        }
    }

    cout << "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

    string cmd;
    getline(cin, cmd);

    while (cmd != "q" && cmd != "0") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    nextPage();
    mainPage(network);
}


// T3.1
void Menu::reservoirImpact(Network network) {
    cout << " _____________________________________________ \n"
            "|             Reservoir Impact                 |\n"
            "                                               \n"
            " > Specific Reservoir                   [1]    \n"
            " > All Reservoirs                       [2]    \n"
            "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

    string cmd;
    getline(cin, cmd);

    while (cmd != "q" && cmd != "0" && cmd != "1" && cmd != "2") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    int operation = stoi(cmd);

    switch (operation) {
        case 0:
            nextPage();
            mainPage(network);
            break;
        case 1:
            nextPage();
            specificReservoirImpact(network);
            break;
        case 2:
            nextPage();
            allReservoirsImpact(network);
            break;
    }
}

void Menu::specificReservoirImpact(Network network) {
    cout << " _____________________________________________ \n"
            "|          Specific Reservoir Impact           |\n"
            "                                               \n"
            " > Enter Reservoir Code:                        \n";

    string cmd;
    getline(cin, cmd);

    Info reservoirInfo("", "", 0, cmd, 0);
    bool isDeliveryPossible = network.checkDeliveryCapacity(reservoirInfo);

    if (isDeliveryPossible) {
        cout << "The delivery capacity is not affected by removing reservoir " << cmd << ".\n";
    } else {
        cout << "The delivery capacity is affected by removing reservoir " << cmd << ".\n";
    }

    cout << "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

    getline(cin, cmd);

    while (cmd != "q" && cmd != "0") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    nextPage();
    reservoirImpact(network);
}

void Menu::allReservoirsImpact(Network network) {
    cout << " _____________________________________________ \n"
            "|             All Reservoirs Impact            |\n"
            "                                               \n";

    cout << "Placeholder for calculating impact for all reservoirs.\n";

    cout << "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

    string cmd;
    getline(cin, cmd);

    while (cmd != "q" && cmd != "0") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    nextPage();
    reservoirImpact(network);
}


// T3.2

void Menu::pumpingStationImpact(Network network) {
    cout << " _____________________________________________ \n"
            "|        Pumping Station Impact               |\n"
            "                                               \n"
            " > Not Essential                          [1]  \n"
            " > Specific Pumping Station               [2]  \n"
            " > All Pumping Stations                   [3]  \n"
            "                                               \n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

    string cmd;
    getline(cin, cmd);

    while (cmd != "q" && cmd != "0" && cmd != "1" && cmd != "2" && cmd != "3") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    int operation = stoi(cmd);

    switch (operation) {
        case 0:
            nextPage();
            mainPage(network);
            break;
        case 1:
            nextPage();
            notEssentialPumpingStation(network);
            break;
        case 2:
            nextPage();
            specificPumpingStationImpact(network);
            break;
        case 3:
            nextPage();
            allPumpingStationsImpact(network);
            break;
    }

}

void Menu::notEssentialPumpingStation(Network network) {
    cout << " _____________________________________________ \n"
            "|          Not Essential Pumping Station      |\n"
            "                                               \n";

    cout << "List of pumping stations:\n";
    for (const auto& [key, vertex] : network.getVertices()) {
        Info info = vertex->getInfo();
        if (!info.getIsCity()) {
            cout << "Pumping Station Code: " << info.getCode() << endl;
        }
    }

    cout << "Enter the code of the pumping station you want to check: ";
    string pumpingStationCode;
    getline(cin, pumpingStationCode);

    Vertex* pumpingStationVertex = network.findVertex(pumpingStationCode);

    if (pumpingStationVertex == nullptr || pumpingStationVertex->getInfo().getIsCity()) {
        cout << "Invalid pumping station code.\n";
        return;
    }

    Info pumpingStationInfo = pumpingStationVertex->getInfo();

    bool isDeliveryPossible = network.checkDeliveryCapacity(pumpingStationInfo);

    if (isDeliveryPossible) {
        cout << "Removing pumping station " << pumpingStationCode << " does not affect delivery capacity.\n";
    } else {
        cout << "Removing pumping station " << pumpingStationCode << " affects delivery capacity.\n";
    }

    cout << "_________________________________________________\n";
}

void Menu::specificPumpingStationImpact(Network network) {
    cout << " _____________________________________________ \n"
            "|       Specific Pumping Station Impact       |\n"
            "                                               \n";

    cout << "List of pumping stations:\n";
    for (const auto& [key, vertex] : network.getVertices()) {
        Info info = vertex->getInfo();
        if (!info.getIsCity()) {
            cout << "Pumping Station Code: " << info.getCode() << endl;
        }
    }

    cout << "Enter the code of the pumping station you want to analyze: ";
    string pumpingStationCode;
    getline(cin, pumpingStationCode);

    Vertex* pumpingStationVertex = network.findVertex(pumpingStationCode);

    if (pumpingStationVertex == nullptr || pumpingStationVertex->getInfo().getIsCity()) {
        cout << "Invalid pumping station code.\n";
        return;
    }

    Info pumpingStationInfo = pumpingStationVertex->getInfo();

    auto impact = network.pumpingStationImpact(pumpingStationInfo);

    cout << "Impact on delivery capacity for each city:\n";
    for (const auto& [cityCode, deficit] : impact) {
        cout << "City Code: " << cityCode << ", Water Supply Deficit: " << deficit << endl;
    }

    cout << "_________________________________________________\n";
}

void Menu::allPumpingStationsImpact(Network network) {
    cout << " _____________________________________________ \n"
            "|          All Pumping Stations Impact         |\n"
            "                                               \n";

    auto impact = network.allPumpingStationsImpact();

    cout << "Impact on delivery capacity for each city:\n";
    for (const auto& [cityCode, deficit] : impact) {
        cout << "City Code: " << cityCode << ", Water Supply Deficit: " << deficit << endl;
    }

    cout << "_________________________________________________\n";
}
