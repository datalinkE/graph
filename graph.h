#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <memory>

class GraphImplementation;

class Graph
// My declaration of an undirected weighted graph.
// It operates only on vertex numbers so associated objects should be stored elsewhere.
// Good choise is to use vector<shared_ptr<ObjectClass>> as an external storage.
// All functions that take two vertex indeces are symmetric:
// calls like some_function( index1, index2 ) and some_function( index2, index1) are equivalent.
{
public:
    Graph(size_t capacity);
    // constructor reservers space for selected capacity

    size_t verticesCount() const;
    // returns the number of vertices in the graph

    size_t edgesCount() const;
    // returns the number of edges in the graph

    int distance(size_t x, size_t y) const;
    // returns non-negative value (weight) if there is an edge from node x to node y or -1 otherwise

    void connect(size_t x, size_t y, int weight = 0);
    // adds the edge from x to y into the graph, or sets new weight to existing edge


    void disconnect(size_t x, size_t y);
    // removes the edge from x to y from the graph, if it is there

    std::set<size_t> getVertexNeighbors(size_t index) const;
    // lists all nodes y such that there is an edge from x to y.

private:
    std::shared_ptr<GraphImplementation> impl;
};

std::ostream& operator<< (std::ostream& stream, const Graph& G);
// prints out the graph as a list of edges grouped by vertices

#endif // GRAPH_H
