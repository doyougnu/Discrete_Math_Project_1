/*******************************************************************************
 * CommandLine.cpp
 *
 * Tanner G, Jeff Y, Micah J, Mitchell O
 * 2/23/2016
 * Discrete Mathematics I Project
 *
 * The user interface for the Graphs
 * This is ugly because it's just an interface file. The Graph file
 * will be able to be used in other C++ programs.
 *
*******************************************************************************/

#include "libs.h"
#include "Graph.h"
#include "Tools.h"

using namespace std;

void printAlgorithms(Graph);
void printSets(vector<vector<int> >);

int main ()
{
  bool running = true;
  ifstream in_file;
  string file_name;
  int option;
  string graph_folder = "graph_files/";

  cout << "------------------------------------------------------------" << endl
       << "                Discrete Mathematics Project" << endl
       << "                             by" << endl
       << "            Tanner G, Jeff Y, Micah J, Mitchell O" << endl
       << "------------------------------------------------------------" << endl
       << "Enter graph filename: ";

  // stupid error checking section
  if (!(cin >> file_name)) // Error checker
  {
    cout << "Error 101: Invalid input" << endl;
    return 101; // invalid input
  }

  // Try to open the file
  file_name = graph_folder.append(file_name);
  in_file.open(file_name.c_str());
  if (!in_file) // Check to make sure the file exists/opened
  {
    cout << endl << "Error 404: File \"" << file_name << "\" does not exist!"
         << endl;
    return 404; // haha
  }

  // get type
  string type;
  cout << "Enter graph file type (es, am): ";
  if (!(cin >> type))
  {
    cout << "Unrecognized type!" << endl;
    return 5;
  }

  // Ok now we load stuff
  cout << endl << "Loading graph...";
  Graph graph(in_file, type);

  // Error better checkings
  if (graph.getVertexNum() == 0 || graph.getEdgeNum() == 0)
    return 122;

  // Print important info
  cout << graph.getGraphInformation();
  printAlgorithms(graph);

  while (running)
  {
    cout << endl << "Enter a command: ";

    if (cin >> option)
    {
      switch (option)
      {
        case 0:
        {
          running = false;
          break;
        }
        case 1:
        {
          cout << endl << "Havel-Hakimi Algorithm" << endl;
          vector<int> elim_seq = graph.findKResElimSeq(true);
          if (elim_seq[graph.getVertexNum()] != -1)
          {
            cout << endl
                 << "R(G) = " << elim_seq[graph.getVertexNum()] << endl
                 << "E(D) = "
                 << Tools::getVectorAsString(elim_seq, graph.getVertexNum())
                 << endl;
          }
          else
          {
            cout << "Sequence is not graphic." << endl;
          }
          break;
        }
        case 2:
        {
          cout << "a(G) = " << graph.findAnnihilationNumber() << endl;
          break;
        }
        case 3:
        {
          cout << endl << "Prim's Algorithm" << endl;
          Graph::GraphSet result = graph.findMinimumSpanningTree(0, true);
          if (graph.isSpanningTree(result))
            cout << "Success! Found minimum spanning tree."  << endl << endl;
          else
            cout << "Failed! Could not find minimum spanning tree." << endl
                 << endl;

          cout << "V(H) = { "
               << graph.getVertexSetAsString(result.vertexSet) << "}" << endl
               << "E(H) = { "
               << graph.getEdgeSetAsString(result.edgeSet) << " }" << endl;
          break;
        }
        case 4:
        {
          vector<vector<int> > zgs = graph.findZeroForcingSets();
          cout << "Z(G) = " << zgs[0].size() << endl << endl;
          printSets(zgs);
          break;
        }
        case 5:
        {
          vector<vector<int> > mis = graph.findMaximumIndependentSets();
          cout << "alpha(G) = " << mis[0].size() << endl << endl;
          printSets(mis);
          break;
        }
        case 6:
        {
          cout << "Look! A clique number!" << endl;
          break;
        }
        case 7:
        {
          cout << "Look! A chromatic number!" << endl;
          break;
        }
        case 8:
        {
          cout << "Look! A domination number!" << endl;
          break;
        }
        case 9:
        {
          cout << "Look! A total domination number stuff!" << endl;
          break;
        }
        case 10:
        {
          printAlgorithms(graph);
          break;
        }
        case 11:
        {
          cout << graph.getGraphInformation();
          break;
        }
        case 101: // testing stuff
        {
          vector<int> fs;
          int id = 0;
          cout << "Enter up to " << graph.getVertexNum()
               << " vertices from 0 to " << graph.getVertexNum() - 1
               << " (enter -1 to start): " << endl;
          cin >> id;
          while (id != -1)
          {
            fs.push_back(id);
            cin >> id;
          }
          if (graph.isIndependentSet(fs))
            cout << "Yes!" << endl;
          else
            cout << "No!" << endl;
          break;
        }
        default:
          cout << "\"" << option << "\" is not currently programmed." << endl;
          break;
      }
    }
    else
      return -1;

  }

  return 0;
}

// ------------------------------------------------------------------------
// printAlgorithms: Prints a list of algorithms and functions
// graph: used to check if either a sequence or matrix was loaded
// ------------------------------------------------------------------------
void printAlgorithms(Graph graph)
{
  // Header
  cout << endl
       << "----------------------------------------" << endl
       << "        Algorithms and Functions        " << endl
       << "----------------------------------------" << endl
       << "0. Close program" << endl
       << "1. Find and print residue of the graph and elimination "
       << "sequence" << endl
       << "2. Find and print the annihilation number" << endl
       << "3. Find and print the minimum spanning tree" << endl
       << "4. Find all minimum forcing sets and zero forcing number" << endl
       << "5. Find all maximum independent sets and independence number" << endl
       << "6. Find all maximum cliques and clique number" << endl
       << "7. Find the chromatic number" << endl
       << "8. Find all minimum dominating sets and domination number" << endl
       << "9. Find total domination stuff?" << endl
       << "10. Show available Algorithms" << endl
       << "11. Show trivial Graph information" << endl;
}

void printSets(vector<vector<int> > sets)
{
  if (sets.size() > 1)
    cout << sets.size() << " Sets" << endl;
  else
    cout << "Set" << endl;
  for (int i = 0; i < sets.size(); i++)
  {
    for (int j = 0; j < sets[i].size(); j++)
    {
      cout << sets[i][j] << " ";
    }
    cout << endl;
  }
}
