#include <iostream>
using namespace std;

class Nodo{
    public:
        int info;
        Nodo *ligaDer = NULL;
        Nodo *ligaIzq = NULL;
};

class ListaDoblementeLigada{
    public:
        Nodo *INICIO = NULL;
        Nodo *FIN = NULL;
        
        void inserta_inicio(int DATO);
        void inserta_final(int DATO);
        void inserta_antes_x(int DATO, int X);
        void inserta_despues_x(int DATO, int X);
        
        void elimina_inicio();
        void elimina_final();
        void elimina_x(int X);
        void elimina_antes_x(int X);
        void elimina_despues_x(int X);
        
        void mostrarDer();
        void mostrarIzq();
};

void ListaDoblementeLigada::inserta_inicio(int DATO){
    if (INICIO == NULL){
        Nodo *P = new Nodo();
        P->info = DATO;
        
        INICIO = P;
        FIN = P;
        
    }
    else{
        Nodo *P = INICIO;
        Nodo *Q = new Nodo();
        
        Q->info = DATO;
        Q->ligaDer = P;
        P->ligaIzq = Q;
        
        P = Q;
        INICIO = P;
    }
}

void ListaDoblementeLigada::inserta_final(int DATO){
    if (INICIO == NULL){
        return;
    }
    
    Nodo *F = FIN;
    Nodo *Q = new Nodo();
    Q->info = DATO;
    Q->ligaIzq = F;
    F->ligaDer = Q;
    
    FIN = Q;
}

void ListaDoblementeLigada::inserta_antes_x(int DATO, int X){
    //EL PUNTERO FIN NO SE MODIFICA
    
    if (INICIO == NULL){
        return;
    }
    
    Nodo *P = INICIO;
    Nodo *Q = P;
    
    while (Q->ligaDer != NULL && Q->info != X){
        Q = Q->ligaDer;
    }
    
    if (Q->info == X){
        Nodo *T = new Nodo();
        T->info = DATO;
        T->ligaDer = Q;
        
        Nodo *R = Q->ligaIzq;
        Q->ligaIzq = T;
        
        if (P == Q){  //TIENE UN SOLO NODO
            P = T;
            T->ligaIzq = NULL; //OPCIONAL
        }
        else{
            R->ligaDer = T;
            T->ligaIzq = R;
        }
    }
    else{
        cout << "EL NODO DADO COMO REFERENCIA NO SE ENCUENTRA EN LA LISTA\n";
    }
    INICIO = P;
    
}

void ListaDoblementeLigada::inserta_despues_x(int DATO, int X){
    Nodo *P = INICIO;
    Nodo *F = FIN;
    Nodo *Q = P;
    int BAND = 1;
    
    while (Q->info != X && BAND == 1){
        if (Q->ligaDer != NULL){
            Q = Q->ligaDer;
        }
        else{
            BAND = 0;
        }
    }
    
    if (BAND == 1){
        Nodo *T = new Nodo();
        T->info = DATO;
        T->ligaDer = Q->ligaDer;
        Q->ligaDer = T;
        
        T->ligaIzq = Q;
        if (Q == F){
            F = T;
        }
        else{
            T->ligaDer->ligaIzq = T;
        }
    }
    else{
        cout << "EL NODO DADO COMO REFERENCIA NO SE ENCUENTRA EN LA LISTA\n";
    }
    
    FIN = F;
}
        
void ListaDoblementeLigada::elimina_inicio(){
    Nodo *P = INICIO;
    Nodo *F = FIN;
    Nodo *Q = P;
    /*
    P = Q->ligaDer;
    
    if (P != NULL){ // VERIFICAMOS QUE HAY MAS DE 1 NODO
        P->ligaIzq = NULL;
    }
    INICIO = P;
    */
    
    if (Q->ligaDer != NULL){ //VERIFICAMOS QUE HAY MAS DE 1 NODO
        P = Q->ligaDer;
        P->ligaIzq = NULL;
    }
    else{
        P = NULL;
        F = NULL;
    }
    
    INICIO = P;
    FIN = F;
}

void ListaDoblementeLigada::elimina_final(){
    Nodo *P = INICIO;
    Nodo *F = FIN;
    Nodo *Q = F;
    
    if (Q->ligaIzq != NULL){ //VERIFICAMOS QUE HAY MAS DE 1 NODO
        F = Q->ligaIzq;
        F->ligaDer = NULL;
    }
    else{
        F = NULL;
        P = NULL;
    }
    
    INICIO = P;
    FIN = F;
}

void ListaDoblementeLigada::elimina_x(int X){
    Nodo *P = INICIO;
    Nodo *F = FIN;
    Nodo *Q = P;
    
    while ( (Q->ligaDer != NULL) && (Q->info != X) ){
        Q = Q->ligaDer;
    }
    
    if (Q->info == X){
        if ( (Q == P) && (Q == F) ){ //SOLO TIENE UN NODO
            P = NULL;
            F = NULL;
        }
        else{
            if (Q == P){ //ES EL PRIMERO
                P = Q->ligaDer;
                P->ligaIzq = NULL;
            }
            else{
                if (Q == F){ //ES EL ULTIMO
                    F = Q->ligaIzq;
                    F->ligaDer = NULL;
                }
                else{ //ES EL INTERMEDIO
                    Nodo *T = Q->ligaIzq;
                    Nodo *R = Q->ligaDer;
                    T->ligaDer = R;
                    R->ligaIzq = T;
                }
            }
        }
    }
    else{
        cout << "EL ELEMENTO CON INFORMACION X NO SE ENCUENTRA EN LA LISTA\n";
    }
    
    INICIO = P;
    FIN = F;
}

void ListaDoblementeLigada::elimina_antes_x(int X){
    Nodo *P = INICIO;
    Nodo *Q = P;
    
    while ( (Q->ligaDer != NULL) && (Q->info != X) ){
        Q = Q->ligaDer;
    }
    
    if (Q->info == X){
        if (Q == P){
            cout << "NO EXISTE NODO ANTERIOR AL PRIMERO\n";
        }
        else{
            Nodo *T = Q->ligaIzq;
            if (P == T){ //ES PRIMER NODO
                P = Q;
                P->ligaIzq = NULL;
            }
            else{
                Nodo *R = T->ligaIzq;
                Q->ligaIzq = R;
                R->ligaDer = Q;
            }
        }
    }
    else{
        cout << "EL ELEMENTO CON INFORMACION X NO SE ENCUENTRA EN LA LISTA\n";
    }
    
    INICIO = P;
}

void ListaDoblementeLigada::elimina_despues_x(int X){
    Nodo *F = FIN;
    Nodo *P = INICIO;
    Nodo *Q = P;
    
    while ( (Q->ligaDer != NULL) && (Q->info != X) ){
        Q = Q->ligaDer;
    }
    
    if (Q->info == X){
        if (Q == F){
            cout << "NO EXISTE NODO DESPUES DE X\n";
        }
        else{
            Nodo *T = Q->ligaDer;
            if (T == F){ //ULTIMO NODO
                F = Q;
                F->ligaDer = NULL;
            }
            else{
                Nodo *tmp = T->ligaDer;
                Q->ligaDer = tmp;
                tmp->ligaIzq = Q;
            }
        }
    }
    else{
        cout << "EL ELEMENTO CON INFORMACION X NO SE ENCUENTRA EN LA LISTA\n";
    }
    
    INICIO = P;
    FIN = F;
}

        
void ListaDoblementeLigada::mostrarDer(){
    Nodo *P = INICIO;
    while (P != NULL){
        cout << P->info << "->";
        P = P->ligaDer;
    }
}

void ListaDoblementeLigada::mostrarIzq(){
    Nodo *F = FIN;
    while (F != NULL){
        cout << "<-" << F->info;
        F = F->ligaIzq;
    }
}

int main()
{
    ListaDoblementeLigada *lista = new ListaDoblementeLigada();
    cout << "\nLISTA DOBLEMENTE ENLAZADA\n\n";
    cout << "INSERCION EN LISTAS\n\n";
    lista->inserta_inicio(12);
    lista->inserta_final(15);
    lista->inserta_antes_x(13,12);
    lista->inserta_despues_x(16,15);
    lista->mostrarDer();
    cout << endl;
    lista->mostrarIzq();
    
    cout << "\n\nELIMINACION EN LISTAS\n\n";
    lista->elimina_inicio();
    //lista->elimina_final();
    //lista->elimina_x(15);
    //lista->elimina_antes_x(15);
    //lista->elimina_despues_x(12);
    lista->mostrarDer();
    cout << endl;
    lista->mostrarIzq();


    return 0;
}