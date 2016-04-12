/*******************************************************************************
 * Graph.h
 *
 * Tanner G, Jeff Y, Micah J, Mitchell O
 * 4/5/2016
 * Discrete Mathematics I Project
 *
 * A class declaration of a Graph object.
 *
*******************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"

class Graph
{
  public:
    Graph(std::ifstream&);

    struct GraphSet
    {
      std::vector<Vertex> vertexSet;
      std::vector<Edge> edgeSet;
    };

    // stuff that generates stuff
    void generateDegreeSequence();

    // Algorithms
    std::vector<int> findKResElimSeq(bool);
    std::vector<int> findKResElimSeq(std::vector<int>, int, bool);
    int findAnnihilationNumber();
    // GraphSet findMinimumSpanningTree() const;
    void sortEdgeSetByWeightNonDecreasing(std::vector<Edge>&);

    // Functions
    // bool isTreeAfterAdding(Edge, GraphSet) const;
<<<<<<< HEAD
    // bool isSpanningTree(GraphSet, GraphSet) const;
    // bool isTree(GraphSet) const;
=======
    // bool isSpanningTree(GraphSet) const;
    bool isTree(GraphSet);
>>>>>>> b427591f1e10c5decb8cc7d207ac4ab8d77f0365

    // Functions for GraphSets (number sets)
    bool vertexSetEqual(std::vector<Vertex>, std::vector<Vertex>) const;

    // Accessors
    int getEdgeNum() const;
    int getVertexNum() const;
    int getResidue() const;
    int getAnnihiltion() const;
    std::vector<int> getSequence() const;
    std::string getDegreeSequenceAsString() const;
    std::string getEdgeSetAsString() const;
    std::string getVertexSetAsString() const;
    std::string getGraphInformation() const;
    int getMaxDegree() const;
    int getMinDegree() const;
    int getAverageDegree() const;

  private:
    std::vector<int> degreeSequence;
    GraphSet graphSet;
};

#endif // Graph_H
