/*******************************************************************************
 * Graph.cpp
 *
 * Tanner G, Jeff Y, Micah J, Mitchell O
 * 4/5/2016
 * Discrete Mathematics I Project
 *
 * An object that represents a Discrete graph. This object does not print
 * to the console.
 *
*******************************************************************************/

#include "Graph.h"
#include "Tools.h"
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

// ------------------------------------------------------------------------
// Graph: Default constructor, creates an empty graph with 0 vertices
// ------------------------------------------------------------------------
Graph::Graph()
{
  loaded = false;
}

// ------------------------------------------------------------------------
// Graph: Constructor for a Graph that loads in graph
//        data from a file.
// data: file input stream connected to the verified graph.txt file
// ------------------------------------------------------------------------
Graph::Graph(ifstream& data)
{
  // Load in edge number and number of vertices
  int num_vertices,
      num_edges;
  data >> num_vertices >> num_edges;

  for (int v = 0; v < num_vertices; v++)
  {
    Vertex vertex(0, v);
    vertexSet.push_back(vertex);
  }

  int f, t, w;
  for (int e = 0; e < num_edges; e++)
  {
    data >> f >> t >> w;
    Edge edge(f, t, w);
    edgeSet.push_back(edge);
    vertexSet[f].incrementDegree();
    vertexSet[t].incrementDegree();
  }

  // sort edgeSet in nondecreasing order by weight
  generateDegreeSequence();

  loaded = true;

}

// ------------------------------------------------------------------------
// generateDegreeSequence: Generates a degree sequence from vertex set
// ------------------------------------------------------------------------
void Graph::generateDegreeSequence()
{
  // Initialize Sequence
  for (int i = 0; i < vertexSet.size(); i++)
    degreeSequence.push_back(vertexSet[i].getDegree());

  Tools::sortNonIncreasing(degreeSequence, vertexSet.size());
}

// ------------------------------------------------------------------------
// findAnnihilationNumber: Computes the annhilation number. The annihilation
//                         number a(G) is the largest integer k such that the
//                         sum of the first k terms of the nondecreasing degree
//                         sequence of G is at most the number of edges in G.
// returns an int
// ------------------------------------------------------------------------
int Graph::findAnnihilationNumber()
{
  int edge_num = getEdgeNum();
  int k = 0,
      sum = 0;
  for (int i = vertexSet.size() - 1; i > 0; i--) // Traverse backwards
  {
    sum += degreeSequence[i];
    if (sum <= edge_num)
      k++;
    else
      break; // fuck it...
  }

  return k;
}

// ------------------------------------------------------------------------
// findMinimumSpanningTree: Uses Prim's algorithm to find the Minimum
//                          spanning tree of this graph object
// returns a GraphSet
// ------------------------------------------------------------------------
/*GraphSet Graph::findMinimumSpanningTree()

  Create GraphSet G initialized with this Graph vertexSet and edgeSet
  Create GraphSet H

  Add some vertex from this Graph to vertexSet in H

  sort G by weight in nondecreasing order

  While H.vertexSet != G.vertexSet (has same elements, regardless of order)
    Get edges that can be added that will keep H a tree (eA)
    if eA.size() > 0
      Find lowest cost edge in eA (e)
    else // all remaining edges will make it a cycle
      return H

    add e to H.edgeSet
    remove e from G.edgeSet

    if (e.from is not in H.vertexSet)
      add vertex with id e.from to vertexSet
    if (e.to is not in H.vertexSet)
      add vertex with id e.to to vertexSet
  end while

  return H

  IS THIS RIGHT?
*/

// ------------------------------------------------------------------------
// findKResElimSeq: Calls the recursive findKResElimSeq to make it easier
// print_steps: prints result of each step if true
// returns a vector<int>
// ------------------------------------------------------------------------
vector<int> Graph::findKResElimSeq(bool print_steps)
{
  return findKResElimSeq(degreeSequence, vertexSet.size(), print_steps);
}

// ------------------------------------------------------------------------
// findKResElimSeq: Uses the Havel-Hakimi algorithm to find the k-residue,
//                  the elimination sequence, and if the sequence is graphic.
//                  Returns true if it is graphic, false otherwise. The
//                  sequence passed in is rebuilt in this format:
//                  {elimination sequence, k-residue} with k-residue being
//                  the last element of the sequence.
// seq: degree sequence to input
// n: number of slots the algorithm looks at in seq
// print_steps: prints result of each step if true
// returns a vector<int>
// ------------------------------------------------------------------------
vector<int> Graph::findKResElimSeq(vector<int> seq, int n, bool print_steps)
{
  if (print_steps)
    cout << Tools::getVectorAsString(seq, n) << endl;

  // Grab first number
  int first_num = seq[0];

  // The first number needs to be less than or equal to n-1, where n is the
  // number of vertices
  if (first_num > n - 1) // negation
  {
    seq.push_back(-1);
    return seq;
  }

  // Swap first and last number in the array
  seq[0] = seq[n - 1];
  seq[n - 1] = first_num;

  // We swapped the largest value with the last element in the array
  // So if we decrement the amount of vertices by 1 in the array, it will
  // ignore the largest value, effectively "crossing it out"
  n--;

  // Sort all but the one we "crossed out" keeping them saved at the end
  Tools::sortNonIncreasing(seq, n);

  // Subtract 1 from the first first_num numbers ...yeah
  for (int i = 0; i < first_num; i++)
    seq[i]--;

  // Sort before passing the array back through
  Tools::sortNonIncreasing(seq, n);

  // Check for base case
  if (Tools::anyNegatives(seq, n)) // Vertices can't have negative degrees
  {
    if (print_steps) // print last "failure" step
      cout << Tools::getVectorAsString(seq, n) << endl;
    seq.push_back(-1);
    return seq;
  }
  else if (Tools::onlyZeros(seq, n)) // If there's only zeros left
  {
    if (print_steps)
      cout << Tools::getVectorAsString(seq, n) << endl;
    Tools::sortNonIncreasing(seq, vertexSet.size());
    seq.push_back(Tools::countZeros(seq, vertexSet.size()));
    return seq; // We're done!
  }
  else if (n <= 1) // If there's not only zeros and we're on the last
  {
    if (print_steps) // print last "failure" step
      cout << Tools::getVectorAsString(seq, n) << endl;
    seq.push_back(-1);
    return seq; // one, then we can't end up with zeros
  }
  else // If there's no negatives, nonzeros, and its not on the last number
  {
    return findKResElimSeq(seq, n, print_steps); // Keep going!
  }
}

// ------------------------------------------------------------------------
// Accessors: Various accessors to member variables, this is ugly
// ------------------------------------------------------------------------
int Graph::getEdgeNum() const { return edgeSet.size(); }
int Graph::getVertexNum() const { return vertexSet.size(); }
vector<int> Graph::getSequence() const { return degreeSequence; }
bool Graph::isLoaded() const { return loaded; }
string Graph::getDegreeSequenceAsString() const
{
  return Tools::getVectorAsString(degreeSequence, vertexSet.size());
}
string Graph::getEdgeSetAsString() const
{
  stringstream ss;
  for (int e = 0; e < edgeSet.size(); e++)
  {
    ss << edgeSet[e].toString();
    if (e < edgeSet.size() - 1) // don't put a space at the end
      ss << " ";
  }
  return ss.str();
}
string Graph::getVertexSetAsString() const
{
  vector<int> v;
  for (int i = 0; i < vertexSet.size(); i++)
    v.push_back(vertexSet[i].getId());
  return Tools::getVectorAsString(v, vertexSet.size());
}
int Graph::getMaxDegree() const
{
  return Tools::findMax(degreeSequence, vertexSet.size());
}
int Graph::getMinDegree() const
{
  return Tools::findMin(degreeSequence, vertexSet.size());
}
int Graph::getAverageDegree() const
{
  return Tools::findAverage(degreeSequence, vertexSet.size());
}
