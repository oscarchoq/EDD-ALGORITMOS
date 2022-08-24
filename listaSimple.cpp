#include <iostream>

using namespace std;

class Nodo{
    public:
        int info = 0;
        Nodo *liga = NULL;
};

class Lista{
    public:
        Nodo *INICIO;
        /* METODOS */
        
        /* INSERCION EN LISTAS SIMPLEMENTE LIGADAS */
        void inserta_inicio(int DATO);
        void inserta_final(int DATO);
        void inserta_antes_X(int DATO, int X);
        void inserta_despues_X(int DATO, int X);
        
        /* ELIMINACION EN LISTAS SIMPLEMENTE LIGADAS */
        void elimina_inicio();
        void elimina_ultimo();
        void elimina_X(int X);
        void elimina_antes_X(int X);
        void elimina_despues_X(int X);
        
        void mostrar();
};

/* INSERCION EN LISTAS SIMPLEMENTE LIGADAS */

void Lista::inserta_inicio(int DATO)
{
    Nodo *P = INICIO;
    Nodo *Q = new Nodo();
    Q->info = DATO;
    Q->liga = INICIO;
    INICIO = Q;
}

void Lista::inserta_final(int DATO)
{
    Nodo *P = INICIO;
    Nodo *T = P;
    while (T->liga != NULL){
        T = T->liga;
    }
    Nodo *Q = new Nodo();
    Q->info = DATO;
    Q->liga = NULL;
    T->liga = Q;
}

void Lista::inserta_antes_X(int DATO, int X)
{
    Nodo *P = INICIO;
    Nodo *Q = P;
    Nodo *T = new Nodo();
    int BAND = 1;
    while ( (Q->info != X) && (BAND == 1) ){
        if (Q->liga != NULL){
            T = Q;
            Q = Q->liga;
        }
        else{
            BAND = 0;
        }
    }
    if (BAND == 1){
        Nodo *R = new Nodo();
        R->info = DATO;
        if (P == Q){
            R->liga = P;
            P = R;
        }
        else{
            T->liga = R;
            R->liga = Q;
        }
    }
    else{
        cout << "\nEL NODO DADO COMO REFERENCIA NO SE ENCUENTRA EN LA LISTA\n";
    }
    INICIO = P;
}

void Lista::inserta_despues_X(int DATO, int X)
{
    Nodo *P = INICIO;
    Nodo *Q = P;
    int BAND = 1;
    while ( (Q->info != X) && (BAND == 1) ){
        if (Q->liga != NULL){
            Q = Q->liga;
        }
        else{
            BAND = 0;
        }
    }
    if (BAND == 1){
        Nodo *T = new Nodo();
        T->info = DATO;
        T->liga = Q->liga;
        Q->liga = T;
    }
    else{
        cout << "\nEL NODO DADO COMO REFERENCIA NO SE ENCUENTRA EN LA LISTA\n";
    }
}

/* ELIMINACION EN LISTAS SIMPLEMENTE LIGADAS */

void Lista::elimina_inicio()
{

    Nodo *Q = INICIO;
    INICIO = Q->liga;
    delete Q;
    
}

void Lista::elimina_ultimo()
{
    Nodo *P = INICIO;
    Nodo *Q = P;
    Nodo *T = new Nodo();
    if (P->liga == NULL){ //VERIFICA SI LA LISTA TIENE UN SOLO NODO
        P = NULL;
    }
    else{
        while (Q->liga != NULL){
            T = Q;
            Q = Q->liga;
        }
        T->liga = NULL;
    }
    delete Q;
}

void Lista::elimina_X(int X)
{
    Nodo *P = INICIO;
    Nodo *Q = P;
    Nodo *T = new Nodo();
    int BAND = 1;
    while ( (Q->info != X) && (BAND == 1) ){
        if (Q->liga != NULL){
            T = Q;
            Q = Q->liga;
        }
        else{
            BAND = 0;
        }
    }
    if (BAND == 0){
        cout << "EL ELEMENTO CON INFORMACION 'X' NO SE ENCUENTRA EN LA LISTA\n";
    }
    else{
        if (P == Q){ //VERIFICA SI EL ELEMENTO A ELIMINAR ES PRIMERO
            P = Q->liga;
        }
        else{
            T->liga = Q->liga;
        }
        delete Q;
    }
}

void Lista::elimina_antes_X(int X)
{
    Nodo *P = INICIO;
    Nodo *Q, *T, *R;
    int BAND;
    if (P->info == X){
        cout << "NO EXISTE UN NODO QUE PRECEDA AL QUE CONTIENE A 'X' \n";
    }
    else{
        Q = P;
        T = P; 
        BAND = 1;
        while ( (Q->info != X) && (BAND == 1) ){
            if (Q->liga != NULL){
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
                P = Q;
            }
            else{
                R->liga = Q;
            }
            delete T;
        }
    }
}

void Lista::elimina_despues_X(int X)
{
    Nodo *P = INICIO;
    Nodo *Q, *T;
    int BAND;
    if (P->liga == NULL){
        cout << "\nNO EXISTE UN NODO POSTERIOR AL QUE CONTIENE A 'X'\n";
    }
    else{
        Q = P;
        BAND = 1;
        while ( (Q->info != X) && (BAND == 1) ){
            if (Q->liga != NULL){
                Q = Q->liga;
                T = Q->liga;
            }
            else{
                BAND = 0;
            }
        }
        if (Q == P){
            P->liga = P->liga->liga;
        }
        else{
            if (BAND == 0){
                cout << "\nEL ELEMENTO NO SE ENCUENTRA EN LA LISTA\n";
            }
            else{
                if (T != NULL){
                    Q->liga = T->liga;
                   delete T;
                }
                else{
                    cout << "\nNO HAY ELEMENTO A ELIMINAR\n";
                }
            }
        }
    }
}

/* MOSTRAR NODOS */
void Lista::mostrar()
{
    Nodo *P = INICIO;
    while (P != NULL){
        cout << P->info << endl;
        P = P->liga;
    }
}

int main()
{
    Nodo *P= new Nodo();
    P->info = 11;
    
    Lista *lista = new Lista();
    lista->INICIO = P;
    
    cout << "\nINSERCION EN LISTAS\n";
    lista->inserta_inicio(10);
    lista->inserta_final(14);
    lista->inserta_antes_X(13,14);
    lista->inserta_despues_X(12,11);
    lista->mostrar();
    
    cout << "\nELIMINACION EN LISTAS\n";
    lista->elimina_inicio();
    //lista->elimina_antes_X(14);
    //lista->elimina_ultimo();
    //lista->elimina_despues_X(11);
    //lista->elimina_X(14);
    
    lista->mostrar();

    return 0;
}