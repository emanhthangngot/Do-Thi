#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<algorithm>

using namespace std;

#define ADJ_MATRIX vector<vector<int>>

ADJ_MATRIX readAdjacencyMatrix(string fileName)
{
    ifstream input(fileName);
    if (!input)
    {
        cerr << "Khong the mo file: " << fileName << endl;
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
void printMatrix(ADJ_MATRIX matrix)
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


// Cho đồ thị có hướng từ đó ta chuyển thành đồ thị vô hướng tương ứng
ADJ_MATRIX convertToUndirected(ADJ_MATRIX directedMatrix) {
    int n = directedMatrix.size();
    ADJ_MATRIX undirectedMatrix = directedMatrix;
    for(int u = 0; u< n; u++) {
        for(int v = 0; v <n; v++) {
            if(directedMatrix[u][v] > 0) {
                undirectedMatrix[v][u] = directedMatrix[u][v];
            }
        }
    }
    return undirectedMatrix;
}

// Cho đồ thị bù của 1 đồ thị vô hướng được in ra dưới dạng ma trận kề
ADJ_MATRIX complementGraph(ADJ_MATRIX matrix) {
    int n = matrix.size();
    ADJ_MATRIX complement = matrix;
    for(int i = 0; i<n; i++) {
        for(int j = 0 ; j<n; j++) {
            complement[i][j] = 1 - complement[i][j];
        }
    }
    return complement;
}

// Cho đồ thị chuyển vị của 1 đồ thị có hướng dưới dạng ma trận kề
ADJ_MATRIX transposeGraph(ADJ_MATRIX graph) {
    int n = graph.size();
    ADJ_MATRIX transpose(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            transpose[i][j] = graph[j][i];
        }
    }

    return transpose;
}



int main() {
    string fileName = "graph5.txt";
    ADJ_MATRIX matrix = readAdjacencyMatrix(fileName);
    ADJ_MATRIX undirect = convertToUndirected(matrix);
    printMatrix(matrix);
    cout << endl;
    printMatrix(undirect);
    ADJ_MATRIX complement = complementGraph(undirect);
    cout << endl << "Do thi bu cua do thi tren la: " << endl;
    printMatrix(complement);
    ADJ_MATRIX transpose = transposeGraph(matrix);
    cout << endl << "Do thi chuyen vi cua do thi la: " << endl;
    printMatrix(transpose);
    

    return 0;
}