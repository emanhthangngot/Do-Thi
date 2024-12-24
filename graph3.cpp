#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

vector<vector<int>> readAdjacencyMatrix(string fileName)
{
    ifstream input(fileName);
    if (!input)
    {
        cerr << "Khong the mo file: " << fileName << endl;
        exit(1);
    }
    int n;
    input >> n; // Số đỉnh
    vector<vector<int>> matrix(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            input >> matrix[i][j];

    return matrix;
}

// Hàm in ma trận kề
void printMatrix(vector<vector<int>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void findArticulationPoints(int u, vector<vector<int>> &matrix, vector<bool> &visited, vector<int> &discovery, vector<int> &low, vector<int> &parent, vector<bool> &isArticulation, int &time)
{
    visited[u] = true;
    discovery[u] = low[u] = ++time;
    int children = 0;

    for (int v = 0; v < matrix.size(); v++)
    {
        if (matrix[u][v] == 1) // Nếu có cạnh giữa u và v
        {
            if (!visited[v]) // Nếu v chưa được thăm
            {
                children++;
                parent[v] = u;
                findArticulationPoints(v, matrix, visited, discovery, low, parent, isArticulation, time);

                // Cập nhật low của u dựa trên low của con v
                low[u] = min(low[u], low[v]);

                // Kiểm tra điều kiện đỉnh khớp
                if (parent[u] == -1 && children > 1) // Trường hợp u là gốc và có nhiều hơn 1 cây con
                    isArticulation[u] = true;
                if (parent[u] != -1 && low[v] >= discovery[u]) // Trường hợp u không phải gốc
                    isArticulation[u] = true;
            }
            else if (v != parent[u]) // Nếu v là tổ tiên của u
            {
                low[u] = min(low[u], discovery[v]);
            }
        }
    }
}


void findBridges(int u, vector<vector<int>> &matrix, vector<bool> &visited, vector<int> &discovery, vector<int> &low, vector<int> &parent, vector<pair<int, int>> &bridges, int &time)
{
    visited[u] = true;
    discovery[u] = low[u] = ++time;

    for (int v = 0; v < matrix.size(); v++)
    {
        if (matrix[u][v] == 1) // Nếu có cạnh giữa u và v
        {
            if (!visited[v]) // Nếu v chưa được thăm
            {
                parent[v] = u;
                findBridges(v, matrix, visited, discovery, low, parent, bridges, time);

                // Cập nhật low của u dựa trên low của con v
                low[u] = min(low[u], low[v]);

                // Kiểm tra điều kiện cạnh cầu
                if (low[v] > discovery[u])
                {
                    bridges.push_back({u, v});
                }
            }
            else if (v != parent[u]) // Nếu v là tổ tiên của u
            {
                low[u] = min(low[u], discovery[v]);
            }
        }
    }
}


void findArticulationPointsAndBridges(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<bool> visited(n, false);
    vector<int> discovery(n, -1);
    vector<int> low(n, -1);
    vector<int> parent(n, -1);
    vector<bool> isArticulation(n, false);
    vector<pair<int, int>> bridges;
    int time = 0;

    // Duyệt qua tất cả các đỉnh để xử lý thành phần liên thông
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            findArticulationPoints(i, matrix, visited, discovery, low, parent, isArticulation, time);
            findBridges(i, matrix, visited, discovery, low, parent, bridges, time);
        }
    }

    // In các đỉnh khớp
    cout << "Cac dinh khop: ";
    for (int i = 0; i < n; i++)
    {
        if (isArticulation[i])
        {
            cout << i + 1 << " ";
        }
    }
    cout << endl;

    // In các cạnh cầu
    cout << "Cac canh cau: ";
    for (auto &bridge : bridges)
    {
        cout << "(" << bridge.first + 1 << ", " << bridge.second + 1 << ") ";
    }
    cout << endl;
}


int main() {
    string fileName = "graph4.txt";
    vector<vector<int>> matrix = readAdjacencyMatrix(fileName);
    printMatrix(matrix);
}