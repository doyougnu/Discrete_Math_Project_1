/*******************************************************************************
 * Graph.h
 *
 * Tanner Gower, put, your, names, here
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
    Graph(std::&ifstream);

    // Algorithms
    vector<int> findKResElimSeq(bool);
    vector<int> findKResElimSeq(vector<int>, int, bool);
    int findAnnihilationNumber();

    // Accessors
    int getEdgeNum() const;
    int getVertexNum() const;
    int getResidue() const;
    int getAnnihiltion() const;
    vector<int> getSequence() const;
    bool isLoaded() const;
    std::string getDegreeSequenceAsString() const;
    int getMaxDegree() const;
    int getMinDegree() const;
    int getAverageDegree() const;

  private:
    vector<int> degreeSequence;

    vector<Vertex> vertexSet;
    vector<Edge> edgeSet;

    bool loaded;
};

#endif // Graph_H
