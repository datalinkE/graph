#ifndef DIJKSTRA_GRAPH_PATH_H
#define DIJKSTRA_GRAPH_PATH_H

#include <list>
#include <memory>
#include "graph.h"

class DijkstraGraphPathImplementation;

class DijkstraGraphPath
// class that should find the shortest path in the graph
// and then hold obtained result as a list of vertex indeces and summary weight
{
public:
    DijkstraGraphPath(const Graph& graph, size_t x, size_t y);
    // constructor sets all input data for searching the path and do actual work
    // then it holds obtained result in some immutable fields

    const size_t from, to;
    // store start/end vertices of desired path

    bool exists() const;
    // indicates if path between desired vertices exists in the graph

    const std::list<size_t>& vertices() const;
    // if the path exists this field holds corresponding vertex indeces

    int weight() const;
    // if the path exists returns path summary weight

private:
    std::shared_ptr<DijkstraGraphPathImplementation> impl;
};


std::ostream& operator<< (std::ostream& stream, const DijkstraGraphPath& gp);

#endif // DIJKSTRA_GRAPH_PATH_H
