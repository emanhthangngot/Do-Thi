#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

// Hàm đọc ma trận kề từ file
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

// Kiem tra do thi vo huong hay co huong
bool isUndirectedGraph(vector<vector<int>> matrix)
{
    for (int i = 0; i < matrix.size() - 1; i++)
    {
        for (int j = i + 1; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] != matrix[j][i])
                return false;
        }
    }
    return true;
}

void verticeLevel(vector<vector<int>> v, vector<int> &arr)
{
    for (int i = 0; i < v.size(); i++)
    {
        int sum = 0;
        for (int j = 0; j < v.size(); j++)
        {
            sum += v[i][j];
        }
        cout << i + 1 << ": " << sum << endl;
        arr[i] = sum;
    }
}

// Xac dinh dinh treo va dinh la cho do thi vo huong

void findDanglingVertices(vector<int> v)
{
    cout << "Dinh treo: ";
    for (int i = 0; i < v.size(); i++)
        if (v[i] == 0)
            cout << i + 1 << " ";
    cout << endl;
    cout << "Dinh la: ";
    for (int i = 0; i < v.size(); i++)
        if (v[i] == 1)
            cout << i + 1 << " ";
    cout << endl;
}

bool isCompleteGraph(const vector<vector<int>> &matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i != j && matrix[i][j] != 1)
                return false; // Mọi cặp đỉnh phải có cạnh
            if (i == j && matrix[i][j] != 0)
                return false; // Không có cạnh khuyên
        }
    }
    return true;
}

// Kiểm tra đồ thị vòng
bool isCycleGraph(const vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<int> degree(n, 0);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] == 1)
                degree[i]++;
        }
    }

    // Mỗi đỉnh phải có bậc bằng 2
    for (int i = 0; i < n; ++i)
    {
        if (degree[i] != 2)
            return false;
    }
    return true;
}

// Kiểm tra đồ thị hai phía (bipartite graph) bằng BFS
bool isBipartite(const vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<int> color(n, -1); // -1: chưa tô màu, 0 và 1: hai màu khác nhau

    for (int start = 0; start < n; ++start)
    {
        if (color[start] == -1)
        {
            color[start] = 0;
            vector<int> queue = {start};

            while (!queue.empty())
            {
                int u = queue.back();
                queue.pop_back();

                for (int v = 0; v < n; ++v)
                {
                    if (matrix[u][v])
                    {
                        if (color[v] == -1)
                        {                            // Chưa tô màu
                            color[v] = 1 - color[u]; // Tô màu đối lập
                            queue.push_back(v);
                        }
                        else if (color[v] == color[u])
                        {
                            return false; // Có hai đỉnh kề nhau cùng màu -> Không phải đồ thị hai phía
                        }
                    }
                }
            }
        }
    }
    return true;
}

// Kiểm tra đồ thị hai phía đầy đủ
bool isCompleteBipartite(const vector<vector<int>> &matrix)
{
    if (!isBipartite(matrix))
        return false;

    int n = matrix.size();
    vector<int> color(n, -1);
    vector<int> partA, partB;

    // Tô màu và chia đỉnh thành hai tập
    for (int start = 0; start < n; ++start)
    {
        if (color[start] == -1)
        {
            color[start] = 0;
            vector<int> queue = {start};

            while (!queue.empty())
            {
                int u = queue.back();
                queue.pop_back();

                for (int v = 0; v < n; ++v)
                {
                    if (matrix[u][v])
                    {
                        if (color[v] == -1)
                        {
                            color[v] = 1 - color[u];
                            queue.push_back(v);
                        }
                    }
                }
            }
        }
    }

    // Phân chia các đỉnh theo màu
    for (int i = 0; i < n; ++i)
    {
        if (color[i] == 0)
            partA.push_back(i);
        else
            partB.push_back(i);
    }

    // Kiểm tra mọi cặp đỉnh từ hai tập có đúng một cạnh nối
    for (int a : partA)
    {
        for (int b : partB)
        {
            if (matrix[a][b] != 1)
                return false;
        }
    }
    return true;
}

void DFS(int u, vector<vector<int>> &matrix, vector<bool> &visited)
{
    visited[u] = true; // Đánh dấu đỉnh u đã được thăm
    for (int v = 0; v < matrix.size(); v++)
    {
        if (matrix[u][v] == 1 && !visited[v])
        { // Nếu có cạnh và v chưa được thăm
            DFS(v, matrix, visited);
        }
    }
}

// Hàm tìm số lượng thành phần liên thông
int countConnectedComponents(vector<vector<int>> &matrix)
{
    int n = matrix.size();          // Số đỉnh
    vector<bool> visited(n, false); // Mảng đánh dấu
    int components = 0;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        { // Nếu đỉnh i chưa được thăm
            components++;
            DFS(i, matrix, visited); // Duyệt từ đỉnh i
        }
    }
    return components;
}

int main()
{
    string file1 = "graph3.txt";
    vector<vector<int>> matrix = readAdjacencyMatrix(file1);
    printMatrix(matrix);
    if (isUndirectedGraph(matrix))
    {
        cout << "Day la ma tran vo huong" << endl;
    }
    else
    {
        cout << "Day la ma tran co huong" << endl;
    }
    vector<int> arr(matrix.size(), 0);
    verticeLevel(matrix, arr);
    findDanglingVertices(arr);

    if (isCompleteGraph(matrix))
        cout << "- Do thi day du.\n";
    else
        cout << "- Khong phai do thi day du.\n";

    if (isCycleGraph(matrix))
        cout << "- Do thi vong.\n";
    else
        cout << "- Khong phai do thi vong.\n";

    if (isBipartite(matrix))
        cout << "- Do thi hai phia.\n";
    else
        cout << "- Khong phai do thi hai phia.\n";

    if (isCompleteBipartite(matrix))
        cout << "- Do thi hai phia day du.\n";
    else
        cout << "- Khong phai do thi hai phia day du.\n";
    return 0;
}
