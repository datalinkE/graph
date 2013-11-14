#include <list>
#include <queue>
#include "dijkstra_graph_path.h"

class PathWithPriority
// helper class to represent some of the possible pathes as a list of vertex indeces
{
public:
    double priority;
    std::list<size_t> vertices;

    bool operator<(const PathWithPriority& other) const
    // such behavior is needed to use this type in std::priority queue
    // where top element is always max element and wee need to retrieve
    // path with the lowest priority
    {
        return priority >= other.priority;
    }

    PathWithPriority(size_t start) :
        priority(0)
    {
        vertices.push_back(start);
    }

    PathWithPriority(const PathWithPriority& path, size_t next_vertex, double weight) :
    // creates new path from some existing (non-final) path
        priority(path.priority + weight)
    {
       vertices = path.vertices;
       vertices.push_back(next_vertex);
    }
};

class DijkstraGraphPathImplementation
// this class uses priority queue to find the shortest path
// and then holds obtained result as a list of vertex indeces and summary weight
{
public:
    DijkstraGraphPathImplementation(const Graph& graph, size_t x, size_t y) :
        weight(-1),
        _x(x),
        _y(y)
    // we do here all work on detecting path between vertices x and y in graph
    // using a kind of A* algorithm
    {
        std::priority_queue<PathWithPriority> pq;
        std::set<size_t> visited;

        pq.push(x);

        while(!pq.empty())
        {
            PathWithPriority element = pq.top();
            pq.pop();
            size_t index = *element.vertices.rbegin();
            visited.insert(index);
            if(y == index)
            {
                solvable = true;
                vertices = element.vertices;
                weight = element.priority;
            }
            else
            {
                for( int next_vertex : graph.getVertexNeighbors(index))
                {
                    auto ins_result = visited.insert(next_vertex);
                    if(!ins_result.second)  continue;

                    pq.push(PathWithPriority(element, next_vertex, graph.distance(index,next_vertex)));
                }
            }
        }
    }

    std::list<size_t> vertices;
    double weight;
    bool solvable;
    int _x, _y;
};

DijkstraGraphPath::DijkstraGraphPath(const Graph &graph, size_t x, size_t y)    :
    from(x),
    to(y)
{
    impl = std::make_shared<DijkstraGraphPathImplementation>(graph, x, y);
}

bool DijkstraGraphPath::exists() const
{
    return impl->solvable;
}

double DijkstraGraphPath::weight() const
{
    return impl->weight;
}

const std::list<size_t>& DijkstraGraphPath::vertices() const
{
    return impl->vertices;
}

std::ostream& operator<< (std::ostream& stream, const DijkstraGraphPath& gp)
{
    if(!gp.exists())
        stream << "No valid path between " << gp.from << " and " << gp.to << std::endl;
    else
    {
        stream << "Path " << gp.from << "->" << gp.to
               << " [weight " << gp.weight() << "] :" ;
        for(auto x : gp.vertices())
            stream << x << " ";
        stream << std::endl;
    }

    return stream;
}
