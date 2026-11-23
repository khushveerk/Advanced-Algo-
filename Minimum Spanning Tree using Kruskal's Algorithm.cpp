# To determine the Minimum Spanning Tree (MST) of a graph using Kruskal's Algorithm.


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
};

// Find parent of a node
int findParent(vector<int>& parent, int node)
{
    if (parent[node] == node)
        return node;

    return parent[node] = findParent(parent, parent[node]);
}

// Combine two sets
void unionSet(vector<int>& parent, vector<int>& rank,
              int u, int v)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v])
        parent[u] = v;

    else if (rank[u] > rank[v])
        parent[v] = u;

    else
    {
        parent[v] = u;
        rank[u]++;
    }
}

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

    // Sort edges by weight
    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b)
         {
             return a.weight < b.weight;
         });

    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int totalWeight = 0;
    int count = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (Edge e : edges)
    {
        int u = findParent(parent, e.u);
        int v = findParent(parent, e.v);

        // Include edge only if it forms no cycle
        if (u != v)
        {
            cout << e.u << " - " << e.v
                 << " : " << e.weight << endl;

            totalWeight += e.weight;
            unionSet(parent, rank, u, v);

            count++;

            if (count == V - 1)
                break;
        }
    }

    if (count != V - 1)
        cout << "MST does not exist. Graph is disconnected.\n";
    else
        cout << "Total MST weight: " << totalWeight;

    return 0;
}

/**
Enter number of vertices and edges: 4 5

Enter edges (u v weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

Edges in Minimum Spanning Tree:
2 - 3 : 4
0 - 3 : 5
0 - 1 : 10

Total MST weight: 19
  **/
