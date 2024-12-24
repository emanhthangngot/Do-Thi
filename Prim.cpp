//
// Template for Homework 3 - MST.
//
// Description:
// In this homework, you're asked to implement Prim's Algorithm to find the Minimum Spanning Tree (MST)
// of an undirected graph.
//
// Grading:
// We'll test your code on several testcases, all would be load from input files
// (of course, we've implemented the pipeline for you).
//
// Input:
// The input file would follow this format:
//
// 3
// 0 2 1
// 2 0 1
// 1 1 0
// 1
//
// where
// - 1st line: an integer n -- total vertices in the graph.
// - Next n lines, each line consists of n integers.
//   (Please have a look at the definition of adjacency matrix in
//   undirected graphs.)
// - Last line: an integer k -- starting vertex of the Prim's algorithm
//
//
// Example: input_sample.txt
//
// Instructions:
// 1. Fill your code inside <// TODO: YOUR CODE HERE> zone.
// 2. You should NOT modify code inside <// DO NOT MODIFY CODE INSIDE THIS ZONE>
//    to prevent your code getting wrong answer from grader.
// 3. You can add additional functions to support your implementation,
//    but don't modify given prototypes.
// 4. You can modify the main() function to test your code,
//    but remember to restore it to the original version after finished.
//    We test your code with the original main() function, any modification
//    can results in your code getting wrong answer.
//
// Have fun!

// Last updated: Jul 24, 2024.
//

#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

#define ADJ_MATRIX vector<vector<int>>

// Note that we're using map<pair<int, int>, int> to represent an edges list,
// yet it's still somehow inefficient with O(log) for insertion & lookup.
#define EDGES_LIST map<pair<int, int>, int>

// Predefined prototypes

/**
 * @brief Read a given graph's adjacency matrix from stdin (i.e. using cin).
 *
 * @param n total vertices of the graph.
 * @return vector<vector<int>> The adjacency matrix of the given graph.
 */
ADJ_MATRIX readAdjacencyMatrix(int &);

/**
 * @brief Minimum Spanning Tree with Prim's Algorithm
 *
 * @param graph Given adjacency matrix of a graph.
 * @param startVertex Starting vertex.
 *
 * @return List of edges.
 */
EDGES_LIST Prim(const ADJ_MATRIX &, int);

// ------------------------------------------------
// DO NOT MODIFY CODE INSIDE THIS ZONE

/**
 * @brief Print a given Edges List.
 *
 * @param l Given edges list.
 */
void printEdgesList(const EDGES_LIST &l)
{
    for (const auto &i : l)
    {
        pair<int, int> edge = i.first;
        cout << "( " << edge.first << ", " << edge.second << ") = " << i.second
             << "\n";
    }
}

// ------------------------------------------------

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

// Note: to insert an edge of (u, v) = w where
// - u = first vertex
// - v = second vertex
// - w = the edge's weight
// - EDGES_LIST l
// Therefore l[{u, v}] = w;

EDGES_LIST Prim(const ADJ_MATRIX &graph, int startVertex)
{
    int n = graph.size();
    vector<bool> MSTSet(n, false);
    vector<int> minWeight(n, INT_MAX);
    vector<int> parent(n, -1);
    int edgesFound = 0; // Keep track of edges added to MST

    minWeight[startVertex] = 0;

    for (int count = 0; count < n - 1; count++)
    {
        int min = INT_MAX, u = -1;

        for (int i = 0; i < n; i++)
        {
            if (!MSTSet[i] && minWeight[i] < min)
            {
                min = minWeight[i];
                u = i;
            }
        }

        if (u == -1)
        {
            // No more reachable vertices, exit the loop.
            break; // Important change
        }

        MSTSet[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] > 0 && !MSTSet[v] && graph[u][v] < minWeight[v])
            {
                parent[v] = u;
                minWeight[v] = graph[u][v];
            }
        }
    }


    EDGES_LIST mstEdges;
    for (int i = 0; i < n; i++) // Iterate through all vertices
    {
        if (parent[i] != -1)
        {
            mstEdges[{min(parent[i], i), max(parent[i], i)}] = graph[parent[i]][i];
            edgesFound++; // Increment edges found
        }
    }

    if (edgesFound != n - 1 && edgesFound != 0)
    {
        cerr << "Graph is disconnected. Partial MST found with " << edgesFound << " edges." << endl;
    }

    return mstEdges;
}
// ------------------------------------------------

int main()
{
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);




    int n; // n = total vertices of the given graph.
    ADJ_MATRIX graph = readAdjacencyMatrix(n);

    // Starting vertex of the Prim's algorithm.
    int k;
    cin >> k;

    // Validate starting vertex
    if (k < 0 || k >= n)
    {
        cerr << "Invalid starting vertex!" << endl;
        return 1;
    }

    // Make sure that you've read the matrix successfully.
    assert(graph.size() == n);
    assert(graph[0].size() == n);

    EDGES_LIST el = Prim(graph, k);

    // Total edges in MST = n - 1;
    assert(el.size() == n - 1);
    cout << "MST found with Prim's algorithm:\n";
    printEdgesList(el);

    return 0;
}