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

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Graph.h"
#include "Tools.h"

using namespace std;

void printAlgorithms(Graph);

int main ()
{
  bool running = true;
  ifstream in_file;
  string file_name,
         option = "";

  cout << "------------------------------------------------------------" << endl
       << "                Discrete Mathematics Project" << endl
       << "                             by" << endl
       << "            Tanner G, Jeff Y, Micah J, Mitchell O" << endl
       << "------------------------------------------------------------" << endl
       << "Enter graph filename: ";

  // stupid error checking section
  if (!(cin >> file_name)) // Error hecker
  {
    cout << "Error 101: Invalid input" << endl;
    return 101; // invalid input
  }

  in_file.open(file_name.c_str());
  if (!in_file) // Check to make sure the file exists/opened
  {
    cout << endl << "Error 404: File \"" << file_name << "\" does not exist!"
         << endl;
    return 404; // haha
  }

  // Ok now we load stuff
  cout << endl << "Loading graph...";
  Graph graph(in_file);
  if (graph.isLoaded())
    cout << "Success!" << endl;
  else
    cout << "Failed!" << endl; // This is completely useless

  // Trivial graph information
  cout << endl
       << "-------------------------------------------------" << endl
       << "                Graph Information                " << endl
       << "-------------------------------------------------" << endl
       << "Order: " << graph.getVertexNum() << endl
       << "Edges: " << graph.getEdgeNum() << endl
       << "Degree Sequence: " << graph.getDegreeSequenceAsString() << endl
       << "Maximum Degree: " << graph.getMaxDegree() << endl
       << "Minimum Degree: " << graph.getMinDegree() << endl
       << "Average Degree: " << graph.getAverageDegree()
       << endl;

  printAlgorithms(graph);

  while (running)
  {
    cout << endl << "Enter a command: ";

    if (cin >> option)
    {
      if (option == "exit")
        running = false;
      else if (option == "algs")
      {
        printAlgorithms(graph);
      }
      else if (option == "rg")
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
          cout << "Sequence is not graphic." << endl; // shit's fucked
        }
      }
      else if (option == "ag")
        cout << "a(G) = " << graph.findAnnihilationNumber() << endl;
      else
        cout << "\"" << option << "\" is not currently programmed." << endl;
    }
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
       << "rg - Find and print residue of the graph and elimination "
       << "sequence" << endl
       << "ag - Find and print the annihilation number" << endl
       << "algs - Show available Algorithms" << endl
       << "exit - Close program" << endl;
}
