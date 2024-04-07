#ifndef PROJETO1DA_ALGORITHMS_H
#define PROJETO1DA_ALGORITHMS_H
#include <queue>
#include "../graph/Network.h"

/*Edmonds karp*/

/**
 * @brief Implements the Edmonds-Karp algorithm to find the max flow in a network.
 *
 * @details Searches the maximum flow from a source vertex 's' to a target vertex 't' in a network. 
 * It iterates through the network until it no longer find any more path from 's' to 't',
 * calculating the flow according to change of paths. First it need to check if they exist, which
 * throws an error in case its not valid. After that, it go get them and start doing a loop to find the paths path
 * using BFS, while computing the minimum residual capacity along the path, and updating the flow along the path.
 * Once no more path exists, the algorithm calculates and saves the incoming flow for each vertex in the network.
 *
 * @param network The network to use
 * @param sourceCode The code of the starting Vertex
 * @param targetCode The code of the final Vertex
 *
 * @throws std::logic_error if either source or/and target vertex is invalid or if the source = target.
 *
 * @complexity The time complexity of this depends on the number of iterations to get the max flow.
 * In the worst case, where the algorithm iterates through all possible paths, the time complexity is O(V * E^2),
 * where 'V' stands for the number of vertices and 'E' stands for the number of edges in the network.
 */
void edmondsKarp(Network *network, string sourceCode, string targetCode);

/**
 * @brief Updates the flow, while going a certain path from sourceVertex to targetVertex.
 *
 * @details This function travels the path from targetVertex back to sourceVertex
 * and updates the flow of the edges along the path. It goes through the edges of the path,
 * updating the flow values based on the direction of the edges.
 *
 * @param sourceVertex The initial vertex.
 * @param targetVertex The vertex to reach.
 * @param flow The starting value of the flow.
 *
 * @complexity The time complexity depends on the length of the augmenting path, which is the number of vertices in the network.
 * Therefore, in the worst case, where the path contains 'V' vertices, the time complexity is O(V).
 */
void augmentFlowOfPath(Vertex *sourceVertex, Vertex *targetVertex, double flow);

/**
 * @brief Finds the minimum residual capacity along the augmenting path from the source 's' to the target 't'.
 *
 * @details This function traverses the augmenting path from the target vertex 't' back to the source vertex 's'
 * to find the minimum residual capacity along the path. It iterates through the edges of the path, updating the
 * minimum residual capacity encountered. If the edge direction is from destination to origin, it calculates the
 * residual capacity as the edge capacity minus the flow. If the direction is from origin to destination, it calculates
 * the residual capacity as the flow. Finally, it returns the minimum residual capacity found along the augmenting path.
 *
 * @param sourceVertex
 * @param targetVertex
 *
 * @return The minimum residual capacity along path from sourceVertex to targetVertex.
 *
 * @complexity The time complexity depends on the length of the augmenting path, which is the number of vertices in the network.
 * Therefore, in the worst case, where the path contains 'V' vertices, the time complexity is O(V).
 */
double findMinResidualAlongPath(Vertex *sourceVertex, Vertex *targetVertex);

/**
 * @brief Finds an augmenting path using Breadth-First Search.
 *
 * @details This function performs a Breadth-First Search (BFS) on the given network 'g' starting from the source vertex 's'
 * to find an augmenting path leading to the target vertex 't'. It marks all vertices as unvisited initially, then marks
 * the source vertex 's' as visited and enqueues it. During BFS traversal, it processes outgoing and incoming edges of each
 * visited vertex to find an augmenting path.
 *
 * @param network
 * @param sourceVertex
 * @param targetVertex
 *
 * @return True if path is found, false otherwise.
 *
 * @complexity The time complexity of this function depends on the size of the network and the number of edges. In the worst
 * case, where the network has 'V' vertices and 'E' edges, the time complexity is O(V + E), as it performs BFS traversal.
 */
bool findAugmentingPath(Network *network, Vertex *sourceVertex, Vertex *targetVertex);

/**
 * @brief Checks if a vertex is unvisited and there is residual capacity, then marks it as visited,
 * sets the path through which it was reached, and enqueues it
 *
 * @details This function is used in network traversal algorithms to visit vertices while considering residual capacities.
 * It checks if the vertex 'w' is not visited and there is residual capacity, then marks 'w' as visited, sets the path
 * through which it was reached, and enqueues it for further processing
 *
 * @param q
 * @param e
 * @param w
 * @param residual 
 *
 * @complexity The time complexity is O(1) since it has no for's or other things like that
 */
void visitAndTest(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);




#endif //PROJETO1DA_ALGORITHMS_H
