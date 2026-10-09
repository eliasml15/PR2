//
// Created by elias on 02/10/2026.
//

#ifndef PR2_LISTADENLAZADA_H
#define PR2_LISTADENLAZADA_H
//< Si ponemos clases dentro de otras el typename T hay q cambiarlo a typename X por ej, como el for i for j
//< Ponemos las clases dentro, fuera? public?
template<typename T>
class Nodo {
public:
    T dato;
    Nodo *ant, *sig;

    Nodo(T &aDato, Nodo *aAnt,Nodo *aSig):dato(aDato),ant(aAnt),sig(aSig) {}
    ~Nodo(){}
};




template<typename T>
class ListaDEnlazada {
    Nodo<T> *cabecera, *cola;
public:
    ListaDEnlazada() : cabecera(0), cola(0) {}
    ListaDEnlazada(const ListaDEnlazada &l);
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
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada &l):cabecera(l.cabecera),cola(l.cola) {
    Nodo<T> *p=cabecera->sig;
    while (cola!=p->sig) {
        if (p!=nullptr) {
            p=new Nodo<T>;
            p=p->sig;
        }
    }
    if (cola==p->sig) {

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
void ListaDEnlazada<T>::insertar(Iterador &i, T &dato) {
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



template <typename T>
class Iterador {
    Nodo<T> *nodo;
    friend class ListaDEnlazada<T>; //hay que usar friend class pq esta fuera de ListaD<T>
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


#endif //PR2_LISTADENLAZADA_H