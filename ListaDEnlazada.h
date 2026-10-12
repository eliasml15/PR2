//
// Created by elias on 02/10/2026.
//

#ifndef PR2_LISTADENLAZADA_H
#define PR2_LISTADENLAZADA_H

#include "VDinamico.h"

//Clase Nodo
template<typename X>
class Nodo {
public:
    X dato;
    Nodo *ant, *sig;

    Nodo(const  X &aDato, Nodo *aAnt=0,Nodo *aSig=0):dato(aDato),ant(aAnt),sig(aSig) {} //Constructor parametrizado. Le pasamos en el primer parametro, un valor por referencia que contiene los datos que almacenaremos
    ~Nodo(){}
};

template <class T>
class ListaDEnlazada {
private:

    Nodo<T> *cabecera, *cola;
    unsigned int tamanio; //esto nos llevará la cuenta de cuantos nodos hay actualmente

public:
//IMPLEMENTACION DE LA CLASE ITERADOR

class Iterador {
    public:
        Nodo<T> *nodo;
        //friend class ListaDEnlazada<I>; //hay que usar friend class pq esta fuera de ListaD<T>
        Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}
        //añadido
        bool fin(){return nodo==0;}
        bool hayAnterior() { return nodo->ant != 0; }
        bool haySiguiente() { return nodo->sig != 0; }
        void anterior() { nodo = nodo->ant; }
        void siguiente() { nodo = nodo->sig; }
        T &dato() { return nodo->dato; }
        ~Iterador(){}
    };


public:
    ListaDEnlazada(); //defecto
    ListaDEnlazada(const ListaDEnlazada<T> &l); //copia
    ListaDEnlazada<T> &operator=(const VDinamico<T> &arr); //oeporador asoignacion

    T& inicio(); //Obtenemos el nodo inicial
    T& final(); //Obtenemos el nodo final

    unsigned tam(); //nos devolvera la cantidad de nodod

    Iterador iterador(); //con este metodo, podremos colocar un puntero a la primera direccion para poder recorrer todos los nodos
    Iterador iteradorR();

    void insertaInicio(const T& dato); //para insertar un nuevo nodo por el inicio
    void insertaFin(const T& dato); //para insertar un nuevo nodo por el final

    void inserta(Iterador &p,const T &dato); //para insertar en la posicion anterior a la que apunta p

    void borraInicio(); //borra el elemento del innicio
    void borraFinal(); //borra el elemento del final

    void borra(Iterador &p);  //borrar cualquier elemento que nos diga un iterador

    ListaDEnlazada<T> concatena(const ListaDEnlazada<T> &l);
    ListaDEnlazada<T> operator+(const ListaDEnlazada<T> &l); //necesario para el concatena

    ~ListaDEnlazada(); //destructor
};

//Implementacion
template <class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada &origen):tamanio(0) {
    // Inicializamos los miembros de la nueva lista como una lista vacía
    cabecera = nullptr;
    cola = nullptr;

    // Creación de un puntero auxiliar para recorrer la lista origen 'l'
    // Empezamos en el primer nodo de la lista a copiar
    Nodo<T> *p = origen.cabecera;

    // Recorremos toda la lista origen hasta llegar al final (nullptr)
    while (p != nullptr) {
        // Insertamos el dato del nodo actual al final de nuestra nueva lista.
        // Utilizando el método de nuestra clase insertaFin.
        // (Nota: se puede crear el nodo manualmente, pero usar insertaFin
        // nos evita rehacer la lógica de enganche de punteros ant y sig).
        insertaFin(p->dato);

        //Avanzamos al siguiente nodo de la lista origen 'l'
        p = p->sig;
    }
}

template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(const ListaDEnlazada<T> &l) {
    Nodo<T> *p=cabecera;

    while (p!=0){
        borraInicio();
        p=cabecera;
    }
    cabecera=0;
    cola=0;
    p=l.cabecera;
    tamanio=0;
    while (p!=0){
        insertarFinal(p->dato);
        p=p->sig;
    }
    return (*this);
}


template <class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    if (cabecera){
        Nodo<T> *borra=cabecera;
        while (borra) {
            cabecera=cabecera->sig;
            delete borra;
            borra=cabecera;
        }
        cola=cabecera=0;
        tamanio=0;
    }
}

template <class T>
    void ListaDEnlazada<T>::insertarInicio(T &dato){
        Nodo<T> *nuevo=new Nodo<T>(dato,0,cabecera);
        if (cola==0) {
            cola=nuevo;
        }
        if (cabecera!=0) {
            cabecera->ant=nuevo;
        }
        cabecera=nuevo;
        tamanio++;

}
template <class T>
    void ListaDEnlazada<T>::insertarFinal(T &dato) {
        Nodo<T> *nuevo=new Nodo<T>(dato,cola,0);
        if (cabecera==0) {
            cabecera=nuevo;
        }
        if (cola!=0)
            cola->sig=nuevo;
        cola=nuevo;
        tamanio--;
    }

    //< Inserta antes del nodo que indica el iterador
template <class T>
void ListaDEnlazada<T>::insertar(const Iterador &i, T &dato) {
        if (cabecera==0) {
            insertarInicio(dato);
        }else {
            if (i.nodo!=0) {
                Nodo<T> *nuevo=new Nodo<T>(dato,i.nodo->ant,i.nodo);
                Nodo<T> *p,*q;

                p=i.nodo->ant; q=i.nodo;
                if (p==0) {
                    cabecera=nuevo;
                }else
                    p->sig=nuevo;
                q->ant=nuevo;
            }
        }
}

template<class T>
ListaDEnlazada<T>::Iterador ListaDEnlazada<T>::iterador()  {
    return ListaDEnlazada<T>::Iterador(cabecera);
}

template<class T>
ListaDEnlazada<T>::Iterador ListaDEnlazada<T>::iteradorR()  {
    return Iterador(cola);
}

template<class T>
void ListaDEnlazada<T>::borrarInicio(){
    if (cabecera) {
        tamanio--;
        Nodo<T> *borrado = cabecera;
        cabecera= cabecera->sig;
        delete borrado;
        // Caso especial al
        // borrar el �ltimo nodo
        if (cabecera != 0)
            cabecera->ant = 0;
        else
            cola = 0;
    }
}

template<class T>
void ListaDEnlazada<T>::borrarFinal(){
    if (cola) {
        tamanio--;
        Nodo<T> *borrado = cola;
        cola= cola->ant;
        delete borrado;
        // Caso especial al
        // borrar el �ltimo nodo
        if (cola != 0)
            cola->sig = 0;
        else
            cabecera = 0;
    }
}

template<class T>
void ListaDEnlazada<T>::borrar(ListaDEnlazada<T>::Iterador &p){

    if (p.nodo!=0 && cabecera !=0){
        if (cabecera==cola){
            cabecera=cola= 0;
        } else {
            if (p.nodo==cabecera){    //Tb con BorrarInicio()
                cabecera=cabecera->sig;
                p.nodo->sig->ant=0;

            } else {
                if (p.nodo==cola){   //Tb con BorrarFinal()
                    cola=cola->ant;
                    p.nodo->ant->sig=0;

                } else{
                    p.nodo->ant->sig=p.nodo->sig;
                    p.nodo->sig->ant=p.nodo->ant;
                }
            }
        }
        delete p.nodo;
        tamanio--;
    }
}

template<class T>
T & ListaDEnlazada<T>::inicio(){
    if (!cabecera)
        throw std::logic_error("No existe valor inicial");
    return cabecera->dato;
};

template<class T>
T & ListaDEnlazada<T>::final(){
    if (!cola)
        throw std::logic_error("No existe valor final");
    return cola->dato;
};

template<class T>
unsigned ListaDEnlazada<T>::tam() {
    return tamanio;
};

/**
//< Si ponemos clases dentro de otras el typename T hay q cambiarlo a typename X por ej, como el for i for j
//< Ponemos las clases dentro, fuera? public?

template<typename T>
class ListaDEnlazada {

    template<typename U>
class Nodo {
    public:
        U dato;
        Nodo *ant, *sig;
        //FIXME: ANADIR EL CONST EN LA V.FINAL
        Nodo(const U &aDato, Nodo *aAnt,Nodo *aSig):dato(aDato),ant(aAnt),sig(aSig) {}
        ~Nodo(){}
    };

    template <typename V>
class Iterador {
        Nodo<T> *nodo;
        friend class ListaDEnlazada; //hay que usar friend class pq esta fuera de ListaD<T>
    public:
        Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}
        //añadido
        bool fin(){return nodo==0;}
        bool hayAnterior() { return nodo->ant != 0; }
        bool haySiguiente() { return nodo->sig != 0; }
        void anterior() { nodo = nodo->ant; }
        void siguiente() { nodo = nodo->sig; }
        T &dato() { return nodo->dato; }
        ~Iterador(){}
    };

    Nodo<T> *cabecera, *cola;

public:
    ListaDEnlazada() : cabecera(0), cola(0) {}
    ListaDEnlazada(const ListaDEnlazada<T> &l);
    ~ListaDEnlazada();
    ListaDEnlazada &operator=(ListaDEnlazada &l);
    Iterador<T> iteradorInicio() { return Iterador<T>(cabecera); }
    Iterador<T> iteradorFinal() { return Iterador<T>(cola); }
    void insertarInicio(T &dato);
    void insertarFinal(T &dato);
    void insertar(Iterador<T> &i, T &dato);
    void borrarInicio();
    void borrarFinal();
    void borrar(Iterador<T> &i); //borrar, hay que tener en cuenta que pasa si hay un unico nodo cabecera=cola=0;
    T &inicio() { return cabecera->dato; }
    T &final() { return cola->dato; }

};

template<typename T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T> &l) : cabecera(nullptr), cola(nullptr) {
    Nodo<T> *p = l.cabecera;
    while (p != nullptr) {
        insertarFinal(p->dato);
        p = p->sig;
    }
}

template<typename T>
ListaDEnlazada<T>~ListaDEnlazada() {

}

template<typename T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(ListaDEnlazada &l) {

}
template<typename T>
void ListaDEnlazada<T>::insertarInicio(T &dato) {
    Nodo<T> *nuevo=new Nodo<T>(dato,0,cabecera);
    if (cola==0) {
        cola=nuevo;
    }
    if (cabecera!=0) {
        cabecera->ant=nuevo;
    }
    cabecera=nuevo;
}
template<typename T>
void ListaDEnlazada<T>::insertarFinal(T &dato) {
    Nodo<T> *nuevo=new Nodo<T>(dato,cola,0);
    if (cabecera==0) {
        cabecera=nuevo;
    }
    if (cola!=0)
        cola->sig=nuevo;
    cola=nuevo;
}

//< Inserta antes del nodo que indica el iterador
template<typename T>
//FIXME:EL CONST EN ITERADOR &I
void ListaDEnlazada<T>::insertar(const Iterador &i, T &dato) {
    if (cabecera==0) {
        insertarInicio(dato);
    }else {
        if (i.nodo!=0) {
            Nodo<T> *nuevo=new Nodo<T>(dato,i.nodo->ant,i.nodo);
            Nodo<T> *p,*q;

            p=i.nodo->ant; q=i.nodo;
            if (p==0) {
                cabecera=nuevo;
            }else
                p->sig=nuevo;
            q->ant=nuevo;
        }
    }
}

//< Concatena y operador+ PREGUNTAR
**/
#endif //PR2_LISTADENLAZADA_H