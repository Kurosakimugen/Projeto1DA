#ifndef EDGE_H
#define EDGE_H


#include "Info.h"
#include "Vertex.h"


class Edge{
public:

    /**
     * Edge Constructor
     * @param orig
     * @param dest
     * @param weight
     * @param isUnidirectional
     */
    Edge(Vertex* orig, Vertex* dest, double weight, bool isUnidirectional);


    /**
     * Function to get the destination vertex
     * @return Node destination vertex
     */
    Vertex *getDest() const;

    /**
     * Function to get the value of weight
     * @return weight value
     */
    double getWeight() const;

    /**
     * Function to get the origin vertex
     * @return Node of origin
     */
    Vertex *getOrig() const;

    //Parte do Selected
    /**
     * Function to know if a edge has been selected or not
     * @return true if it has or false if not
     */
    bool isSelected() const;

    /**
     * Function to change the select value
     * @param selected
     */
    void setSelected(bool selected);

    //Parte do Reverse
    /**
     * Function to get the same Edge but with the origin and destination reverted
     * @return Reverted Edge
     */
    Edge *getReverse() const;

    /**
     * Function to create the same with edges but with nodes reversed
     * @param reverse
     */
    void setReverse(Edge *reverse);

    //Parte do Flow
    /**
     * Function to get the value of the flow
     * @return Flow value
     */
    double getFlow() const;

    /**
     * Function to set the value of flow
     * @param flow
     */
    void setFlow(double flow);

    bool getIsUnidirectional() const;

protected:
    Vertex *dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
    bool isUnidirectional;

    void setIsUnidirectional(bool value);
};

#endif // EDGE_H
