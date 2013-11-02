#ifndef DEJKSTRA_GRAPH_PATH_H
#define DEJKSTRA_GRAPH_PATH_H

#include <list>
#include <queue>

#include "graph.h"

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


template<class Vertex>
class DejkstraGraphPath
{
public:
    DejkstraGraphPath(const Graph<Vertex>& graph, int x, int y) :
        pathWeight(-1),
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
                shortestPath = element.vertices;
                pathWeight = element.priority;
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

    std::list<int> shortestPath;
    int pathWeight;
    bool solvable;
    int _x, _y;
};

template <class Vertex>
std::ostream& operator<< (std::ostream& stream, const DejkstraGraphPath<Vertex>& gp)
{
    if(!gp.solvable)
        stream << "No valid path between " << gp._x << " and " << gp._y << std::endl;
    else
    {
        stream << "Path: ";
        for(auto x : gp.shortestPath)
            stream << x << " ";
        stream << "weight = " << gp.pathWeight << std::endl;
    }

    return stream;
}

#endif // DEJKSTRA_GRAPH_PATH_H
