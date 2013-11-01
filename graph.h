#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <memory>


template<class Vertex>
class Graph
// My stl-based implementation of an undirected weighted graph.
// It operates only on vertex numbers and stores associated objects
// in vector<shared_ptr>. Each vertex caches its neighboring indeces as set<int>.
// Edges are tracked as map< pair<int,int>, int> - two vertex numbers to weight.
// All functions that take two vertex indeces are symmetric:
// calls like some_function( index1, index2 ) and some_function( index2, index1) are equivalent.
{
public:
    typedef std::pair<int, int> EdgeKey;
    typedef std::shared_ptr<Vertex> SpVertex;

    Graph(int capacity) :
    // constructor reservers space for selected capacity
        vertexNeighbors(capacity, std::set<int>())
    {
        vertices.reserve(capacity);
    }

    int verticesCount() const
    // returns the number of vertices in the graph
    {
        return vertices.size();
    }

    int edgesCount() const
    // returns the number of edges in the graph
    {
        return edges.size();
    }

    SpVertex getVertex(int index) const
    // pass out vertex associated with index
    {
        return vertices.at(index);
    }

    void addVertex(SpVertex sp)
    {
        vertices.push_back(sp);
    }

    int distance(int x, int y) const
    // returns non-negative value (weight) if there is an edge from node x to node y or -1 otherwise
    {
        vertices.at(x);
        vertices.at(y);
        // the code above should throw out_of_bounds if indeces are wrong
        auto iElement = edges.find(makeEdgeKey(x, y));
        if (iElement == edges.end())
            return -1;
        else
            return iElement->second;
    }

    void connect(int x, int y, int weight = 0)
    // adds to G the edge from x to y, or sets new weight to existing edge
    {
        vertices.at(x);
        vertices.at(y);
        // the code above should throw out_of_bounds if indeces are wrong
        edges.insert(std::make_pair(makeEdgeKey(x, y), weight));
        vertexNeighbors[x].insert(y);
        vertexNeighbors[y].insert(x);
    }

    void disconnect(int x, int y)
    // removes the edge from x to y, if it is there
    {
        vertices.at(x);
        vertices.at(y);
        // the code above should throw out_of_bounds if indeces are wrong
        edges.erase(makeEdgeKey(x, y));
        vertexNeighbors[x].erase(y);
        vertexNeighbors[y].erase(x);
    }


    std::set<int> getVertexNeighbors(int index) const
    // lists all nodes y such that there is an edge from x to y.
    {
        return vertexNeighbors.at(index);;
    }


private:
    std::map<const EdgeKey, int> edges;
    std::vector<SpVertex> vertices;
    std::vector<std::set<int>> vertexNeighbors;

    static const EdgeKey makeEdgeKey(int x, int y)
    // construct a two-value key where values are ordered
    {
        return (x > y) ?	std::make_pair(y, x) : std::make_pair(x, y);
    }
};

template <class Vertex>
std::ostream& operator<< (std::ostream& stream, const Graph<Vertex>& G)
{
    int v = G.verticesCount();
    int e = G.edgesCount();

    stream << "Graph with " << v << " vertices and " << e << " edges:" << std::endl;

    for(int i = 0; i < v; i++)
    {
        stream << "V(" << i << ") = " << *G.getVertex(i) << " : ";
        for(auto p : G.getVertexNeighbors(i))
        {
            stream << p << " ";
        }
        stream << std::endl;
    }
    return stream;
}


#endif // GRAPH_H
