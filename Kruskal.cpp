#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define ADJ_MATRIX vector<vector<int>>
#define EDGES_LIST map<pair<int, int>, int>

int find(int parent[], int x)
{
    if (parent[x] != x)
        parent[x] = find(parent, parent[x]);
    return parent[x];
}

bool unionSets(int parent[], int rank[], int x, int y)
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX == rootY)
        return false;

    if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    return true;
}

ADJ_MATRIX readAdjacencyMatrix(int &);
EDGES_LIST Kruskal(const ADJ_MATRIX &);

void printEdgesList(const EDGES_LIST &l)
{
    for (const auto &i : l)
    {
        pair<int, int> edge = i.first;
        cout << "( " << edge.first << ", " << edge.second << ") = " << i.second
             << "\n";
    }
}

ADJ_MATRIX readAdjacencyMatrix(int &n)
{
    cin >> n;
    ADJ_MATRIX matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

EDGES_LIST Kruskal(const ADJ_MATRIX &graph)
{
    int n = graph.size();
    vector<pair<int, pair<int, int>>> edges;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (graph[i][j] > 0)
            {
                edges.push_back({graph[i][j], {i, j}});
            }
        }
    }

    sort(edges.begin(), edges.end());

    int parent[n], rank[n];
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    EDGES_LIST mstEdges;
    int edgesFound = 0;

    for (const auto &edge : edges)
    {
        int weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if (unionSets(parent, rank, u, v))
        {
            mstEdges[{min(u, v), max(u, v)}] = weight;
            edgesFound++;
            if (edgesFound == n - 1)
                break;
        }
    }

    if (edgesFound != n - 1)
    {
        cerr << "Graph is disconnected. Partial MST found with " << edgesFound << " edges." << endl;
    }

    return mstEdges;
}

int main()
{
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);

    int n;
    ADJ_MATRIX graph = readAdjacencyMatrix(n);

    assert(graph.size() == n);
    assert(graph[0].size() == n);

    EDGES_LIST el = Kruskal(graph);

    assert(el.size() == n - 1);
    cout << "MST found with Kruskal's algorithm:\n";
    printEdgesList(el);

    return 0;
}
