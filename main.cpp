#include <iostream>
#include <cstdlib>
#include <ctime>
#include "graph.h"
#include "dejkstra_graph_path.h"

using namespace std;

void basic_use()
// this function gives a simple and straightforward example
// of how graph classes API should work
// each vertex-associated object is stored with a smart pointer
// its could look odd in this basic example but should be extremaly usefull
// in real code were graph vertices are associated with some complex data structures
{
    const int VERTICE_COUNT = 3;

    Graph<int> G(VERTICE_COUNT);
    for(int i = 0; i < VERTICE_COUNT; i++)
    {
        G.addVertex( ::make_shared<int>(i) );
    }
    for(int i = 1; i < VERTICE_COUNT; i++)
    {
        G.connect(0, i, i);
    }
    ::cout << G;

    ::cout << DejkstraGraphPath<int>(G, 0, 1);
}

void simulation(int node_count, double edge_density, int weight_limit)
// we use Monte Carlo simulation with sertain parameters to produce a graph
// with node_count vertices each of which have edge_density * (node_count - 1) neighbors
// each graph eadge have its weight between 1 and weight_limit
// when graph is created we search for the multiple paths:
// 0 to 1, 0 to 2, 0 to 3, 0 to 4, …, 0 to (node_count-1) and compute average path weight value
{
    ::cout << "Simulation for "
           << node_count << " nodes "
           << edge_density << " dencity and "
           << weight_limit << " max edge weight" << ::endl << ::endl;

    Graph<int> G(node_count);
    for(int i = 0; i < node_count; i++)
    {
        G.addVertex( ::make_shared<int>(i) );
    }

    ::srand(::time(NULL));

    for(int i = 0; i < node_count; i++)
        for(int j = i+1; j < node_count; j++)
        {
            double roll = static_cast<double>(::rand()) / RAND_MAX;
            if(roll < edge_density)
            {
                int weight = ::rand() % weight_limit + 1;
                G.connect(i, j, weight);
            }
        }

    ::cout << G << ::endl;
    ::cout << "Finding pathes..." << ::endl << ::endl;

    int pathes_summ = 0;
    int pathes_count = node_count - 1;
    for(int i = 1; i < node_count; i++)
    {
        DejkstraGraphPath<int> path(G, 0, i);
        if(path.solvable)
            pathes_summ += path.weight;
        else
            pathes_count--;

        ::cout << path;
    }
    ::cout << "Average path length is " << pathes_summ / pathes_count << ::endl;
}

void something_wrong()
// replace standard terminate handler to set breakpoint here
// for debugging purpose
{
    ::cout << "bang!" << ::endl;
    ::abort();
}

int main()
{
    // programm output is massive, redirect to file for better experience
    ::set_terminate(something_wrong);

    ::cout << "Part 1" << ::endl;
    simulation(50, 0.2, 10);

    ::cout << "Part 2" << ::endl;
    simulation(50, 0.4, 10);
    return 0;
}

