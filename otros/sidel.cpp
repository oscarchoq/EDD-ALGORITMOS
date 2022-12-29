#include <iostream>
#include <cmath>
using namespace std;

class Matriz{
    public:
        int fila;
        int columna;
        double M[10][10];
        double tmp[10][10];

        Matriz(int fila, int columna);
        void rellenar();
        void imprimir();
        bool diagonalDominante();
        void ordenarMatriz();
        void seidel();
};

int main(){
    int fila, columna;
    cout << "INGRESE LA DIMENSION DE LA FILA: ";
    cin >> fila;
    cout << "INGRESE LA DIMENSION DE LA COLUMNA: ";
    cin >> columna;

    Matriz M(fila, columna);
    M.rellenar();

    /*
    if ( M.diagonalDominante() ){
        M.seidel();
    } else{
        cout << "No cumple con las condiciones para resolverlo por Gauss Seidel";
    }
    */
    M.ordenarMatriz();
    return 0;
}

Matriz::Matriz(int fila, int columna){
    this->fila = fila;
    this->columna = columna;
}

void Matriz::rellenar(){
    cout << "INGRESE LOS DATOS PARA LA MATRIZ: ";
    for (int i = 0; i < fila; i++){
        for (int j = 0; j < columna; j++){
            cout << "M[" << i << "][" << j << "] = ";
            cin >> M[i][j];
        }
        cout << endl;
    }
}

void Matriz::imprimir(){
    cout << "MOSTRANDO LOS DATOS PARA LA MATRIZ: ";
    for (int i = 0; i < fila; i++){
        for (int j = 0; j < columna; j++){
            cout <<  M[i][j] << "\t";
        }
        cout << endl;
    }
}

bool Matriz::diagonalDominante(){
    bool cen = true;
    for (int i = 0; i < fila; i++){
        double tmp = 0;
        for ( int j = 0; i < columna-1; j++){ //-1 pq no se considera a las respuestas
            if (i == j) { continue; }
            tmp += abs(M[i][j]);
        }
        if ( abs(M[i][i] < tmp) ){
            cen = false;
        }
    }
    return cen;
}

void Matriz::ordenarMatriz(){
    double tmp[fila][columna];
    double max;
    double comparar, aux, aux1;

    for (int i = 0; i < fila; i++){
        
        for (int j = i; j < fila; j++){
            max = abs(M[j][i]);
            for (int k = j+1; k < fila; k++){
                comparar = abs(M[k][i]);
                if (max < comparar){
                    max = comparar;
                    //Intercambio por filas
                    for ( int m = 0; m < columna; m++){
                        aux = M[j][m];
                        aux1 = M[k][m];
                        tmp[j][m] = aux1;
                        tmp[k][m] = aux;
                    }
                }
            }
        }
    }

    /*
    
    for (int i = 0; i < fila; i++){ 
        max = abs(M[i][i]);
        for ( int j = 0; j < fila; j++){ 
            
            if ( max < abs(M[j][i]) ){
                max = M[j][i];
                for (int k = 0; k < columna; k++){
                    tmp[i][k] = M[j][k];
                    tmp[j][k] = M[i][k];
                }
            }
        }
    }*/

    cout << "\n\nMOSTRANDO LOS DATOS PARA LA MATRIZ: \n";
    for (int i = 0; i < fila; i++){
        for (int j = 0; j < columna; j++){
            cout <<  tmp[i][j] << "\t";
        }
        cout << endl;
    }
}
/*
for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
         if(M[i][i] < M[j][i]){

            for(int k=0;k<n+1;k++){
               V[k]=M[j][k];
               M[j][k]=M[i][k];
               M[i][k]=V[k];
            }
         }

      }
   }*/

   #include <iostream>
#include <cmath>

using namespace std;

const int N = 3; // Número de ecuaciones
const double TOL = 1e-5; // Tolerancia para la convergencia

// Función para resolver el sistema de ecuaciones
void gaussSeidel(double a[N][N], double b[N], double x[N], int maxIter)
{
    double sum, error;
    int i, j;

    for (int k = 0; k < maxIter; k++)
    {
        error = 0;
        for (i = 0; i < N; i++)
        {
            sum = 0;
            for (j = 0; j < N; j++)
            {
                if (j != i)
                    sum += a[i][j] * x[j];
            }
            double temp = (b[i] - sum) / a[i][i];
            error += abs(x[i] - temp);
            x[i] = temp;
        }

        cout << x[i] << endl;

        // Si se alcanzó la tolerancia, se termina la iteración
        if (error < TOL)
            return;
    }
}

int main()
{
    // Matriz de coeficientes
    double a[N][N] = {
        {12, 3, -5},
        {1, 5, 3},
        {3, 7, 13}};

    // Términos independientes
    double b[N] = {1, 28, 76};

    // Soluciones iniciales
    double x[N] = {0, 0, 0};

    int maxIter = 1000; // Número máximo de iteraciones

    gaussSeidel(a, b, x, maxIter);

    // Imprime las soluciones
    cout << "Soluciones: " << endl;
    for (int i = 0; i < N; i++)
        cout << "x" << i << " = " << x[i] << endl;

    return 0;
}