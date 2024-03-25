#include <iostream>
#include "graph/Network.h" // Certifique-se de que este é o caminho correto para o arquivo

int main() {
    Network network;

    // Carregar dados
    network.read_reservoirsFile("caminho/para/Reservoirs.csv");
    network.read_citiesFile("caminho/para/Cities.csv");
    network.read_stationsFile("caminho/para/Stations.csv");
    network.read_pipesFile("caminho/para/Pipes.csv");

    // Supondo que você tenha métodos implementados para imprimir vértices e arestas
    network.printVertices(); // Este método precisa ser implementado por você
    network.printEdges(); // Implementação fornecida anteriormente

    return 0;
}
