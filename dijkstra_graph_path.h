#ifndef DIJKSTRA_GRAPH_PATH_H
#define DIJKSTRA_GRAPH_PATH_H

#include <list>
#include <queue>
#include "graph.cpp"

class PathWithPriority
// helper class to represent some of the possible pathes as a list of vertex indeces
{
public:
    int priority;
    std::list<int> vertices;

    bool operator<(const PathWithPriority& other) const
    // such behavior is needed to use this type in std::priority queue
    // where top element is always max element and wee need to retrieve
    // path with the lowest priority
    {
        return priority >= other.priority;
    }

    PathWithPriority(int start) :
        priority(0)
    {
        vertices.push_back(start);
    }

    PathWithPriority(const PathWithPriority& path, int next_vertex, int weight) :
    // creates new path from some existing (non-final) path
        priority(path.priority + weight)
    {
       vertices = path.vertices;
       vertices.push_back(next_vertex);
    }
};

class DijkstraGraphPath
// this class uses priority queue to find the shortest path
// and then holds obtained result as a list of vertex indeces and summary weight
{
public:
    DijkstraGraphPath(const Graph& graph, int x, int y) :
        weight(-1),
        _x(x),
        _y(y)
    // we do here all work on detecting path between vertices x and y in graph
    // using a kind of A* algorithm
    {
        std::priority_queue<PathWithPriority> pq;
        std::set<int> visited;

        pq.push(x);

        while(!pq.empty())
        {
            PathWithPriority element = pq.top();
            pq.pop();
            int index = *element.vertices.rbegin();
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

    std::list<int> vertices;
    int weight;
    bool solvable;
    int _x, _y;
};


std::ostream& operator<< (std::ostream& stream, const DijkstraGraphPath& gp)
{
    if(!gp.solvable)
        stream << "No valid path between " << gp._x << " and " << gp._y << std::endl;
    else
    {
        stream << "Path " << gp._x << "->" << gp._y
               << " [weight " << gp.weight << "] :" ;
        for(auto x : gp.vertices)
            stream << x << " ";
        stream << std::endl;
    }

    return stream;
}

#endif // DIJKSTRA_GRAPH_PATH_H
