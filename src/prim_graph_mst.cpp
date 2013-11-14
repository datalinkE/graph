#include <queue>
#include <cassert>
#include "prim_graph_mst.h"

class EdgeWithPriority
// helper class to use graph eges in priority queue
{
public:
    double weight;
    Graph::EdgeKey key;

    EdgeWithPriority(int x, int y, const Graph& graph)
    {
        weight = graph.distance(x, y);
        assert(weight >= 0);
        key = Graph::makeEdgeKey(x, y);
    }

    bool operator<(const EdgeWithPriority& other) const
    // such behavior is needed to use this type in std::priority queue
    // where top element is always max element and wee need to retrieve
    // edge with the lowest weight
    {
        return weight >= other.weight;
    }
};

class PrimGraphMstImplementation
{
//actual implementation of Prim's algorithm
public:
    PrimGraphMstImplementation(const Graph& graph)  :
        graph(graph),
        summaryWeight(0)
      // we do all the work here in constructor
      // we assume that graph is connected
    {
        assert(graph.verticesCount() > 0);
        visitVertex(0);

        while(!pq.empty() && visited.size() < graph.verticesCount())
        {
            EdgeWithPriority element = pq.top();
            pq.pop();

            if(visited.find(element.key.first) == visited.end())
            {
                edges.push_back(element.key);
                summaryWeight += element.weight;
                visitVertex(element.key.first);
            }
            else if (visited.find(element.key.second) == visited.end())
            {
                edges.push_back(element.key);
                summaryWeight += element.weight;
                visitVertex(element.key.second);
            }
            else
            {
                continue;
            }
        }
    }

    void visitVertex(size_t index)
    // helper method marks vertex as visited and adds all it's
    // edges to priority queue
    {
        visited.insert(index);
        for(size_t other : graph.getVertexNeighbors(index))
        {
            pq.push(EdgeWithPriority(index, other, graph));
        }
    }

    bool valid() const
    // it could be wrong if given graph was not connected
    {
        return visited.size() == graph.verticesCount();
    }


    const Graph& graph;
    double summaryWeight;
    std::list<Graph::EdgeKey> edges;

private:
    std::priority_queue<EdgeWithPriority> pq;
    std::set<size_t> visited;
};

PrimGraphMst::PrimGraphMst(const Graph& graph)
{
    impl = std::make_shared<PrimGraphMstImplementation>(graph);
}

const std::list<Graph::EdgeKey>& PrimGraphMst::edges()
{
    return impl->edges;
}

bool PrimGraphMst::valid() const
{
    return impl->valid();
}

double PrimGraphMst::weight() const
{
    return impl->summaryWeight;
}

Graph* PrimGraphMst::makeTreeGraph()
{
    if(!valid())
        return nullptr;

    Graph* result = new Graph(impl->graph.verticesCount());
    for(Graph::EdgeKey element : impl->edges)
    {
        double weight = impl->graph.distance(element.first, element.second);
        result->connect(element.first, element.second, weight);
    }

    return result;
}
