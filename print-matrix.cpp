#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

void PrintMatrix(int **matrix, int rows, int cols) {

    for (int i = 0; i < rows; ++i) {
        cout << "|"; 

        for (int j = 0; j < cols; ++j) {
            // print each element of the matrix with a width of 4
            cout << setw(4) << matrix[i][j] << " "; 
        }

        cout << "|" << endl; 
    }
}