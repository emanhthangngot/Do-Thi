
//
// Template for Homework 4 - Single-Source Shortest Path.
//
// Description:
// In this homework, you're asked to implement Dijkstra's Algorithm to find the
// Shortest Path between a pair of vertices in an directed/undirected graph.
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
// 2 0 1.


// 1 1 0
// 0 1
//
// where
// - 1st line: an integer n -- total vertices in the graph.
// - Next n lines, each line consists of n integers.
//   (Please have a look at the definition of adjacency matrix in
//   undirected graphs.)
// - Last line: a pair of integers u and v -- the starting and ending vertices
// of the path.
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
// Last updated: Dec 19, 2024.
//

#include <cassert>
#include <climits>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define ADJ_MATRIX vector<vector<int>>

// Predefined prototypes

/**
 * @brief Read a given graph's adjacency matrix from stdin (i.e. using cin).
 *
 * @param n total vertices of the graph.
 * @return vector<vector<int>> The adjacency matrix of the given graph.
 */
ADJ_MATRIX readAdjacencyMatrix(int &);

/**
 * @brief Dijkstra's algorithm to find the Shortest Path between a pair of
 * vertices.
 *
 * @param matrix the adjacency matrix of the graph.
 * @param start the starting vertex.
 * @param end the target vertex.
 * @param trace saving traveled vertices.
 * @return int minimum length of the path.
 */
int Dijkstra(const ADJ_MATRIX &, int, int, vector<int> &);

// ------------------------------------------------
// DO NOT MODIFY CODE INSIDE THIS ZONE

/**
 * @brief Print a given trace vector.
 *
 * 
 * 
 * @param end the ending vertex of the path.
 * @param trace Given trace vector.
 */
void printTrace(int end, const vector<int> &trace)
{
    stack<int> s;
    s.push(end);

    int current = end;
    while (trace[current] != -1)
    {
        s.push(trace[current]);
        current = trace[current];
    }

    while (s.size() > 1)
    {
        cout << s.top() << " -> ";
        s.pop();
    }

    cout << s.top();
}

// ------------------------------------------------

ADJ_MATRIX readAdjacencyMatrix(int &n)
{
    cin >> n;
    ADJ_MATRIX matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

int Dijkstra(const ADJ_MATRIX &matrix, int start, int end, vector<int> &trace)
{
    int n = matrix.size();
    vector<long long> D(n, INT_MAX);
    vector<bool> P(n, false);

    D[start] = 0;
    trace[start] = -1;

    for (int i = 0; i < n; ++i)
    {
        int uBest = -1;
        long long Min = INT_MAX;

        // Tìm đỉnh chưa sử dụng có khoảng cách nhỏ nhất
        for (int u = 0; u < n; ++u)
        {
            if (!P[u] && D[u] < Min)
            {
                Min = D[u];
                uBest = u;
            }
        }

        if (uBest == -1)
            break; // Không còn đỉnh nào để duyệt

        P[uBest] = true;

        // Cập nhật khoảng cách cho các đỉnh kề
        for (int v = 0; v < n; ++v)
        {
            if (matrix[uBest][v] > 0 && !P[v])
            {
                long long w = matrix[uBest][v];
                if (D[v] > D[uBest] + w)
                {
                    D[v] = D[uBest] + w;
                    trace[v] = uBest;
                }
            }
        }
    }

    return (D[end] == INT_MAX) ? -1 : D[end];
}

// ------------------------------------------------

int main()
{
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);

    int n; // n = total vertices of the given graph.
    ADJ_MATRIX graph = readAdjacencyMatrix(n);

    // Starting vertex of the Prim's algorithm.
    int start, end;
    cin >> start >> end;

    // Make sure that you've read the matrix successfully.
    assert(graph.size() == n);
    assert(graph[0].size() == n);

    vector<int> trace(n, -1);
    int minPathLength = Dijkstra(graph, start, end, trace);

    // Finding shortest path
    cout << "Shortest path's length: " << minPathLength << "\n";
    cout << "Trace: " << "\n";
    printTrace(end, trace);

    return 0;
}