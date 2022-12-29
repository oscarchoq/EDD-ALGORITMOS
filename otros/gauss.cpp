#include <iostream>
using namespace std;

class Matriz{
    public:
        int fila;
        int columna;
        double M[10][10];

        Matriz(int fila, int columna);
        void rellenar();
        void imprimir();
        void gauss();
};


int main(){

    int fila, columna;
    cout << "INGRESE LA DIMENSION DE LA FILA: ";
    cin >> fila;
    cout << "INGRESE LA DIMENSION DE LA COLUMNA: ";
    cin >> columna;

    Matriz M(fila, columna);
    M.rellenar();
    M.gauss();

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

void Matriz::gauss(){
     
    // LOS ELEMENTOS DE LA DIAGONAL PRINCIPAL NO DEBEN SER CEROS
    //Matriz triangular supeior con ceros
    
    for (int i = 0; i < fila; i++){
        if (M[i][i] == 0 ) { break; } 
        
        for (int k = i + 1; k < fila; k++){
            double aux = M[k][i] / M[i][i];

            for (int j = i; j < columna; j++){
                M[k][j] = M[k][j] - ( M[i][j] * aux );
            }

            //Mostrar matriz
            cout << endl << endl;
            for (int i = 0; i < fila; i++){
                for (int j = 0; j < columna; j++){
                    cout << M[i][j] << "\t";
                }
                cout << endl;
            }
        }
    }
    
    //Encontrar el valor de las incognitas
    double x[fila];
    double tmp = 0;
    x[fila-1] = M[fila-1][columna-1] / M[fila-1][columna-2];
    for (int i = fila - 2; i >= 0; i--){
        for ( int j = i + 1; j < columna; j++){
            tmp += M[i][j] * x[j]; //Multiplica los valores encontrados en la matriz
        }
        x[i] = (M[i][columna-1] - tmp) / M[i][i];
    }

    cout << "\nRESULTADOS: \n";
    for (int i = 0; i < fila; i++)
        cout << "X" << i << "= " << x[i] << endl; 


}