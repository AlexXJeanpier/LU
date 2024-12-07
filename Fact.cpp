#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

typedef vector<vector<double>> Matrix;

//Determinante
double determinant(const Matrix& A) {
    int n = A.size();
    double det = 1;
    
    for (int i = 0; i < n; ++i) {
        det *= A[i][0];
    }
    
    return det;
}

// Verificar si matriz esta bien condicionada
bool VerificarCondicion(const Matrix& A) {
    const double EPS = 1e-9;
    int n = A.size();
    
    //Para la diagonal
    for (int i = 0; i < n; ++i) {
        if (abs(A[i][i]) < EPS) return false;
    }
    
    // Verificar determinante 
    double det = determinant(A);
    if (abs(det) < EPS) return false;
    
    return true; // Aprobada XD
}

// Imprimir matriz
void imprimirMatriz(const Matrix& mat, const string& nombreMatriz) 
{
    cout << "Matrix " << nombreMatriz << ":\n";
    for (const auto& row : mat) 
    {
        for (double valor : row)
            cout << setw(10) << valor << " ";
        cout << endl;
    }

    cout << endl;
    cout << "--------------------------" << endl;
}

//Multiplicar matriz
Matrix multiplicarMatriz(const Matrix& A, const Matrix& B) 
{
    int n = A.size(), m = B[0].size(), p = A[0].size();
    Matrix result(n, vector<double>(m, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < p; ++k)
                result[i][j] += A[i][k] * B[k][j];

    return result;
}

//Factorizacion LU
void DescomposicionLU(const Matrix& A) 
{
    int n = A.size();
    Matrix L(n, vector<double>(n, 0)), U = A, E;

    vector<string> pro; //vector para los procesimientos

    //Vecctor L
    for (int i = 0; i < n; ++i) 
    {
        L[i][i] = 1.0;
    }

    vector<Matrix> Es;

    for (int i = 0; i < n; ++i) 
    {
        for (int j = i + 1; j < n; ++j) 
        {
            double factor = U[j][i] / U[i][i];
            L[j][i] = factor;

            // Construccion de la matriz Elemental
            E = Matrix(n, vector<double>(n, 0));
            for (int k = 0; k < n; ++k) E[k][k] = 1.0;
            E[j][i] = -factor;

            U = multiplicarMatriz(E, U);

            int NroE = Es.size() + 1;

            Es.push_back(E);

            // Registrar el paso realizado
            pro.push_back("F_" + to_string(j + 1) + " = F_" + to_string(j + 1) + " - (" + to_string(factor) + ") * F_" + to_string(i + 1)); //Imprime los  procesos realizados
            imprimirMatriz(E, "E_" + to_string(NroE));
            
        }
    }

    // Imprimir matrices finales
    imprimirMatriz(U, "U");
    imprimirMatriz(L, "L");

    // Imprimir procedimientos
    cout << "Procedimientos realizados:\n";
    for (const string& pro : pro) 
    {
        cout << pro << endl;
    }

    // Formulas 
    cout << "\nU = ";
    for (int i = 0; i < Es.size(); ++i)
        cout << "E_" << i + 1 << (i < Es.size() - 1 ? " * " : "");
    cout << " * A\n";

    cout << "A = ";
    for (int i = 0; i < Es.size(); ++i)
        cout << "E_" << i + 1 << "^-1" << (i < Es.size() - 1 ? " * " : "");
    cout << " * U\n";
}



int main() {
    cout << " ====================== FACTORIZACION LU ======================\n";
    cout << " Ingrese el numero de filas y columnas de la matriz A: ";
    int n;
    cin >> n;

    Matrix A(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) {
            cout << " Elemento [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> A[i][j];
        }
    }
    cout << endl;
    
    if (!VerificarCondicion(A)) {
        cout << "La matriz no esta bien condicionada.\n";
        return 1;
    }
    
    imprimirMatriz(A, "A");
    DescomposicionLU(A);

    return 0;
}
