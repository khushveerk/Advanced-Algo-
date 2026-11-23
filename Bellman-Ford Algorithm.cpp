# To find the shortest paths from a given source vertex to all other vertices in a weighted graph.


#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
    int u, v, weight;
};

int main()
{
    int V, E;

    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].u >> edges[i].v
            >> edges[i].weight;
    }

    int source;

    cout << "Enter source vertex: ";
    cin >> source;

    const int INF = 1000000000;

    vector<int> dist(V, INF);
    dist[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i < V; i++)
    {
        bool updated = false;

        for (Edge e : edges)
        {
            if (dist[e.u] != INF &&
                dist[e.u] + e.weight < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.weight;
                updated = true;
            }
        }

        if (!updated)
            break;
    }

    // Check for negative weight cycle
    for (Edge e : edges)
    {
        if (dist[e.u] != INF &&
            dist[e.u] + e.weight < dist[e.v])
        {
            cout << "Negative weight cycle detected!";
            return 0;
        }
    }

    cout << "\nShortest distances from source "
         << source << ":\n";

    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " : ";

        if (dist[i] == INF)
            cout << "INF";
        else
            cout << dist[i];

        cout << endl;
    }

    return 0;
}

/**
Enter number of vertices and edges: 5 8

Enter edges (u v weight):
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3

Enter source vertex: 0

Shortest distances from source 0:
Vertex 0 : 0
Vertex 1 : -1
Vertex 2 : 2
Vertex 3 : -2
Vertex 4 : 1
  **/

