/*******************************************************************************
 * Vertex.h
 *
 * Tanner G, Jeff Y, Micah J, Mitchell O
 * 4/6/2016
 * Discrete Mathematics I Project
 *
 * An object that represents a Vertex in a Discrete Graph. This object does
 * not print to the console.
 *
*******************************************************************************/
#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

class Vertex
{
  public:
    Vertex();
    Vertex(int);

    // Mutators
    void setId(int);
    void addNeighbor(int);
    void setColor(int);

    // Accessors
    int getDegree() const;
    std::vector<int> getNeighbors() const;
    int getId() const;
    int getColor() const;
    
    // Operators
    bool operator==(const Vertex &rhs);

  private:
    int id,
        color;
    std::vector<int> neighbors;
};

#endif // VERTEX_H
