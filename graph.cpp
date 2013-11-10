#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <memory>
#include <cassert>

#include "graph.h"

const Graph::EdgeKey Graph::makeEdgeKey(size_t x, size_t y)
// construct a two-value key where values are ordered
{
    return (x > y) ?	std::make_pair(y, x) : std::make_pair(x, y);
}

// non-public class that do the job

class GraphImplementation
// My stl-based implementation of an undirected weighted graph.
// It operates only on vertex numbers so associated objects should be stored elsewhere.
// Good choise is to use vector<shared_ptr<ObjectClass>> as external storage.
// Each vertex caches its neighboring indeces as set<int>.
// Edges are tracked as map< pair<int,int>, int> - two vertex numbers to weight.
// All functions that take two vertex indeces are symmetric:
// calls like some_function( index1, index2 ) and some_function( index2, index1) are equivalent.
{
public:

    GraphImplementation(size_t capacity) :
    // constructor reservers space for selected capacity
        size(capacity),
        vertexNeighbors(capacity, std::set<size_t>())
    {
    }

    int verticesCount() const
    // returns the number of vertices in the graph
    {
        return size;
    }

    int edgesCount() const
    // returns the number of edges in the graph
    {
        return edges.size();
    }

    int distance(size_t x, size_t y) const
    // returns non-negative value (weight) if there is an edge from node x to node y or -1 otherwise
    {
        assert(x < size && y < size);
        // the code above should fall if indeces are wrong
        auto iElement = edges.find(Graph::makeEdgeKey(x, y));
        if (iElement == edges.end())
            return -1;
        else
            return iElement->second;
    }

    void connect(size_t x, size_t y, double weight = 0)
    // adds to G the edge from x to y, or sets new weight to existing edge
    {
        assert(x < size && y < size);
        // the code above should fall if indeces are wrong
        edges.insert(std::make_pair(Graph::makeEdgeKey(x, y), weight));
        vertexNeighbors[x].insert(y);
        vertexNeighbors[y].insert(x);
    }

    void disconnect(size_t x, size_t y)
    // removes the edge from x to y, if it is there
    {
        assert(x < size && y < size);
        // the code above should fall if indeces are wrong
        edges.erase(Graph::makeEdgeKey(x, y));
        vertexNeighbors[x].erase(y);
        vertexNeighbors[y].erase(x);
    }

    std::set<size_t> getVertexNeighbors(size_t index) const
    // lists all nodes y such that there is an edge from x to y.
    {
        return vertexNeighbors.at(index);;
    }


private:
    size_t size;
    std::map<const Graph::EdgeKey, int> edges;
    std::vector<std::set<size_t>> vertexNeighbors;
};

std::ostream& operator<< (std::ostream& stream, const Graph& G)
{
    size_t v = G.verticesCount();
    size_t e = G.edgesCount();

    stream << "Graph with " << v << " vertices and " << e << " edges:" << std::endl;

    for(size_t i = 0; i < v; i++)
    {
        stream << "Edges(" << i << ") : ";
        for(auto p : G.getVertexNeighbors(i))
        {
            stream << p << "[" << G.distance(i, p) <<"] ";
        }
        stream << std::endl;
    }
    return stream;
}

// below goes an implementation of public Graph class

Graph::Graph(size_t capacity)
{
    impl = std::make_shared<GraphImplementation>(capacity);
}

Graph::Graph(std::istream& in)
{
    assert(in);
    size_t capacity;
    in >> capacity;
    impl = std::make_shared<GraphImplementation>(capacity);

    while(in)
    {
       size_t x, y;
       double weight;
       in >> x;
       if(!in)  break;
       in >> y;
       if(!in)  break;
       in >> weight;
       impl->connect(x, y, weight);
    }
}

size_t Graph::verticesCount() const
{
    return impl->verticesCount();
}

size_t Graph::edgesCount() const
{
    return impl->edgesCount();
}

double Graph::distance(size_t x, size_t y) const
{
    return impl->distance(x, y);
}

void Graph::connect(size_t x, size_t y, double weight)
{
    impl->connect(x, y, weight);
}

void Graph::disconnect(size_t x, size_t y)
{
    impl->disconnect(x, y);
}

std::set<size_t> Graph::getVertexNeighbors(size_t index) const
{
    return impl->getVertexNeighbors(index);
}
