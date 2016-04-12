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

// ------------------------------------------------------------------------
// Vertex: Default constructor, creates a vertex with 0 degree and -1 id
// ------------------------------------------------------------------------
Vertex::Vertex()
{
  degree = 0;
  id = -1;
}

// ------------------------------------------------------------------------
// Vertex: Creates a vertex with the specified id and degree
// d: degree
// i: id
// ------------------------------------------------------------------------
Vertex::Vertex(int d, int i)
{
  degree = d;
  id = i;
}

// ------------------------------------------------------------------------
// Mutators: Functions that change class members
// ------------------------------------------------------------------------
void Vertex::setId(int i) { id = i; }
void Vertex::setDegree(int d) { degree = d; }
void Vertex::incrementDegree() { degree++; }
void Vertex::decrementDegree() { degree--; }

// ------------------------------------------------------------------------
// Accessors: Functions that access class members
// ------------------------------------------------------------------------
int Vertex::getDegree() const { return degree; }
int Vertex::getId() const { return id; }

// ------------------------------------------------------------------------
// Operators: Overloaded operators
// ------------------------------------------------------------------------
bool Vertex::operator==(const Vertex &rhs)
{
  return (degree == rhs.degree && id == rhs.id);
}
