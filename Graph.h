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
    Graph();
    Graph(std::ifstream&);

    // stuff that generates stuff
    void generateDegreeSequence();

    // Algorithms
    std::vector<int> findKResElimSeq(bool);
    std::vector<int> findKResElimSeq(std::vector<int>, int, bool);
    int findAnnihilationNumber();

    // Accessors
    int getEdgeNum() const;
    int getVertexNum() const;
    int getResidue() const;
    int getAnnihiltion() const;
    std::vector<int> getSequence() const;
    bool isLoaded() const;
    std::string getDegreeSequenceAsString() const;
    int getMaxDegree() const;
    int getMinDegree() const;
    int getAverageDegree() const;

  private:
    std::vector<int> degreeSequence;

    std::vector<Vertex> vertexSet;
    std::vector<Edge> edgeSet;

    bool loaded;
};

#endif // Graph_H
