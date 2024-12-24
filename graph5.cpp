#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

#define ADJ_MATRIX vector<vector<int>>
#define EDGES_LIST map<pair<int, int>, int>

// Hàm đọc ma trận kề từ file
ADJ_MATRIX readAdjacencyMatrix(string fileName) {
    ifstream input(fileName);
    if (!input) {
        cerr << "Không thể mở file: " << fileName << endl;
        exit(1);
    }
    int n;
    input >> n; // Số đỉnh
    ADJ_MATRIX matrix(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            input >> matrix[i][j];

    return matrix;
}

// Hàm in ma trận kề
void printMatrix(ADJ_MATRIX matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// BFS để tìm cây khung
void BFS_SpanningTree(const ADJ_MATRIX& adjMatrix, EDGES_LIST& edgesList, int start) {
    int n = adjMatrix.size();
    set<int> visited; // Để lưu các đỉnh đã thăm
    queue<int> q;

    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Duyệt tất cả các đỉnh kề của u trong ma trận kề
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] != 0 && visited.find(v) == visited.end()) {
                // Nếu v chưa thăm và có cạnh nối với u
                visited.insert(v);
                q.push(v);

                // Thêm vào danh sách cạnh cây khung
                if (edgesList.find({u, v}) == edgesList.end() && edgesList.find({v, u}) == edgesList.end()) {
                    edgesList[{u, v}] = adjMatrix[u][v];
                }
            }
        }
    }

    // In danh sách các cạnh trong cây khung (bao gồm trọng số nếu có)
    cout << "Danh sach canh cua cay khung: " << endl;
    for (auto& edge : edgesList) {
        cout << edge.first.first << " - " << edge.first.second << " (Trong so: " << edge.second << ")" << endl;
    }
}

// Hàm kiểm tra điều kiện tồn tại chu trình Euler
bool isEulerian(const ADJ_MATRIX& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        int degree = 0;
        for (int j = 0; j < n; ++j) {
            degree += matrix[i][j];
        }
        if (degree % 2 != 0) {
            return false; // Nếu có đỉnh với bậc lẻ, không có chu trình Euler
        }
    }
    return true;
}

// Thuật toán Hierholzer để tìm chu trình Euler
void hierholzer(int start, ADJ_MATRIX& matrix, vector<int>& eulerCycle) {
    stack<int> currentPath; // Dùng để lưu đường đi hiện tại
    currentPath.push(start);

    while (!currentPath.empty()) {
        int u = currentPath.top();

        // Tìm một cạnh chưa đi từ đỉnh u
        bool foundEdge = false;
        for (int v = 0; v < matrix[u].size(); ++v) {
            if (matrix[u][v] > 0) {  // Nếu có cạnh từ u đến v
                --matrix[u][v];      // Đánh dấu là đã đi qua cạnh này
                --matrix[v][u];      // Đối xứng trong đồ thị vô hướng
                currentPath.push(v); // Đi đến đỉnh tiếp theo
                foundEdge = true;
                break;
            }
        }

        // Nếu không còn cạnh nào từ u
        if (!foundEdge) {
            eulerCycle.push_back(u);
            currentPath.pop();
        }
    }
}

// Hàm tìm và in chu trình Euler
void printEulerianCycle(ADJ_MATRIX& matrix) {
    if (!isEulerian(matrix)) {
        cout << "Khong ton tai chu trinh Euler" << endl;
        return;
    }

    int n = matrix.size();
    int start = -1;

    // Tìm đỉnh bắt đầu (đỉnh bất kỳ có cạnh nối)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > 0) {
                start = i;
                break;

                
            }
        }
        if (start != -1) break;
    }

    vector<int> eulerCycle;
    hierholzer(start, matrix, eulerCycle);

    // Đảo ngược kết quả vì lưu theo thứ tự ngược
    reverse(eulerCycle.begin(), eulerCycle.end());

    // In chu trình Euler
    cout << "Chu trinh Euler:" << endl;
    for (size_t i = 0; i < eulerCycle.size(); ++i) {
        cout << eulerCycle[i];
        if (i < eulerCycle.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void DFS_SpanningTree(ADJ_MATRIX& adjMatrix, EDGES_LIST& edgesList, int start, set<int>& visited) {
    visited.insert(start); // Đánh dấu đỉnh `start` là đã thăm

    int n = adjMatrix.size();
    for (int v = 0; v < n; ++v) {
        if (adjMatrix[start][v] != 0 && visited.find(v) == visited.end()) {
            // Nếu có cạnh nối từ `start` đến `v` và `v` chưa thăm
            edgesList[{start, v}] = adjMatrix[start][v];

            // Gọi đệ quy để duyệt tiếp từ đỉnh `v`
            DFS_SpanningTree(adjMatrix, edgesList, v, visited);
        }
    }
}

// Wrapper function to simplify calling DFS
void findSpanningTreeDFS(ADJ_MATRIX& adjMatrix, EDGES_LIST& edgesList, int start) {
    set<int> visited; // Lưu các đỉnh đã thăm
    DFS_SpanningTree(adjMatrix, edgesList, start, visited);

    // In danh sách các cạnh trong cây khung
    cout << "Danh sach canh cua cay khung:" << endl;
    for (auto& edge : edgesList) {
        cout << edge.first.first << " - " << edge.first.second << " (Trong so: " << edge.second << ")" << endl;
    }
}


int main() {
    string fileName = "graph6.txt";
    ADJ_MATRIX matrix = readAdjacencyMatrix(fileName);

    cout << "Ma tran ke cua do thi la: " << endl;
    printMatrix(matrix);

    // bfs
    EDGES_LIST edge1;
    BFS_SpanningTree(matrix, edge1, 0);

    // dfs
    EDGES_LIST edges2;
    findSpanningTreeDFS(matrix, edges2, 0);

    // Tìm và in chu trình Euler
    printEulerianCycle(matrix);

    return 0;
}
