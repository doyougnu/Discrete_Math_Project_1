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
#include "libs.h"

using namespace std;

// ------------------------------------------------------------------------
// Graph: Constructor for a Graph that loads in graph
//        data from a file.
// data: file input stream connected to the verified graph.txt file
// ------------------------------------------------------------------------
Graph::Graph(ifstream& data, string type)
{
  if (type == "es")
  {
    // Load in edge number and number of vertices
    int num_vertices,
        num_edges;

    if (data >> num_vertices >> num_edges)
    {
      for (int v = 0; v < num_vertices; v++)
      {
        Vertex vertex(v);
        graphSet.vertexSet.push_back(vertex);
      }

      int f, t, w;
      for (int e = 0; e < num_edges; e++)
      {
        data >> f >> t >> w;
        Edge edge(f, t, w);
        graphSet.edgeSet.push_back(edge);
        graphSet.vertexSet[f].addNeighbor(t);
        graphSet.vertexSet[t].addNeighbor(f);
      }

      sortEdgeSetByWeightNonDecreasing(graphSet.edgeSet);
      generateDegreeSequence();

      cout << "Done loading edge set!" << endl;
    }
    else
    {
      cout << "Failed loading edge set!" << endl;
    }
  }
  else if (type == "am")
  {
    int num_vertices;

    if (data >> num_vertices)
    {
      for (int v = 0; v < num_vertices; v++)
      {
        Vertex vertex(v);
        graphSet.vertexSet.push_back(vertex);
      }

      vector<vector<int> > matrix;
      int cell;
      for (int r = 0; r < num_vertices; r++)
      {
        vector<int> row;
        for (int c = 0; c < num_vertices; c++)
        {
          data >> cell;
          row.push_back(cell);
        }
        matrix.push_back(row);
      }

      for (int f = 0; f < num_vertices; f++)
      {
        for (int t = f; t < num_vertices; t++)
        {
          if (matrix[f][t] == 1)
          {
            Edge edge(f, t, 0);
            graphSet.edgeSet.push_back(edge);
            graphSet.vertexSet[f].addNeighbor(t);
            graphSet.vertexSet[t].addNeighbor(f);
          }
        }
      }

      generateDegreeSequence();

      cout << "Done loading adjacency matrix!" << endl;
    }
    else
    {
      cout << "Failed loading adjacency matrix!" << endl;
    }
  }
  else
  {
    cout << "Unrecognized graph file type!" << endl;
  }
}

// ------------------------------------------------------------------------
// generateDegreeSequence: Generates a degree sequence from vertex set
// ------------------------------------------------------------------------
void Graph::generateDegreeSequence()
{
  // Initialize Sequence
  for (int i = 0; i < graphSet.vertexSet.size(); i++)
    degreeSequence.push_back(graphSet.vertexSet[i].getDegree());

  Tools::sortNonIncreasing(degreeSequence, graphSet.vertexSet.size());
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
  for (int i = graphSet.vertexSet.size() - 1; i > 0; i--) // Traverse backwards
  {
    sum += degreeSequence[i];
    if (sum <= edge_num)
      k++;
    else
      break;
  }

  return k;
}

// ------------------------------------------------------------------------
// findMinimumSpanningTree: Uses Prim's algorithm to find the Minimum
//                          spanning tree of this graph object
// returns a GraphSet
// ------------------------------------------------------------------------
Graph::GraphSet Graph::findMinimumSpanningTree(int start, bool print_steps)
{
  GraphSet g, h;
  g.vertexSet = graphSet.vertexSet;
  g.edgeSet = graphSet.edgeSet;

  int weight = 0,
      step = 1;

  // Add some vertex from this Graph to vertexSet in H
  h.vertexSet.push_back(g.vertexSet[start]);

  // Loop until the vertex sets of each graphs are equal
  while (!vertexSetEqual(g, h))
  {
    // find the least cost edge
    Edge e;
    for (int i = 0; i < g.edgeSet.size(); i++) // Loop through all edges
    {
      if (isTreeAfterAdding(g.edgeSet[i], h, g)) // Find one that can be added
      {
        // This will always be the minimum cost edge because
        // we sorted by weight in non-decreasing order
        e = g.edgeSet[i];

        // Delete least cost edge e in g
        g.edgeSet.erase(g.edgeSet.begin() + i);
        break;
      }
    }

    // add e to H.edgeSet as well as vertices
    addEdgeToGraphSet(e, h, g);
    weight += e.getWeight(); // Keep track of MST weight

    // Print step
    if (print_steps)
      cout << "Step " << step << ": added " << e.toString()
           << " w(H) = " << weight << endl;
    step++;
  }

  return h;
}

// ------------------------------------------------------------------------
// sortEdgeSetByWeightNonDecreasing: Sorts an edge set by weight
// edgeSet: edge set to be sorted
// ------------------------------------------------------------------------
void Graph::sortEdgeSetByWeightNonDecreasing(vector<Edge> &edgeSet)
{
  Edge temp;
  int max;
  for (int i = 0; i < edgeSet.size() - 1; i++)
  {
    // Start with the first element as the maximum
    max = i;

    // Loop through elements and check for an element less than max
    for (int j = i + 1; j < edgeSet.size(); j++)
      if (edgeSet[j].getWeight() < edgeSet[max].getWeight())
        max = j;

    // If the maximum element is NOT what we started with, we must swap
    if (max != i)
    {
      temp = edgeSet[i];
      edgeSet[i] = edgeSet[max];
      edgeSet[max] = temp;
    }
  }
}

// ------------------------------------------------------------------------
// isTreeAfterAdding: checks if graph will remain a tree after adding edge
// edge: edge to add
// graph: graph to add edge to
// returns a bool
// ------------------------------------------------------------------------
bool Graph::isTreeAfterAdding(Edge edge, GraphSet graph, GraphSet from)
{
  addEdgeToGraphSet(edge, graph, from);
  return isTree(graph); // that was easy
}

// ------------------------------------------------------------------------
// addEdgeToGraphSet: adds an edge to the graph set and adds the vertex
//                    without duplicated vertices and edges
// edge: edge to add
// graph: graph to add edge to
// ------------------------------------------------------------------------
void Graph::addEdgeToGraphSet(Edge edge, GraphSet &graph, GraphSet from)
{
  if (!isEdgeInGraph(edge, graph)) // Make sure we don't add dupes
  {
    graph.edgeSet.push_back(edge);

    Vertex v = getVertexById(edge.getTo(), from); // Find the vertex in from
    if (v.getId() != -1)
      addVertexToGraphSet(v, graph); // add it if found and if not already added

    v = getVertexById(edge.getFrom(), from); // same shit here
    if (v.getId() != -1)
      addVertexToGraphSet(v, graph);

  }
}

// ------------------------------------------------------------------------
// addVertexToGraphSet: adds a vertex to the graph set without duplicates
// vertex: vertex to add
// graph: graph to add vertex to
// ------------------------------------------------------------------------
void Graph::addVertexToGraphSet(Vertex vertex, GraphSet &graph)
{
  if (!isVertexInGraph(vertex, graph))
    graph.vertexSet.push_back(vertex);
}

// ------------------------------------------------------------------------
// isSpanningTree: checks if tree is a spanning tree of graph
// tree: tree to check
// graph: graph to check
// returns a bool
// ------------------------------------------------------------------------
bool Graph::isSpanningTree(GraphSet tree, GraphSet graph) const
{
  if (!vertexSetEqual(tree, graph)) // Must have same vertex set
    return false;

  for (int i = 0; i < tree.edgeSet.size(); i++) // Loop through edges in tree
    if (!isEdgeInGraph(tree.edgeSet[i], graph)) // Those edges are in graph?
      return false; // If you find one that isn't, return false

  return true; // otherwise, they are all there and YAY
}

// ------------------------------------------------------------------------
// isSpanningTree: checks if tree is a spanning tree of this graph
// tree: tree to check
// returns a bool
// ------------------------------------------------------------------------
bool Graph::isSpanningTree(GraphSet tree) const
{
  return isSpanningTree(tree, graphSet);
}

// ------------------------------------------------------------------------
// isEdgeInGraph: checks if edge is in graph
// edge: edge to look for in graph
// graph: graph in question
// returns a bool
// ------------------------------------------------------------------------
bool Graph::isEdgeInGraph(Edge edge, GraphSet graph) const
{
  for (int i = 0; i < graph.edgeSet.size(); i++)
  {
    if (edge == graph.edgeSet[i])
      return true;
  }
  return false;
}

// ------------------------------------------------------------------------
// isVertexInGraph: checks if vertex is in graph
// vertex: vertex to look for in graph
// graph: graph in question
// returns a bool
// ------------------------------------------------------------------------
bool Graph::isVertexInGraph(Vertex vertex, GraphSet graph) const
{
  for (int i = 0; i < graph.vertexSet.size(); i++)
  {
    if (vertex == graph.vertexSet[i])
      return true;
  }
  return false;
}

// ------------------------------------------------------------------------
// isTree: checks if the GraphSet represents a Tree
// returns a bool
// ------------------------------------------------------------------------
bool Graph::isTree(GraphSet graphset) const
{
  return graphset.edgeSet.size() == (graphset.vertexSet.size() - 1);
}

// ------------------------------------------------------------------------
// vertexSetEqual: checks if both vertex sets have the same elements
//                 regardless of order. This treats sets like Number Sets
//                 in Discrete Math.
// v1: one of them vertex sets ya gonna checks
// v2: one of them other vertex sets ya gonna compare
// returns a bool
// ------------------------------------------------------------------------
bool Graph::vertexSetEqual(GraphSet g1, GraphSet g2) const
{
  vector<Vertex> v1 = g1.vertexSet;
  vector<Vertex> v2 = g2.vertexSet;

  if (v1.size() != v2.size())
    return false;

  bool foundMatch = false;
  for (int i = 0; i < v1.size(); i++)
  {
    for (int j = 0; j < v2.size(); j++)
    {
      if (v1[i] == v2[j]) // Check if element in v1 is anywhere in v2
        foundMatch = true; // if so, there's a match for the element
    }
    if (!foundMatch) // If we loop through and never find a match, they aren't
     return false;   // equal
  }

  return true;
}

// ------------------------------------------------------------------------
// getVertexById: finds a vertex in graph by ID, returns a vertex with
//                data (-1, -1) if not found
// vertex: id to search for
// graph: GraphSet to look in
// returns a Vertex
// ------------------------------------------------------------------------
Vertex Graph::getVertexById(int vertex, GraphSet graph) const
{
  for (int i = 0; i < graph.vertexSet.size(); i++)
    if (graph.vertexSet[i].getId() == vertex)
    {
      return graph.vertexSet[i];
    }

  Vertex v(-1);
  return v;
}

// ------------------------------------------------------------------------
// findKResElimSeq: Calls the recursive findKResElimSeq to make it easier
// print_steps: prints result of each step if true
// returns a vector<int>
// ------------------------------------------------------------------------
vector<int> Graph::findKResElimSeq(bool print_steps)
{
  return findKResElimSeq(degreeSequence, graphSet.vertexSet.size(),
                         print_steps);
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
    Tools::sortNonIncreasing(seq, graphSet.vertexSet.size());
    seq.push_back(Tools::countZeros(seq, graphSet.vertexSet.size()));
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
// maxPossibleEdges: given int n vertices, calculates the maximum number of
// edge for a given graph
// returns an int
// ------------------------------------------------------------------------
int Graph::maxPossibleEdges(int numvertices)
{
  return (numvertices * (numvertices - 1)) / 2;
}

// ------------------------------------------------------------------------
// isForcingSet: checks if this set is a forcing set of this graph with
// some salt or some shit i guess
// set: vertex set to check
// returns a damn bool
// ------------------------------------------------------------------------
bool Graph::isForcingSet(vector<int> set)
{

  vector<Vertex> c_set, v_set;

  for (int i = 0; i < graphSet.vertexSet.size(); i++)
    v_set.push_back(graphSet.vertexSet[i]);

  for (int i = 0; i < set.size(); i++)
  {
    c_set.push_back(graphSet.vertexSet[set[i]]);
    v_set[c_set.back().getId()].setColor(1);
  }

  int id = anyVertexWithExactlyOneNonColoredNeighbor(c_set, v_set);
  while (id != -1)
  {
    c_set.push_back(graphSet.vertexSet[id]);
    v_set[c_set.back().getId()].setColor(1);

    id = anyVertexWithExactlyOneNonColoredNeighbor(c_set, v_set);
  }
  return c_set.size() == v_set.size();
}

// ------------------------------------------------------------------------
// anyVertexWithExactlyOneColoredNeighbor: returns the index if found,
//  -1 if not
// set: vertex set to check
// v_set: vertex set
// returns an int
// ------------------------------------------------------------------------
int Graph::anyVertexWithExactlyOneNonColoredNeighbor(vector<Vertex> set,
                                                  vector<Vertex> v_set) const
{
  for (int i = 0; i < set.size(); i++)
  {
    int n = 0;
    for (int j = 0; j < set[i].getNeighbors().size(); j++)
    {
      if (v_set[set[i].getNeighbors()[j]].getColor() == 0)
       n++;
    }
    if (n == 1)
    {
      for (int j = 0; j < set[i].getNeighbors().size(); j++)
        if (v_set[set[i].getNeighbors()[j]].getColor() == 0)
          return set[i].getNeighbors()[j];
    }
  }
  return -1;
}

// ------------------------------------------------------------------------
// enumerate: enumerates all combinations of num_vertices choose k
// k: elements per combination
// returns a vector<vector<int>>
// ------------------------------------------------------------------------
vector<vector<int> > Graph::enumerate(int k)
{
  vector<vector<int> > result;
  vector<int> c, v_set;

  for (int i = 0; i < k; i++)
    c.push_back(0);

  for (int i = 0; i < getVertexNum(); i++)
    v_set.push_back(i);

  combinations(v_set, k, 0, c, result);

  return result;
}

// ------------------------------------------------------------------------
// combinations: recursive function for combos
// set: set to make combinations from
// l: your k
// s: starting point
// comb: single combination
// save: all combinations saved
// ------------------------------------------------------------------------
void Graph::combinations(vector<int> set, int l, int s, vector<int> comb,
                         vector<vector<int> >& save)
{
  if (l == 0)
  {
    save.push_back(comb);
    return;
  }
  for (int i = s; i <= set.size() - l; i++)
  {
    comb[comb.size() - l] = set[i];
    combinations(set, l-1, i+1, comb, save);
  }
}

// ------------------------------------------------------------------------
// findZeroForcingSet: finds the zero forcing set by BRUTEFORCE MADNESS
// returns a vector<vector<int> > i'm tired
// ------------------------------------------------------------------------
vector<vector<int> > Graph::findZeroForcingSets()
{
  int lower_bound = getMinDegree(); // From Teach's paper, thanks Teach
  vector<vector<int> > results;
  vector<vector<int> > p;
  bool found = false;

  for (int i = lower_bound; i < getVertexNum() && !found; i++)
  {
    p = enumerate(i);
    for (int j = 0; j < p.size(); j++)
    {
      if (isForcingSet(p[j]))
      {
        results.push_back(p[j]);
        found = true;
      }
    }
  }

  return results;
}

// ------------------------------------------------------------------------
// findMaximumIndependentSets: finds maximum independent sets which is also
// the independence number
// returns a vector<vector<int> >
// ------------------------------------------------------------------------
vector<vector<int> > Graph::findMaximumIndependentSets()
{
  int upper_bound = getVertexNum() - ceil((getVertexNum()-1) / getMaxDegree());
  vector<vector<int> > results;
  vector<vector<int> > p;
  bool found = false;

  for (int i = upper_bound; i >= 1 && !found; i--)
  {
    p = enumerate(i);
    for (int j = 0; j < p.size(); j++)
    {
      if (isIndependentSet(p[j]))
      {
        results.push_back(p[j]);
        found = true;
      }
    }
  }

  return results;
}

// ------------------------------------------------------------------------
// isIndependentSet: checks if set is an independent set of this graph
// returns a bool
// ------------------------------------------------------------------------
bool Graph::isIndependentSet(vector<int> set)
{
  for (int v = 0; v < set.size(); v++)
  {
    for (int n = 0; n < graphSet.vertexSet[set[v]].getNeighbors().size(); n++)
    {
      if (Tools::isInSet(set, graphSet.vertexSet[set[v]].getNeighbors()[n]))
        return false;
    }
  }
  return true;
}

// ------------------------------------------------------------------------
// Accessors: Various accessors to member variables, this is ugly
// ------------------------------------------------------------------------
int Graph::getEdgeNum() const { return graphSet.edgeSet.size(); }
int Graph::getVertexNum() const { return graphSet.vertexSet.size(); }
vector<int> Graph::getSequence() const { return degreeSequence; }
string Graph::getDegreeSequenceAsString() const
{
  return Tools::getVectorAsString(degreeSequence, graphSet.vertexSet.size());
}
string Graph::getEdgeSetAsString(vector<Edge> edgeSet) const
{
  stringstream ss;
  for (int e = 0; e < edgeSet.size(); e++)
  {
    stringstream f_mem;
    f_mem << edgeSet[e].toString();
    if (ss.str().size() + f_mem.str().size() >= 60 * (ss.str().size() / 60 + 1))
      ss << endl;
    ss << edgeSet[e].toString();
    if (e < edgeSet.size() - 1) // don't put a space at the end
      ss << " ";
  }
  return ss.str();
}
string Graph::getVertexSetAsString(vector<Vertex> vertexSet) const
{
  vector<int> v;
  for (int i = 0; i < vertexSet.size(); i++)
    v.push_back(vertexSet[i].getId());
  return Tools::getVectorAsString(v, vertexSet.size());
}
string Graph::getGraphInformation() const
{
  stringstream ss;

  // Trivial graph information
  ss << endl
     << "-------------------------------------------------" << endl
     << "                Graph Information                " << endl
     << "-------------------------------------------------" << endl
     << "Order: " << getVertexNum() << endl
     << "Edges: " << getEdgeNum() << endl
     << "Vertex Set: " << getVertexSetAsString(graphSet.vertexSet) << endl
     << "Edge Set: " << getEdgeSetAsString(graphSet.edgeSet) << endl
     << "Degree Sequence: " << getDegreeSequenceAsString() << endl
     << "Maximum Degree: " << getMaxDegree() << endl
     << "Minimum Degree: " << getMinDegree() << endl
     << "Average Degree: " << getAverageDegree()
     << endl;

  return ss.str();
}
int Graph::getMaxDegree() const
{
  return Tools::findMax(degreeSequence, graphSet.vertexSet.size());
}
int Graph::getMinDegree() const
{
  return Tools::findMin(degreeSequence, graphSet.vertexSet.size());
}
int Graph::getAverageDegree() const
{
  return Tools::findAverage(degreeSequence, graphSet.vertexSet.size());
}
