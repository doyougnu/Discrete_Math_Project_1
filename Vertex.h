/*******************************************************************************
 * Vertex.h
 *
 * Tanner Gower, put, your, names, here
 * 4/6/2016
 * Discrete Mathematics I Project
 *
 * An object that represents a Vertex in a Discrete Graph. This object does
 * not print to the console.
 *
*******************************************************************************/
#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
  public:
    Vertex();
    Vertex(int, int);

    // Mutators
    void setId(int);
    void setDegree(int);
    void incrementDegree();
    void decrementDegree();

    // Accessors
    int getDegree() const;
    int getId() const;

  private:
    int degree,
        id; // id could just be the index in the vector<int>, idk
};

#endif // VERTEX_H
