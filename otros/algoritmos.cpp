#include<iostream>
#include<cmath>
#include<random>
#include<string.h>
#define suma cout << " + "
#define resta cout << " - "
#define nada cout << ""
#define MAX 20
using namespace std;

class Matriz{
    public:
        int fila, columna;
        double M[MAX][MAX];
        Matriz(){ }
        Matriz(int, int);
        void leerMatriz(int, int); //Llenado manual
        void llenarMatriz(int, int); //Llenado automatico (random)
        void mostrarMatriz();
        bool cuadrada(){
            if (fila == columna) { return true;}
            else { return false;}
        }
};

bool start = true;
Matriz matriz[MAX];
int indice = 0;

//Menu
void menuPrincipal();
void menuCrearM();
void menuOperaciones();
void menuMetodos();

//Operaciones con matrices
void insertaMatriz(int op); //
void sumaMatrices(Matriz A, Matriz B); //Suma de matrices A + B
void restaMatrices(Matriz A, Matriz B); //Resta de matrices A - B
Matriz multiMatrices(Matriz A, Matriz B); //Multiplicacion de matrices A X B
Matriz numXmatriz(Matriz A, double num); //Multiplicacion de Matriz X Numero
Matriz transpuesta(Matriz M); //Transpuesta
double determinante(Matriz A, int orden); //Determinante de una matriz NxN
double cofactor(Matriz A, int orden, int fila, int columna); //Cofactor NxN
Matriz inversa(Matriz A);
Matriz adjunta(Matriz M);
bool matricesExistentes(int condicion);
void solucionesMatriz(Matriz A, Matriz B);

//Metodos Sistemas Numericos
void Gauss();
void GaussSeidel();
void Raphson();
void Biseccion();
void PuntoFijoMultivariable();
void RapshonModificado();

//Metodos de ayuda para los Metodos Numericos
int grado; double coeficiente[15]; //Para lectura de una funcion
double funcion(double x);
double derivada(double x);
double derivada2(double x); 
string escribirFuncion();
void imprimirBiseccion(int iter, double Xa, double Xb, double Xr, double Ep);
double evaluarFxy(double x, double y); //Punto fijo multivariable
double evaluarGxy(double x, double y); //Punto fijo multivariable

int main(){

    while (start){
        menuPrincipal();
    }

}

/* Declaracion de los metodos de clase Matriz */

Matriz::Matriz(int fila, int columna){
    this->fila = fila;
    this->columna = columna;
}

void Matriz::leerMatriz(int fila, int columna){
    this->fila = fila;
    this->columna = columna;
    for (int i = 0; i < fila; i++){
        for (int j = 0; j < columna; j++){
            cout << "ELEMENTO [" << i+1 << "," << j+1 << "] : ";
            cin >> M[i][j];
        }
    }
}

void Matriz::llenarMatriz(int fila, int columna){
    this->fila = fila;
    this->columna = columna;
    for (int i = 0; i < fila; i++){
        for (int j = 0; j < columna; j++){
            M[i][j] = rand()%10;
        }
    }
}

void Matriz::mostrarMatriz(){
    
    for (int i = 0; i < fila; i++){
        for (int j = 0; j < columna; j++){
            cout << "\t" << M[i][j];
        }
        cout << endl;
    }
}

/* Menu */

void menuPrincipal(){
    system("cls");
    int op;
    cout << "----------------------------------------\n";
    cout << "\tMENU PRINCIPAL\n";
    cout << "----------------------------------------\n";
    cout << "    1. INSERTAR MATRIZ\n    2. OPERACIONES CON MATRICES\n";
    cout << "    3. METODOS NUMERICOS\n    4. SALIR\n    INSERTE UNA OPCION: ";
    cin >> op;
    switch(op){
        case 1: menuCrearM(); break;
        case 2: menuOperaciones(); break;
        case 3: menuMetodos(); break;
        case 4: start = false; break;
        default: cout << "\n\nOPCION NO VALIDA\n";
    }
}

void menuCrearM(){
    int op; bool repite = true;
    do{
        system("cls");
        cout << "----------------------------------------\n";
        cout << "\tMENU CREAR MATRIZ\n";
        cout << "----------------------------------------\n";
        cout << "    1. Llenado manual\n    2. Llenado automatico\n    3. Regresar";
        cout << "\n  Ingrese su opcion: ";
        cin >> op;
        switch(op){
            case 1: insertaMatriz(op); break;
            case 2: insertaMatriz(op); break;
            case 3: repite = false; break;
            default: cout << "Opcion no valida";
        }
    }while (repite);
}

void menuOperaciones(){
    
    system("cls");
    int op, ma1, ma2;
    double num;
    cout << "----------------------------------------\n";
    cout << "\tOPERACIONES CON MATRICES\n";
    cout << "----------------------------------------\n";
    cout << "  1. SUMA MATRICES\n  2. RESTA MATRICES\n";
    cout << "  3. MULTIPLICACION MATRICES\n  4. MULTIPLICACION ESCALAR\n";
    cout << "  5. DETERMINANTE DE UNA MATRIZ\n  6. INVERSA DE UNA MTRIZ\n";
    cout << "  7. REGRESAR AL MENU PRINCIPAL\n\n  INSERTE UNA OPCION: ";
    cin >> op;
    switch(op){
        case 1: // A + B
            if (matricesExistentes(2)) { 
                cout << "\n\tFORMATO A + B\n";
                cout << "MATRIZ A: "; cin >> ma1;
                cout << "MATRIZ B: "; cin >> ma2;
                cout << endl; 
                sumaMatrices(matriz[ma1-1], matriz[ma2-1]); 
            }
            break;
        case 2: // A - B
            if (matricesExistentes(2)) { 
                cout << "\n\tFORMATO A - B\n";
                cout << "MATRIZ A: "; cin >> ma1;
                cout << "MATRIZ B: "; cin >> ma2;
                cout << endl; 
                restaMatrices(matriz[ma1-1], matriz[ma2-1]); 
            }
            break;
        case 3: // A X B
            if (matricesExistentes(2)) { 
                cout << "\n\tFORMATO A X B\n";
                cout << "MATRIZ A: "; cin >> ma1;
                cout << "MATRIZ B: "; cin >> ma2;
                cout << endl; 
                if (matriz[ma1-1].columna == matriz[ma2-1].fila){
                    Matriz T = multiMatrices(matriz[ma1-1], matriz[ma2-1]);
                    T.mostrarMatriz();
                }
                else{
                    cout << "\nNO CUMPLEN LAS CONDICIONES PARA MULTIPLICARSE\n";
                }
            }
            break;
        case 4: // A X num
            if (matricesExistentes(1)) { 
                cout << "\n\tFORMATO A X NUM\n";
                cout << "MATRIZ A: "; cin >> ma1;
                cout << "NUMERO  : "; cin >> num;
                cout << endl; 
                Matriz T = numXmatriz(matriz[ma1-1], num);
                T.mostrarMatriz(); 
            }
            break;
        case 5: // DET(A)
            if (matricesExistentes(1)){
                cout << "\n\tFORMATO det(A)\n";
                cout << "MATRIZ A: "; cin >> ma1;
                if (matriz[ma1-1].cuadrada()){
                    cout << "DETERMINANTE: " << determinante(matriz[ma1-1], matriz[ma1-1].fila) << "\n";
                }
                else{
                    cout << "\nNO ES POSIBLE SACAR LA DETERMINANTE, PORQUE NO ES UNA MATRIZ CUADRADA\n";
                }
            }
            break;
        case 6: // INV (A)
            if (matricesExistentes(1)){
                cout << "\n\tFORMATO Inv(A)\n";
                cout << "MATRIZ A: "; cin >> ma1;
                cout << "\n\n";
                if (matriz[ma1-1].cuadrada()){
                    if (determinante(matriz[ma1-1], matriz[ma1-1].fila) != 0){
                        Matriz Inv = inversa(matriz[ma1-1]);
                        Inv.mostrarMatriz();
                    }
                    else{
                        cout << "\nNO ES POSIBLE HALLAR LA INVERSA, PORQUE SU DETERMINANTE ES IGUAL A 0\n";
                    }
                }
                else{
                    cout << "\nNO ES POSIBLE HALLAR LA INVERSA, PORQUE NO ES UNA MATRIZ CUADRADA\n";
                }
            }
            break;
        case 7: // Regresar al menu principal
            menuPrincipal();
            break;
        default: cout << "\n\nOPCION NO VALIDA\n"; break;
    }
    system("PAUSE");
}

void menuMetodos(){
    system("cls"); int op;
    cout << "----------------------------------------\n";
    cout << "\tMETODOS NUMERICOS\n";
    cout << "----------------------------------------\n";
    cout << "  1. GAUSS\n  2. GAUSS SEIDEL\n";
    cout << "  3. NEWTON RAPHSON\n  4. BISECCION\n";
    cout << "  5. PUNTO FIJO MULTIVARIABLE\n  6. NEWTON RAPHSON MODIFICADO\n";
    cout << "  7. REGRESAR AL MENU PRINCIPAL\n\n  INSERTE UNA OPCION: ";
    cin >> op;
    switch(op){
        case 1: Gauss(); break;
        case 2: GaussSeidel(); break;
        case 3: Raphson(); break;
        case 4: Biseccion(); break;
        case 5: PuntoFijoMultivariable(); break;
        case 6: RapshonModificado(); break;
        case 7: menuPrincipal(); break;
        default: cout << "\n\nOPCION NO VALIDA\n";
    }
}

/* Operaciones con matrices */
void insertaMatriz(int op){
    system("cls");
    int fila, columna;
    cout << "----------------------------------------\n";
    cout << "\tINSERTANDO MATRIZ\n";
    cout << "----------------------------------------\n";
    cout << "  INGRESA LAS DIMENSIONES DE LA MATRIZ \n";
    cout << " Dimension para Fila: "; cin >> fila;
    cout << " Dimension para columna: "; cin >> columna;
    if (op == 1){ matriz[indice].leerMatriz(fila, columna);} //Manual
    if (op == 2){ matriz[indice].llenarMatriz(fila, columna);} //Random

    matriz[indice].mostrarMatriz();
    indice++;
    system("PAUSE");
}

void sumaMatrices(Matriz A, Matriz B){ //Suma de matrices A + B
    if (A.fila == B.fila){
        cout << "\nLA SUMA DE LAS MATRICES ES: \n";
        for (int i = 0; i < A.fila; i++){;
            for (int j = 0; j < A.fila; j++){
               cout << A.M[i][j] + B.M[i][j] << "\t";
            }
            cout << endl;
        }
    }
    else{
        cout << "\nEL ORDEN DE LAS MATRICES NO SON IGUALES\n";
    }
}

void restaMatrices(Matriz A, Matriz B){ //Resta de matrices A - B
    if (A.fila == B.fila){

        cout << "\nLA RESTA DE LAS MATRICES ES: \n";
        for (int i = 0; i < A.fila; i++){;
            for (int j = 0; j < A.fila; j++){
               cout << A.M[i][j] - B.M[i][j] << "\t";
            }
            cout << endl;
        }
    }
    else{
        cout << "\nEL ORDEN DE LAS MATRICES NO SON IGUALES\n";
    }
} 

Matriz multiMatrices(Matriz A, Matriz B){ //Multiplicacion de matrices A X B
    Matriz tmp(A.fila, B.columna);
    for (int i = 0; i < A.fila; i++){
        for (int j = 0; j < B.columna; j++){
            for (int k = 0; k < A.fila; k++){
                tmp.M[i][j] += A.M[i][k] * B.M[k][j];
            }
        }
    }
    return tmp;
}

Matriz numXmatriz(Matriz A, double num){ //Multiplicacion de Matriz X Numero
    Matriz tmp(A.fila, A.columna);
    for (int i = 0; i < A.fila; i++){
        for (int j = 0; j < A.columna; j++){
            tmp.M[i][j] =  num * A.M[i][j]; 
        }
    }
    return tmp;
}

Matriz transpuesta(Matriz M){ //Transpuesta
    Matriz T(M.columna, M.fila);
    for (int i = 0; i < M.fila; i++){
		for (int j = 0; j < M.columna; j++){
			T.M[j][i] = M.M[i][j];  
		}	
	}
    return T;
} 

double determinante(Matriz A, int orden){ //Determinante de una matriz NxN
    double det = 0;
    if (orden == 1){
        det = A.M[0][0];
    }
    else{
        for (int j = 0; j < orden; j++){
            det += A.M[0][j] * cofactor(A, orden, 0, j);
        } 
    }
    return det;
} 

double cofactor(Matriz A, int orden, int fila, int columna){ //Cofactor NxN
    Matriz subM(MAX, MAX);
    int n = orden -1;
    int x = 0, y = 0;
    for (int i = 0; i < orden; i++){
        for (int j = 0; j < orden; j++){
            if (i != fila && j != columna){
                subM.M[x][y] = A.M[i][j];
                y++;
                if ( y == n){
                    x++;
                    y = 0;
                }
            }
        }
    }
    return pow(-1, fila + columna) * determinante(subM, n);
} 

Matriz inversa(Matriz A){
    Matriz adjunt = adjunta(A);
    Matriz Inv = numXmatriz(adjunt, (1/determinante(A, A.fila)));
    return Inv;
}

Matriz adjunta(Matriz M){
    Matriz A(M.fila, M.columna);
    for (int i = 0; i < M.fila; i++){
        for (int j = 0; j < M.columna; j++){
            A.M[i][j] = cofactor(M, M.fila, i, j);
        }
    }
    return transpuesta(A);
}

bool matricesExistentes(int condicion){
    system("cls");
    bool cen = false;
    if (indice == 0){
        cout << "\n\tNO EXISTEN MATRICES REGISTRADAS\n";
    }
    else{
        if (indice > condicion-1){
            cout << "----------------------------------------\n";
            cout << "\tMOSTRANDO MATRICES EXISTENTES\n";
            cout << "----------------------------------------\n";
            for (int i = 0; i < indice; i++){
                cout << "\nMatriz [" << i+1 << "] tiene los elementos:\n\n";
                matriz[i].mostrarMatriz();
            }
            cout << "\n----------------------------------------\n";
            cen = true;
        }
        else{
            cout << "\nLA CANTIDAD DE MATRICES REGISTRADAS DEBE SER AL MENOS DE " << condicion << " \n";
        }
    }

    return cen;
}

void solucionesMatriz(Matriz A, Matriz B){
    //A x X = B  --- A-1 x B = X
    Matriz M = inversa(A);
    Matriz sol = multiMatrices(M, B);
    sol.mostrarMatriz();
}

/* Metodos Sistemas Numericos */
void Gauss(){
    int n, iteracion;
    n = 3;
    double M[n][n] = { {4, -9, 2}, {2, -4, 6}, {1, -1, 3}};

    double b[n] = {5, 3, 4}; //Respuestas
    double x[n]; 
    int det = 1;
    
    for (int i = 0; i < n-1; i++){
        det = det * M[i][i];
        if (det == 0){ break; }
        
        for (int k = i + 1; k < n; k++){
            double aux = M[k][i] / M[i][i];

            for (int j = i; j < n; j++){
                M[k][j] = M[k][j] - ( M[i][j] * aux );
            }

            //Mostrar matriz
            cout << endl << endl;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    cout << M[i][j] << "\t";
                }
                cout << endl;
            }

            b[k] = b[k] - ( b[i] * aux );

        }
    }

    //Inversa para encontrar resultados
    x[n-1] = b[n-1] / M[n-1][n-1];
    for (int i = n - 2; i >= 0; i--){
        x[i] = b[i];
        for ( int j = i + 1; j < n; j++){
            x[i] = x[i] - ( M[i][j] * x[j] );
        }
        x[i] = x[i] / M[i][i];
    }

    cout << "Soluciones: \n";
    for (int i = 0; i < n; i++){
        cout << x[i] << endl;
    }
    
    system("PAUSE");
}

void GaussSeidel(){
    int cantX, iteracion;
    cout << "Ingrese cantidad de interaciones: "; cin >> iteracion;
    cout << "Ingrese cantidad de incognitas: ";
    cin >> cantX;
    double M[cantX][cantX + 1];

    //Lectura de datos
    for (int i = 0; i < cantX; i++){
        for (int j = 0; j < cantX + 1; j++){
            cout << "ELEMENTO [" << i+1 << "," << j+1 << "] : ";
            cin >> M[i][j];
        }
    }

    //Valores X^0 -> Por defecto se inicializan en 0
    double tmp[cantX];
    for (int i = 0; i < cantX; i++){
        tmp[i] = 0;
    }
     //esta mal
    for (int ite = 0; ite < iteracion; ite++){
        cout << "Iteracion " << ite + 1 << " toma los valores de: \n";      
        for (int i = 0; i < cantX; i++){
            int tmpS = 0;
            for (int j = 0; j < cantX; j++){
                if ( i != j ){ //Pq las diagonales dividen
                    tmpS += M[i][j] * tmp[j];
                }
            }
            tmp[i] = (M[i][cantX] - tmpS) / M[i][i];
            cout << "X" << i << " = " << tmp[i] << endl;
        }   
    }

    system("PAUSE");
}

void Raphson(){
    cout << "Indica el mayor grado de la ecuacion: "; cin >> grado;

    //Lectura de coeficientes
    for (int i = grado; i >= 0; i--){
		cout << "Indica el coeficiente para el exponente " << i << " : "; 
		cin >> coeficiente[i];
	}
    double tmp, aux;
    double valorEstimado; //0.001
    cout << "Indique el valor estimado: "; cin >> valorEstimado;
    cout << "Indique X0 = "; cin >> tmp;
    bool cen = true;
    //double tmp = 1, aux = 1;
    aux = tmp;
    int i = 0;

    system("cls");
    cout << "Funcion: " << escribirFuncion() << endl;
    cout << "i\t Xi\t\t |Xi+1 - Xi|\n";

    do{
		cout << i + 1 << "\t";
		tmp = tmp - (funcion(tmp)/derivada(tmp));
		cout << tmp << "\t\t";
		cout << abs(tmp - aux) << "\t";
		if (abs(tmp - aux) < valorEstimado){
			cen = false;
		}
		aux = tmp;	
		i++;
		cout << endl;	
	}while(cen);
    system("PAUSE");
}

void Biseccion(){
    cout << "Indica el mayor grado de la ecuacion: "; cin >> grado;
    //Lectura de coeficientes
    for (int i = grado; i >= 0; i--){
		cout << "Indica el coeficiente para el exponente " << i << " : "; 
		cin >> coeficiente[i];
	}

    double Xa, Xb, Xr_actual, Xr_anterior = 0;
    double Ep; //Error porcentual ->  abs( )
    bool cen = true;
    int k = 1;

    //Funciones de Prueba
    //X^4 + 3X^3 - 2
    //x^3 + 2x^2 + 10x - 20

    //Determinar valores para Xa y Xb
    int ind = 0;
    
    do{
        
        Xa = ind;
        funcion(ind) <= 0 ? ind++ : ind--;
        Xb = ind;
        funcion(Xa) < 0 && funcion(Xb) > 0 ? cen = false : cen = true;

    }while (cen);

    system("cls");
    cout << "\n\n\tMETODO DE LA BISECCION\n\n";
    cout << "F(x) = " << escribirFuncion() << "\n\n";
    cout << "#\tXa\t\tXb\t\tXr\t\tEp\n";
    
    do{
        Xr_actual = (Xa + Xb) / 2;
        Ep = abs( ( (Xr_actual - Xr_anterior) / Xr_actual) * 100 );
        Ep <= 1 && Ep >= 0 ? cen = false : cen = true;
        
        imprimirBiseccion(k,Xa, Xb, Xr_actual, Ep);

        funcion(Xa) * funcion(Xr_actual) > 0 ? Xa = Xr_actual : Xb = Xr_actual;
        Xr_anterior = Xr_actual;
        k++;
    }while (cen);
    system("PAUSE");
}

void PuntoFijoMultivariable(){
    double Error, ErrorCal, x, y, xi, yi;
    bool cen = true;
    int i = 1;

    Error = 0.001;
    x = 0; y = 0;

    do{
        xi = evaluarFxy(x,y); yi = evaluarGxy(x,y);

        ErrorCal = abs(/*raiz*/pow(/*(Xi-Xi-1)^2*/pow(xi-x, 2) + /*(Yi-Yi-1)^2*/pow(yi-y, 2) , 0.5) );

        cout << "\nX" << i << " = " << xi << "\tY" << i << " = " << yi << "\t" << ErrorCal << " < " << Error;

        //if (ErrorCal < Error){ cen = false; }
        
        i++;
        x = xi; y = yi;
    }while (ErrorCal > Error);

    system("PAUSE");
}

void RapshonModificado(){
    cout << "Indica el mayor grado de la ecuacion: "; cin >> grado;

    //Lectura de coeficientes
    for (int i = grado; i >= 0; i--){
		cout << "Indica el coeficiente para el exponente " << i << " : "; 
		cin >> coeficiente[i];
	}
    double tmp, aux;
    double valorEstimado; //0.001
    cout << "Indique el valor estimado: "; cin >> valorEstimado;
    cout << "Indique X0 = "; cin >> tmp;
    bool cen = true;
    //double tmp = 1, aux = 1;
    aux = tmp;
    int i = 0;

    system("cls");
    cout << "Funcion: " << escribirFuncion() << endl;
    cout << "i\t Xi\t\t |Xi+1 - Xi|\n";

    do{
		cout << i + 1 << "\t";

        tmp = tmp - ( ( (funcion(tmp) * derivada(tmp)) ) / ( pow(derivada(tmp), 2) * (funcion(tmp) * derivada2(tmp)) ) );

		tmp = tmp - (funcion(tmp)/derivada(tmp));
		cout << tmp << "\t\t";
		cout << abs(tmp - aux) << "\t";
		if (abs(tmp - aux) < valorEstimado){
			cen = false;
		}
		aux = tmp;	
		i++;
		cout << endl;	
	}while(cen);
    system("PAUSE");
}

/* Metodos de ayuda para los Metodos Numericos */

double funcion(double x){
    double tmp = 0;
    for (int i = grado; i >= 0; i--){
        i == 0 ? tmp += coeficiente[i] : tmp += coeficiente[i] * pow(x,i);
    }
    return tmp;
}

double derivada(double x){
    double tmp = 0;
    for (int i = grado; i >= 0; i--){
        if (i != 0){ tmp += i * coeficiente[i] * pow(x,i-1); }
    }
    return tmp;
}

double derivada2(double x){
    double tmp = 0;
    for (int i = grado; i >= 0; i--){
        if (i != 0){ tmp += i * coeficiente[i] * i-1 * pow(x,i-2); }
    }
    return tmp;
}

string escribirFuncion(){
    string funcion = "";
    for (int i = grado; i >= 0; i--){
        if (i == 0){
            if (coeficiente[i] != 0){
                coeficiente[i] > 0 ? suma : resta;
                cout << abs(coeficiente[i]);
            }
        }
        else{
            if (coeficiente[i] != 0){
                i == grado ? ( coeficiente[i] < 0 ? resta : nada) : ( coeficiente[i] > 0 ? suma : resta);
                coeficiente[i] == 1 ? nada : cout << abs(coeficiente[i]);
                i == 1 ? cout << "x" : cout << "x^" << i;
            }
        }
    }
    return funcion;
}

void imprimirBiseccion(int iter, double Xa, double Xb, double Xr, double Ep){
    cout << iter << "\t" << Xa << "\t\t" << Xb << "\t\t" << Xr << "\t\t";
    iter != 1 ? cout << Ep << " %\n" : cout << "-\n";
}

double evaluarFxy(double x, double y){ //Punto fijo multivariable
    return (pow(x,2) + pow(y,2) + 8)/10;
} 

double evaluarGxy(double x, double y){ //Punto fijo multivariable
    return (x*pow(y,2) + x + 8)/10;
} 
