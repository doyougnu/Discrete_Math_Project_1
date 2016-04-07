/*******************************************************************************
 * Edge.cpp
 *
 * Tanner Gower, put, your, names, here
 * 4/6/2016
 * Discrete Mathematics I Project
 *
 * An object that represents an Edge in a Discrete Graph. This object does
 * not print to the console.
 *
*******************************************************************************/

#include "Edge.h"

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
void Edge::connectTo() { to = t; }

// ------------------------------------------------------------------------
// Accessors: Functions that access class members
// ------------------------------------------------------------------------
int Edge::getWeight() { return weight; }
int Edge::getFrom() { return from; }
int Edge::getTo() { return to; }
