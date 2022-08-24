#include <iostream>
using namespace std;

class Nodo{
    public:
        int info = 0;
        Nodo *liga = NULL;
};

class ListaCircular{
    public:
        Nodo *INICIO = NULL;
        
        void inserta_inicio(int DATO);
        void inserta_final(int DATO);
        void inserta_antes_X(int DATO, int X);
        void inserta_despues_X(int DATO, int X);
        
        void elimina_inicio();
        void elimina_final();
        void elimina_X(int X);
        void elimina_antes_X(int X);
        void elimina_despues_X(int X);
        
        void mostrar();
};

////////////////////////////////////////////////////////////////////////////

void ListaCircular::inserta_inicio(int DATO){
    Nodo *P = INICIO;
    Nodo *Q = new Nodo();
    
    if (P == NULL){ //VACIO
        Q->info = DATO;
        Q->liga = Q;
        P = Q;
    }
    else{ //NO VACIO
        Q->info = DATO;
        
        //buscar el ultimo
        Nodo *F = P;
        while (F->liga != P){
            F = F->liga;
        }
        F->liga = Q;
        Q->liga = P;
        P = Q;
    }
    INICIO = P;
    
}

void ListaCircular::inserta_final(int DATO){
    //el docente implemento un inserta inicio
    Nodo *P = INICIO;
    Nodo *Q = new Nodo();
    
    //buscar el ultimo
    Nodo *F = P;
    while (F->liga != P){
        F = F->liga;
    }
    Q->info = DATO;
    F->liga = Q;
    Q->liga = P;
    
    
    INICIO = P;
}

void ListaCircular::inserta_antes_X(int DATO, int X){
    Nodo *P = INICIO;
    Nodo *Q = P;
    Nodo *T;
    int BAND = 1;
    while (Q->info != X && BAND == 1){
        if (Q->liga != P){
            T = Q;
            Q = Q->liga;
        }
        else{
            BAND = 0;
        }
    }
    if (BAND == 1){
        Nodo *N = new Nodo();
        N->info = DATO;
        if (P == Q){ //PRINER NODO
            
            //BUSCAR EL ULTIMO
            Nodo *F = P;
            while (F->liga != P){
                F = F->liga;
            }
            
            N->liga = P;
            P = N;
             
            F->liga = P;
        }
        else{
            T->liga = N;
            N->liga = Q;
        }
    }
    else{
        cout << "\nEL NODO DADO COMO REFERENCIA NO SE ENCUENTRA EN LA LISTA\n";
    }
    
    INICIO = P;
}

void ListaCircular::inserta_despues_X(int DATO, int X){
    Nodo *P = INICIO;
    Nodo *Q = P;
    int BAND = 1;
    while (Q->info != X && BAND == 1){
        if (Q->liga != P){
            Q = Q->liga;
        }
        else{
            BAND = 0;
        }
    }
    if (BAND == 1){ //ESTA EN EL PRIMERO?
        Nodo *T = new Nodo();
        T->info = DATO;
        T->liga = Q->liga;
        Q->liga = T;
    }
    else{
        cout << "EL NODO DADO COMO REFERENCIA NO SE ENCUENTRA EN LA LISTA\n";
    }
    
    INICIO = P;
}

///////////////////////////////////////////////////////////////////////////////

void ListaCircular::elimina_inicio(){
    Nodo *Q = INICIO;
    
    //BUSCAR EL ULTIMO
    Nodo *F = Q;
    if(F->liga == Q){
        INICIO = NULL;
    }
    else{
        while (F->liga != Q){
        F = F->liga;
        }
        INICIO = Q->liga;
        F->liga = INICIO;
    }
    

    //delete Q;
}

void ListaCircular::elimina_final(){
    Nodo *P = INICIO;
    Nodo *Q = P;
    Nodo *T = new Nodo();
    if (P->liga == P){ //VERIFICA SI LA LISTA TIENE UN SOLO NODO
        INICIO = NULL;//
    }
    else{
        while (Q->liga != P){
            T = Q;
            Q = Q->liga;
        }
        T->liga = P;
    }
    //delete Q;
}

void ListaCircular::elimina_X(int X){
    Nodo *P = INICIO;
    Nodo *Q = P;
    Nodo *T;
    int BAND = 1;
    while ( (Q->info != X) && (BAND == 1) ){
        if (Q->liga != P){
            T = Q;
            Q = Q->liga;
        }
        else{
            BAND = 0;
        }
    }
    if (BAND == 0){
        cout << "EL ELEMENTO CON INFMACION 'X' NO SE ENCUENTRA EN LA LISTA\n";
    }
    else{
        if (P == Q){ //VERIFICA SI EL ELEMENTO A ELIMINAR ES PRIMERO
        
            if(P->liga == P){ //TIENE SOLO 1 ELEMENTO
                P = NULL;
            }
            else{   //TIENE MAS DE 1 ASI QUE BUSCARA EL FINAL
                //BUSCAR EL ULTIMO
                Nodo *F = P;
                while (F->liga != P){
                    F = F->liga;
                }
            
                P = Q->liga;
                F->liga = P;
            }
        }
        else{
            T->liga = Q->liga;
        }
        //delete Q;
    }
    INICIO = P;
}

void ListaCircular::elimina_antes_X(int X){
    Nodo *P = INICIO;
    Nodo *Q, *T, *R;
    int BAND;
    if (P->info == X){//SI X ESTA AL INICIO
        
        
        if(P->liga == P){//SI TIENE SOLO 1 ELEMENTO
            P = NULL;
        }
        else{//SI TIENE MAS DE 1 ELEMENTO
            Nodo *F = P;
            T = P;
            while (F->liga != P){
               T = F;
               F = F->liga;
            }
            T->liga = P;
        }
    }
    else{//SI X NO ESTA EN LA INICIO
        Q = P;
        T = P; 
        BAND = 1;
        while ( (Q->info != X) && (BAND == 1) ){
            if (Q->liga != P){
                R = T;
                T = Q;
                Q = Q->liga;
            }
            else{
                BAND = 0;
            }
        }
        if (BAND == 0){
            cout << "EL ELEMENTO NO SE ENCUENTRA EN LA LISTA\n";
        }
        else{
            if (P->liga == Q){ //EL ELEMENTO A ELIMINAR ES EL PRIMERO
                //BUSCAR EL ULTIMO
                Nodo *F = P;
                while (F->liga != P){
                    F = F->liga;
                }
                P = Q;
                F->liga = P;
            }
            else{
                R->liga = Q;
            }
            //delete T;
        }
    }
    INICIO = P;
}

void ListaCircular::elimina_despues_X(int X){
    Nodo *P = INICIO;
    Nodo *Q = P;
    Nodo *T;
    int BAND = 1;
    
    while (Q->info != X && BAND == 1){
        if (Q->liga != P){
            Q = Q->liga; //Q->info = X;
        }
        else{
            BAND = 0;
        }
    }
    if(BAND == 0){
        cout << "\nEL NODO NO SE ENCUENTRA EN LA LISTA\n";
    }
    else{
        if (Q->liga == P){//ELIMINAR PRIMERO 
           if(P->liga == P){//SI TIENE 1 ELEMENTO
               P = NULL;
           }
           else{//SI TIENE MAS DE 1 ELEMENTO
               T = P->liga;
               Q->liga = T;
               P = T;
           }
        }
        else{
            T = Q->liga;
            Q->liga = T->liga;
            //delete T;
        }
    }
    INICIO = P;
}

///////////////////////////////////////////////////////////////////////////////

void ListaCircular::mostrar(){
    Nodo *P = INICIO;
    
    if (P != NULL){ //P tiene al menos un nodo
        Nodo *F = P;
        if (F->liga == P){ //Solo tiene 1 nodo
            cout << P->info << " -> ";
            cout << P->liga->info << endl; //Imprime la cola
        }
        else{ //P tiene 2 o mas nodos
            while (F->liga != P){
                cout << F->info << " -> ";
                F = F->liga;
                
            }
            cout << F->info << " -> ";
            cout << F->liga->info << endl; //Imprime la cola
            
        }
    }
}

int main()
{
    ListaCircular *list = new ListaCircular();
    
    
    list->inserta_inicio(5);
    list->inserta_inicio(2);
    list->inserta_final(18);
    //list->inserta_antes_X(100,18);
    //list->inserta_despues_X(101,18);
    list->mostrar();
    
    //list->elimina_inicio();
    //list->elimina_final();
    //list->elimina_X(18);
    list->elimina_antes_X(2);
    //list->elimina_despues_X(100);
    list->mostrar();

    return 0;
}