/*******************************************************************************
 * Vertex.cpp
 *
 * Tanner G, Jeff Y, Micah J, Mitchell O
 * 4/6/2016
 * Discrete Mathematics I Project
 *
 * An object that represents a Vertex in a Discrete Graph. This object does
 * not print to the console.
 *
*******************************************************************************/

#include "Vertex.h"
#include <iostream>

// ------------------------------------------------------------------------
// Vertex: Default constructor, creates a vertex with 0 degree and -1 id
// ------------------------------------------------------------------------
Vertex::Vertex()
{
  id = -1;
  color = 0;
}

// ------------------------------------------------------------------------
// Vertex: Creates a vertex with the specified id and degree
// d: degree
// i: id
// ------------------------------------------------------------------------
Vertex::Vertex(int i)
{
  id = i;
  color = 0;
}

// ------------------------------------------------------------------------
// Mutators: Functions that change class members
// ------------------------------------------------------------------------
void Vertex::setId(int i) { id = i; }
void Vertex::addNeighbor(int v) { neighbors.push_back(v); }
void Vertex::setColor(int c) { color = c; }

// ------------------------------------------------------------------------
// Accessors: Functions that access class members
// ------------------------------------------------------------------------
int Vertex::getDegree() const { return neighbors.size(); }
int Vertex::getId() const { return id; }
int Vertex::getColor() const { return color; }
std::vector<int> Vertex::getNeighbors() const { return neighbors; }

// ------------------------------------------------------------------------
// Operators: Overloaded operators
// ------------------------------------------------------------------------
bool Vertex::operator==(const Vertex &rhs)
{
  return (id == rhs.id && color == rhs.color);
}
