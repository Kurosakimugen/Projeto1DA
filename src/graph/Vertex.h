#ifndef PROJETO1DA_VERTEX_H
#define PROJETO1DA_VERTEX_H

#include <vector>
#include "Info.h"

class Edge;
class Vertex {
public:
    /**
     * Vertex Constructor
     * @param inf
     */
    Vertex(Info inf);
    bool operator<(Vertex& vertex) const; // // required by MutablePriorityQueue

    /**
     * Function to get the info of a vertex
     * @return info value
     */
    Info getInfo() const;

    /**
     * Function to get the list of all edges from that vertex
     * @return list of edges
     */
    std::vector<Edge*> getAdj() const;

    //Parte do visited
    /**
     * Function to  if a vertex is visited or not
     * @return true if yes or false otherwise
     */
    bool isVisited() const;

    /**
     * Function to set the value of visited
     * @param visited
     */
    void setVisited(bool visited);

    //Parte do processing
    /**
     * Function to check if a vertex is being processesd
     * @return true if yes or false otherwise
     */
    bool isProcessing() const;

    /**
     * Function to set the value of processing
     * @param processing
     */
    void setProcessing(bool processing);

    //parte do indegree
    /**
     * Function to get the value of degree
     * @return indegree
     */
    unsigned int getIndegree() const;

    /**
     * Function to set the value of indegree
     * @param indegree
     */
    void setIndegree(unsigned int indegree);

    //parte do dist
    /**
     * Function to get the value of dist
     * @return dist
     */
    double getDist() const;

    /**
     * Function to set the value of dist
     * @param dist
     */
    void setDist(double dist);

    //parte do path
    /**
     * Function to get the path of a vertex
     * @return path
     */
    Edge *getPath() const;

    /**
     * Function to set the value of a path
     * @param path
     */
    void setPath(Edge *path);

    /**
     * Function to get all incoming edges with x vertex being the destination
     * @return list of edges
     */
    std::vector<Edge *> getIncoming() const;

    /**
     * Function to set info
     * @param info
     */
    void setInfo(Info info);

    /**
     * Function to add an edge into a vertex
     * @param dest
     * @param w
     * @param isUnidirectional
     * @return
     */
    Edge * addEdge(Vertex *dest, double w, bool isUnidirectional);

    /**
     * Function to remove a certain edge for all the edges
     * @param infoCode
     * @return true if sucessful or false otherwise
     */
    bool removeEdge(string infoCode);

    /**
     * Function to remove all Edges with have x as origin or x as destination
     */
    void removeOutgoingEdges();

protected:
    Info info;                // info node
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree = 0; // used by topsort
    double dist = 0;

    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);

};
#endif //PROJETO1DA_VERTEX_H
