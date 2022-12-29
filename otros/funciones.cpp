#include <iostream>
#include <cmath>
using namespace std;

class Ecuacion{
    public:
        int grado;
        float coeficiente[20];
        float derivada[20];
        float derivada2[20];
        float evaluarFuncion(float x);
        float evaluarDerivada(float x);
        float evaluarDerivada2(float x);

        void Hallarderivada();
        void Hallarderivada2();
        void pedirEcuacion();
        void escribirEcuacion(int i);
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

void Ecuacion::escribirEcuacion(int i){
    switch (i){
        case 1:
            for (int i = this->grado; i>=0; i--){
                if ( i == 0 ){
                    cout << coeficiente[i]; 
                }
                else{
                    cout << coeficiente[i] << "X^" << i << "  ";
                }
            }
         break;
        case 2:
            for (int i = this->grado-1; i>=0; i--){
                if ( i == 0 ){
                    cout << derivada[i]; 
                }
                else{
                    cout << derivada[i] << "X^" << i << "  ";
                }
            }
         break;
        case 3:
            for (int i = this->grado-2; i>=0; i--){
                if ( i == 0 ){
                    cout << derivada2[i]; 
                }
                else{
                    cout << derivada2[i] << "X^" << i << "  ";
                }
            }
         break;
    }
}

void Ecuacion::Hallarderivada(){
    for (int i = grado; i >= 0; i--){
        if (i != 0){
            this->derivada[i-1] = i * coeficiente[i]; 
        }
    }
}

void Ecuacion::Hallarderivada2(){
    for (int i = grado-1; i >= 0; i--){
        if (i != 0){
            this->derivada2[i-1] = i * derivada[i]; 
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

float Ecuacion::evaluarDerivada(float x){
    float tmp = 0;
    for (int i = grado; i >= 0; i--){
        i == 0 ? tmp += derivada[i] : tmp += derivada[i] * pow(x,i);
    }
    return tmp;
}

float Ecuacion::evaluarDerivada2(float x){
    float tmp = 0;
    for (int i = grado; i >= 0; i--){
        i == 0 ? tmp += derivada2[i] : tmp += derivada2[i] * pow(x,i);
    }
    return tmp;
}

int main(){
    Ecuacion m;
    m.pedirEcuacion();
    m.escribirEcuacion(1);
    cout << "\nFuncion evaluada en 1.2: " << m.evaluarFuncion(1.2);
    cout << endl;

    m.Hallarderivada();
    m.escribirEcuacion(2);
    cout << "\nFuncion evaluada en 1.2: " << m.evaluarDerivada(1.2);
    cout << endl;

    cout << endl;
    
    m.Hallarderivada2();
    m.escribirEcuacion(3);
    cout << "\nFuncion evaluada en 1.2: " << m.evaluarDerivada2(1.2);
    cout << endl;

}