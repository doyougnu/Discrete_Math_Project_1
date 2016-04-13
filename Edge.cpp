/*******************************************************************************
 * Edge.cpp
 *
 * Tanner G, Jeff Y, Micah J, Mitchell O
 * 4/6/2016
 * Discrete Mathematics I Project
 *
 * An object that represents an Edge in a Discrete Graph. This object does
 * not print to the console.
 *
*******************************************************************************/

#include "Edge.h"
#include <sstream>

using namespace std;

// ------------------------------------------------------------------------
// Edge: Default constructor, creates an edge with no home
// ------------------------------------------------------------------------
Edge::Edge()
{
  weight = 0;
  from = -1;
  to = -1;
}

// ------------------------------------------------------------------------
// Edge: Creates an edge with the specified from, to and weight value
// f: from
// t: to
// w: weight
// ------------------------------------------------------------------------
Edge::Edge(int f, int t, int w)
{
  from = f;
  to = t;
  weight = w;
}

// ------------------------------------------------------------------------
// Mutators: Functions that change class members
// ------------------------------------------------------------------------
void Edge::setWeight(int w) { weight = w; }
void Edge::connectFrom(int f) { from = f; }
void Edge::connectTo(int t) { to = t; }

// ------------------------------------------------------------------------
// Accessors: Functions that access class members
// ------------------------------------------------------------------------
int Edge::getWeight() const { return weight; }
int Edge::getFrom() const { return from; }
int Edge::getTo() const { return to; }
string Edge::toString() const
{
  stringstream ss;
  ss << "(" << from << "," << to << "," << weight << ")";
  return ss.str();
}

// ------------------------------------------------------------------------
// Operators: Overloaded operators
// ------------------------------------------------------------------------
void Edge::operator=(const Edge &rhs)
{
  from = rhs.from;
  to = rhs.to;
  weight = rhs.weight;
}
bool Edge::operator==(const Edge &rhs)
{
  return (from == rhs.from && to == rhs.to && weight == rhs.weight);
}
