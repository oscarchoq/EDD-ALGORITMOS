#include <iostream>
#include <cmath>
using namespace std;


//DEFINIR LOS DESPEJES DE LAS FUNCIONES
//NO ENCONTRE OTRA MANERA ;( 
double evaluarFxy(double x, double y){ //Punto fijo multivariable
    return (pow(x,2) + pow(y,2) + 8)/10;
} 

double evaluarGxy(double x, double y){ //Punto fijo multivariable
    return (x*pow(y,2) + x + 8)/10;
} 

int main(){
    double Error, ErrorCal, x, y, xi, yi;
    bool cen = true;
    int i = 1;

    Error = 0.001; //Se puede pedir en caso sea necesario
    x = 0; y = 0;

    do{
        xi = evaluarFxy(x,y); yi = evaluarGxy(x,y);

        ErrorCal = abs(/*raiz*/pow(/*(Xi-Xi-1)^2*/pow(xi-x, 2) + /*(Yi-Yi-1)^2*/pow(yi-y, 2) , 0.5) );

        cout << "\nX" << i << " = " << xi << "\tY" << i << " = " << yi << "\t" << ErrorCal << " < " << Error;

        //if (ErrorCal < Error){ cen = false; }
        
        i++;
        x = xi; y = yi;
    }while (ErrorCal > Error);
}