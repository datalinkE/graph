#ifndef PRIM_GRAPH_MST_H
#define PRIM_GRAPH_MST_H

#include <list>
#include "graph.h"

class PrimGraphMstImplementation;

class PrimGraphMst
// class that should find minimum spanning tree (MST) for the given graph
// and then store obtained result as a list of edges and summary weight
{
public:
    PrimGraphMst(const Graph&);
    // all work is actualy done in constructor
    // then we hold obtained result in some immutable fields

    const std::list<Graph::EdgeKey>& edges();
    // returns a list of edges from the given graph that forms MST

    int weight() const;
    // returns MST summary weight

    bool valid() const;
    // checks if obtained mst contains same number of vertices as the given graph
    // it could be wrong if the given graph was not connected

    Graph* makeTreeGraph();
    // construct new graph that have only edges from our MST

private:
    std::shared_ptr<PrimGraphMstImplementation> impl;
};

#endif // PRIM_GRAPH_MST_H
