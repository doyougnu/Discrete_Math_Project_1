/*******************************************************************************
 * Edge.h
 *
 * Tanner G, Jeff Y, Micah J, Mitchell O
 * 4/6/2016
 * Discrete Mathematics I Project
 *
 * An object that represents an Edge in a Discrete Graph. This object does
 * not print to the console.
 *
*******************************************************************************/
#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge
{
  public:
    Edge();
    Edge(int, int, int);

    // Mutators
    void setWeight(int);
    void connectFrom(int);
    void connectTo(int);

    // Accessors
    int getWeight() const;
    int getFrom() const;
    int getTo() const;
    std::string toString() const;

    // Operators
    void operator=(const Edge &rhs);
    bool operator==(const Edge &rhs);

  private:
    int weight,
        from,
        to;
};

#endif // EDGE_H
