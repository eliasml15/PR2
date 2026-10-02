//
// Created by elias on 02/10/2026.
//

#ifndef PR2_LISTADENLAZADA_H
#define PR2_LISTADENLAZADA_H
template<typename T>
class Nodo {
public:
    T dato;
    Nodo *ant, *sig;

    Nodo(T &aDato, Nodo *aAnt,Nodo *aSig):dato(aDato),ant(aAnt),sig(aSig) {}
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
    void borrar(Iterador<T> &i);
    T &inicio() { return cabecera->dato; }
    T &final() { return cola->dato; }

};
template<typename T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada &l):cabecera(l->cabecera),cola(l->cola) {
    
}

template <typename T>
class Iterador {
    Nodo<T> *nodo;
    friend class ListaDEnlazada<T>;
public:
    Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}
    bool hayAnterior() { return nodo->ant != 0; }
    bool haySiguiente() { return nodo->sig != 0; }
    void anterior() { nodo = nodo->ant; }
    void siguiente() { nodo = nodo->sig; }
    T &dato() { return nodo->dato; }
};



#endif //PR2_LISTADENLAZADA_H