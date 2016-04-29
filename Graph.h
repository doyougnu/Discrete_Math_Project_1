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

#include "Vertex.h"
#include "Edge.h"
#include "libs.h"

class Graph
{
  public:
    Graph(std::ifstream&, std::string);

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
    GraphSet findMinimumSpanningTree(int, bool);

    std::vector<std::vector<int> > findZeroForcingSets(int);
    void recursiveForcingSet(std::vector<int>&, int, int, std::vector<int>&,
      std::vector<std::vector<int> >&, int&, bool&);

    std::vector<std::vector<int> > findMaximumIndependentSets(int);
    std::vector<std::vector<int> > findMaximumIndependentSets(GraphSet, int);
    void recursiveIndependentSet(std::vector<int>&, int, int, std::vector<int>&,
      std::vector<std::vector<int> >&, int&, bool&, GraphSet&);

    std::vector<std::vector<int> > findMaximalCliques();
    void bronKerbosch(std::vector<int>, std::vector<int>, std::vector<int>,
      std::vector<std::vector<int> >&, bool&);

    int findChromaticNumber();
    int findChromaticNumber(GraphSet);

    std::vector<std::vector<int> > findMinimumDominatingSets(int);
    void recursiveDominatingSet(std::vector<int>&, int, int, std::vector<int>&,
      std::vector<std::vector<int> >&, int&, bool&);

    int findKPartite();
    int findKPartite(GraphSet, int&);

    void sortEdgeSetByWeightNonDecreasing(std::vector<Edge>&);
    void sortVertexSetByDegreeNonDecreasing(std::vector<Vertex>&);
    void sortVertexSetByDegreeNonIncreasing(std::vector<Vertex>&);

    // Functions
    bool isTreeAfterAdding(Edge, GraphSet, GraphSet);
    void addEdgeToGraphSet(Edge, GraphSet&, GraphSet);
    void addVertexToGraphSet(Vertex, GraphSet&);
    void removeVertexFromGraphSet(int, GraphSet&);
    void removeEdgeFromGraphSet(Edge, GraphSet&);
    bool isSpanningTree(GraphSet, GraphSet) const;
    bool isSpanningTree(GraphSet) const;
    bool isEdgeInGraph(Edge, GraphSet) const;
    bool isVertexInGraph(Vertex, GraphSet) const;
    bool isVertexInSet(Vertex, std::vector<Vertex>) const;
    bool isTree(GraphSet) const;
    bool vertexSetEqual(GraphSet, GraphSet) const;
    bool vertexSetEqual(std::vector<Vertex>, std::vector<Vertex>GraphSet) const;
    Vertex getVertexById(int, GraphSet) const;
    std::vector<std::vector<int> > genAllEdges(int);
    int maxPossibleEdges(int);
    bool isForcingSet(std::vector<int>);
    int getVertexWithOneNonColoredNeighbor(std::vector<Vertex>,
      std::vector<Vertex>) const;
    bool isIndependentSet(std::vector<int>);
    bool isIndependentSet(std::vector<int>, GraphSet);
    bool isDominatingSet(std::vector<int>);
    int findMColoring(int);
    int findMColoring(GraphSet, int);
    bool isGraphColored(GraphSet);

    // Accessors
    int getEdgeNum() const;
    int getVertexNum() const;
    int getResidue() const;
    int getAnnihiltion() const;
    std::vector<int> getSequence() const;
    std::string getDegreeSequenceAsString() const;
    std::string getEdgeSetAsString(std::vector<Edge>) const;
    std::string getVertexSetAsString(std::vector<Vertex>) const;
    std::vector<Vertex> getVertexSetAsVector() const;
    std::string getGraphInformation() const;
    int getMaxDegree() const;
    int getMinDegree() const;
    int getAverageDegree() const;
    GraphSet getGraphSet() const;

  private:
    std::vector<int> degreeSequence;
    GraphSet graphSet;
};

#endif // Graph_H
