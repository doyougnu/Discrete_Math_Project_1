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

void printAlgorithms();
void printSets(vector<vector<int> >, bool, int);

void printSets(vector<vector<int> > sets, bool forwards, int limit)
{
  if (sets.size() > 1)
    cout << sets.size() << " Sets" << endl;
  else
    cout << "Set" << endl;
  int s = limit;
  if (sets.size() <= limit)
    s = sets.size();
  if (forwards)
    {
      for (int i = 0; i < s; i++)
        {
          for (int j = 0; j < sets[i].size(); j++)
            {
              cout << sets[i][j] << " ";
            }
          cout << endl;
        }
    }
  else
    {
      for (int i = s-1; i >= 0; i--)
        {
          for (int j = 0; j < sets[i].size(); j++)
            {
              cout << sets[i][j] << " ";
            }
          cout << endl;
        }
    }
  if (sets.size() > s)
    cout << endl << sets.size() - s << " sets not shown" << endl;
}

// ------------------------------------------------------------------------
// printAlgorithms: Prints a list of algorithms and functions
// graph: used to check if either a sequence or matrix was loaded
// ------------------------------------------------------------------------
void printAlgorithms()
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
       << "4. Find minimum forcing sets and zero forcing number" << endl
       << "5. Find maximum independent sets and independence number" << endl
       << "6. Find maximum cliques and clique number" << endl
       << "7. Find the chromatic number" << endl
       << "8. Find minimum dominating sets and domination number" << endl
       << "9. Find total domination stuff?" << endl
       << "10. Show available Algorithms" << endl
       << "11. Show trivial Graph information" << endl;
}

int main (int argc, char *argv[], char *envp[])
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
       << "Enter graph filename (with extension): ";

  // stupid error checking section
  if (argc < 2)
  {
    if (!(cin >> file_name)) // Error checker
    {
      cout << "Error 101: Invalid input" << endl;
      return 101; // invalid input
    }
  }
  else
  {
    file_name = argv[1];
    cout << file_name << endl;
  }

  // get type
  string type = file_name.substr(file_name.size()-2, file_name.size()-1);

  file_name = graph_folder.append(file_name);

  // Try to open the file
  in_file.open(file_name.c_str());
  if (!in_file) // Check to make sure the file exists/opened
  {
    cout << endl << "Error 404: File \"" << file_name << "\" does not exist!"
         << endl;
    return 404; // haha
  }

  // Ok now we load stuff
  cout << endl << "Loading graph...";
  Graph graph(in_file, type.substr(0, type.size()));

  // Error better checkings
  if (graph.getVertexNum() == 0 || graph.getEdgeNum() == 0)
    return 122;

  // Print important info
  cout << graph.getGraphInformation();

  while (running)
  {
    printAlgorithms();
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
          vector<vector<int> > zgs = graph.findZeroForcingSets(0);
          cout << "Z(G) = " << zgs[0].size() << endl << endl;
          printSets(zgs, true, 10);
          break;
        }
        case 5:
        {
          vector<vector<int> > mis = graph.findMaximumIndependentSets(0);
          cout << "alpha(G) = " << mis[0].size() << endl << endl;
          printSets(mis, true, 10);
          break;
        }
        case 6:
        {
          vector<vector<int> > mc = graph.findMaximalCliques();
          cout << "omega(G) = " << mc[mc.size()-1].size() << endl << endl;
          printSets(mc, false, 10);
          break;
        }
        case 7:
        {
          cout << "Look! A chromatic number!" << endl;
          graph.welshPowell();
          cout << "its right here: " << graph.getChromaticNumber() << endl;
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
          printAlgorithms();
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
