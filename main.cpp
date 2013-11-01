#include <iostream>
#include "graph.h"
#include "dejkstra_graph_path.h"

using namespace std;

const int VERTICE_COUNT = 3;

int main()
{
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
    return 0;
}

