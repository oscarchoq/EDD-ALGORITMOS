#include <iostream>
#include <cmath>
using namespace std;

class Ecuacion{
    public:
        int grado;
        float coeficiente[20];
        float evaluarFuncion(float x);
        void pedirEcuacion();
        void escribirEcuacion();
};

void Ecuacion::pedirEcuacion(){
    cout << "INDIQUE EL MAYOR GRADO DE LA ECUACION: ";
    cin >> this->grado;

    //Lectura de coeficientes
    for (int i = this->grado; i >= 0; i--){
		cout << "Indica el coeficiente para el exponente " << i << " : "; 
		cin >> coeficiente[i];
	}
}

void Ecuacion::escribirEcuacion(){
    for (int i = this->grado; i>=0; i--){
        if ( i == 0 ){
            cout << coeficiente[i]; 
        }
        else{
            cout << coeficiente[i] << "X^" << i << "  ";
        }
    }
}

float Ecuacion::evaluarFuncion(float x){
    float tmp = 0;
    for (int i = grado; i >= 0; i--){
        i == 0 ? tmp += coeficiente[i] : tmp += coeficiente[i] * pow(x,i);
    }
    return tmp;
}

void imprimirBiseccion(int iter, float Xa, float Xb, float Xr, float Ep);

int main(){
    Ecuacion polinomio;
    polinomio.pedirEcuacion();


    float Xa, Xb, Xr_actual, Xr_anterior = 0;
    float Error; //Error Porcentual -> abs();
    bool cen = true;

    /*ENCONTRAR VALORES DE XA Y XB*/
    int ind = 0;
    do{
        Xa = ind;
        polinomio.evaluarFuncion(ind) <= 0 ? ind++ : ind--;
        Xb = ind;
        polinomio.evaluarFuncion(Xa) < 0 && polinomio.evaluarFuncion(Xb) > 0 ? cen = false : cen = true; 
    }while (cen);

    /*METODO BISECCION*/

    cout << "\n\n\tMETODO DE LA BISECCION\n\n";
    cout << "F(x) = "; polinomio.escribirEcuacion(); cout << "\n\n";
    cout << "#\tXa\t\tXb\t\tXr\t\tEp\n";
    int k = 1;
    do{
        Xr_actual = (Xa + Xb) / 2;
        Error = abs( ( (Xr_actual - Xr_anterior) / Xr_actual) * 100 );
        Error <= 1 && Error >= 0 ? cen = false : cen = true;
        
        imprimirBiseccion(k,Xa, Xb, Xr_actual, Error);

        polinomio.evaluarFuncion(Xa) * polinomio.evaluarFuncion(Xr_actual) > 0 ? Xa = Xr_actual : Xb = Xr_actual;
        Xr_anterior = Xr_actual;
        k++;
    }while (cen);
}

void imprimirBiseccion(int iter, float Xa, float Xb, float Xr, float Ep){
    cout << iter << "\t" << Xa << "\t\t" << Xb << "\t\t" << Xr << "\t\t";
    iter != 1 ? cout << Ep << " %\n" : cout << "-\n";
}