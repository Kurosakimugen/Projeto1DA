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
            pipelinefailureimpact(network);
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

            maxFlowContender = cityVertex->getInfo().getFlow();
            /*
            for(auto e : cityVertex->getIncoming()){
                maxFlowContender += e->getFlow();
            }*/

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
            " > Specific Pumping Station               [1]  \n"
            " > All Pumping Stations                   [2]  \n"
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
            specificPumpingStationImpact(network);
            break;
        case 2:
            nextPage();
            allPumpingStationsImpact(network);
            break;
    }

}


void Menu::specificPumpingStationImpact(Network network) {

    vector<string> notEssentialStations = network.findNotEssentialPumpingStations();

    cout << "Available Pumping Stations:\n";
    for (size_t i = 0; i < notEssentialStations.size(); ++i) {
        cout << i + 1 << ". " << notEssentialStations[i] << "\n";
    }

    cout << "\nEnter the number corresponding to the pumping station to analyze its impact: ";
    int stationIndex;
    cin >> stationIndex;

    if (stationIndex < 1 || stationIndex > static_cast<int>(notEssentialStations.size())) {
        cout << "Invalid input. Please select a valid pumping station.\n";
        specificPumpingStationImpact(network); // Reiniciar a função
        return;
    }

    string selectedStation = notEssentialStations[stationIndex - 1];

    bool isDeliveryCapacityMaintained = network.checkDeliveryCapacityAfterRemoval(selectedStation);

    if (isDeliveryCapacityMaintained) {
        cout << "\nThe removal of pumping station " << selectedStation << " does not affect the delivery capacity to all the cities.\n";
    } else {
        cout << "\nThe removal of pumping station " << selectedStation << " affects the delivery capacity to some cities.\n";

        cout << "\nMost Affected Cities:\n";
        auto affectedCities = network.identifyMostAffectedCities(selectedStation);

        map<string, string> cityNames = {
                {"C_1", "Porto Moniz"},
                {"C_2", "Santana"},
                {"C_3", "Machico"},
                {"C_4", "Funchal"},
                {"C_5", "Santa Cruz"},
                {"C_6", "Calheta"},
                {"C_7", "Ponta do Sol"},
                {"C_8", "Ribeira Brava"},
                {"C_9", "Camara de Lobos"},
                {"C_10", "Machico"}
        };

        cout << "\nCity Old Flow | New Flow | Deficit\n";
        for (const auto& [cityCode, deficit] : affectedCities) {
            double oldFlow = deficit;
            double newFlow = network.calculateFlowAfterStationRemoval(selectedStation, cityCode) - oldFlow;
            double waterDeficit = network.calculateWaterDeficit(cityCode, oldFlow, newFlow);

            cout << cityCode << ": " << cityNames[cityCode] << " " << oldFlow << " " << newFlow << " " << waterDeficit << "\n";
        }

    }

    cout << "\n_____________________________________________\n"
            " > Back [0]                        > Quit [q]  \n"
            " _____________________________________________ \n";

    string cmd;
    getline(cin, cmd); 
    getline(cin, cmd);

    while (cmd != "q" && cmd != "0") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") {
        quit(); 
    } else {
        mainPage(network); 
    }
}


void Menu::allPumpingStationsImpact(Network network) {
    for (Vertex* vertex : network.getVertexSet()) {
        Info info = vertex->getInfo();

        if (info.getIsDeliverySite()) {
            string stationCode = info.getCode();

            cout << "Processing pumping station: " << stationCode << endl;

            map<string, double> affectedCities = network.identifyMostAffectedCities(stationCode);

            cout << "Most affected cities by removing pumping station " << stationCode << ":" << endl;
            if (affectedCities.empty()) {
                cout << "No affected cities." << endl;
            } else {
                for (const auto& city : affectedCities) {
                    cout << "City Code: " << city.first << ", Water Supply Deficit: " << city.second << endl;
                }
            }
            cout << "---------------------------------------------" << endl;
        }
    }
}

// T3.3

void Menu::pipelinefailureimpact(Network network) {
    cout <<" _____________________________________________ \n"
           "|        Pipeline Failure Impact               |\n"
           "                                               \n"
           " > All Pipelines                          [1]  \n"
           " > Specific City                          [2]  \n"
           "                                               \n"
           " > Back [0]                        > Quit [q]  \n"
           " _____________________________________________ \n";

    string cmd;
    getline(cin, cmd);

    while (cmd != "q" && cmd != "1" && cmd != "2" ) {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    int operation = stoi(cmd);

    switch (operation) {
        case 1:
            nextPage();
            AllPipelineImpact(network);
            break;
        case 2:
            nextPage();
            CityPipelineImpact(network);
            break;
    }
}

void Menu::AllPipelineImpact(Network network) {
    cout << " _____________________________________________ \n"
            "|          All Pipeline Failure Impact         |\n"
            "                                               \n";

    auto impact = network.eachPipelineImpact();

    cout << "Impact on the flow of each city:\n";
    for (const auto& [PipeID, Resultado] : impact) {
        cout << Resultado << endl;
    }

    cout << " > Back [0]                        > Quit [q]    \n"
            "_________________________________________________\n";
    string cmd;
    getline(cin, cmd);

    while (cmd != "q" && cmd != "0" && cmd != "1" && cmd != "2" && cmd != "3") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    if (cmd == "0") {
        nextPage();
        pipelinefailureimpact(network);
    }
}

void Menu::CityPipelineImpact(Network network) {
    cout << " _____________________________________________ \n"
            "|       Specific City Pipeline Impact         |\n"
            "                                               \n";

    cout << "List of Cities:\n";
    for (const auto& [key, vertex] : network.getVertices()) {
        Info info = vertex->getInfo();
        if (info.getIsCity()) {
            cout << "City Code: " << info.getCode() << endl;
        }
    }

    cout << "Enter the code of the City you want to analyze: ";
    string CityCode;
    getline(cin, CityCode);

    Vertex* CityVertex = network.findVertex(CityCode);

    if (CityVertex == nullptr || !CityVertex->getInfo().getIsCity()) {
        cout << "Invalid City code.\n";
        return;
    }

    auto impact = network.CityPipelineImpact(CityVertex);

    cout << "Impact on the flow of " << CityVertex->getInfo().getName() << " city:\n";
    for (const auto& [PipeID, Resultado] : impact) {
        cout << Resultado << endl;
    }

    cout << " > Back [0]                        > Quit [q]    \n"
            "_________________________________________________\n";
    string cmd;
    getline(cin, cmd);

    while (cmd != "q" && cmd != "0" && cmd != "1" && cmd != "2" && cmd != "3") {
        cout << "ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (cmd == "q") quit();

    if (cmd == "0") {
        nextPage();
        pipelinefailureimpact(network);
    }
}