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

// Hàm chuyển ma trận kề thành danh sách kề
vector<vector<int>> matrixToAdjacencyList(vector<vector<int>> matrix)
{
    int n = matrix.size();
    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] == 1)
                adjList[i].push_back(j); // Đánh số từ 1
    return adjList;
}

// Hàm đọc danh sách kề từ file (xử lý dòng trống)
vector<vector<int>> readMatrixFromAdjacencyList(string fileName)
{
    ifstream input(fileName);
    if (!input)
    {
        cerr << "Khong the mo file: " << fileName << endl;
        exit(1);
    }

    int n;          // Số đỉnh
    input >> n;     // Đọc số đỉnh
    input.ignore(); // Bỏ qua ký tự xuống dòng

    vector<vector<int>> adjList(n);
    string line;

    for (int i = 0; i < n; ++i)
    {
        getline(input, line);

        if (line.empty())
        {
            // Nếu dòng trống, gán đỉnh này không có cạnh kề
            adjList[i] = vector<int>(n, 0);
            continue;
        }
        else
        {
            stringstream ss(line);
            char chr;
            adjList[i] = vector<int>(n, 0);
            while (ss >> chr)
            {
                adjList[i][chr - '0'] = 1;
            }
        }
    }

    return adjList;
}


// Hàm in ma trận kề
void printMatrix(vector<vector<int>> matrix)
{
    for(int i = 0; i< matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool isUndirectedGraph(vector<vector<int>> matrix) {
    for(int i = 0; i<matrix.size(); i++) {
        for(int j = i+1; j< matrix[i].size(); j++) {
            if(matrix[i][j] != matrix[j][i]) return false;
        }
    }
    return true;
}




int countVertices(vector<vector<int>> matrix) {
    return matrix.size();
}

int countEdges(vector<vector<int>> matrix) {
    int sum = 0;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            sum = sum + matrix[i][j] + matrix[j][i]; 
        }
    }
    return int(sum / 2);
}

void VerticeLevelDirected(vector<vector<int>> matrix) {
    int n = matrix.size();

    for (int i = 0; i < n; ++i) {
        int inDegree = 0, outDegree = 0;

        // Out-degree: Count edges going *from* vertex `i`
        for (int j = 0; j < n; ++j) {
            outDegree += matrix[i][j];
        }

        // In-degree: Count edges coming *to* vertex `i`
        for (int j = 0; j < n; ++j) {
            inDegree += matrix[j][i];
        }

        cout << "Dinh " << i + 1 << " co: ";
        cout << "Bac vao = " << inDegree << ", ";
        cout << "Bac ra = " << outDegree << endl;
    }
}


int main()
{
    string file1 = "graph1.txt";
    string file2 = "graph2.txt";

    // Xử lý file graph1.txt: ma trận kề -> danh sách kề
    cout << "Chuyen ma tran ke thanh danh sach ke:" << endl;
    vector<vector<int>> matrix = readAdjacencyMatrix(file1);
    vector<vector<int>> adjList1 = matrixToAdjacencyList(matrix);
    printMatrix(adjList1);

    cout << "\n-----------------------------\n";

    // Xử lý file graph2.txt: danh sách kề -> ma trận kề
    cout << "Chuyen danh sach ke thanh ma tran ke:" << endl;
    vector<vector<int>> matrix2 = readMatrixFromAdjacencyList(file2);
    printMatrix(matrix2);

    cout << "\n-----------------------------\n";
    if(isUndirectedGraph(matrix2)) {
        cout << "Ma tran o tren la cua do thi vo huong" << endl;
    }
    else {
        cout << "Ma tran o tren la cua do thi co huong" << endl;
    }

    cout << "\n-----------------------------\n";
    cout << "So dinh cua do thi tren la: " << countVertices(matrix2) << endl;
    cout << "So canh cua do thi tren la: " << countEdges(matrix2) << endl;

    cout << "\n-----------------------------\n";
    VerticeLevelDirected(matrix2);
    return 0;
}
