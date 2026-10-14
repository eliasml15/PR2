#ifndef PR1_LISTAENLAZADA_H
#define PR1_LISTAENLAZADA_H
#include <stdexcept>


template <class T>
class ListaDEnlazada {
    //Clase Nodo
    template<typename X>
class Nodo {
    public:
        X dato;
        Nodo *ant, *sig;

        Nodo(const  X &aDato, Nodo *aAnt=0,Nodo *aSig=0):dato(aDato),ant(aAnt),sig(aSig) {} //Constructor parametrizado. Le pasamos en el primer parametro, un valor por referencia que contiene los datos que almacenaremos
        ~Nodo(){}
    };

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
    ListaDEnlazada<T> &operator=(const ListaDEnlazada<T> &arr); //oeporador asoignacion

    T& inicio(); //Obtenemos el nodo inicial
    T& final(); //Obtenemos el nodo final

    unsigned tam(); //nos devolvera la cantidad de nodod

    ListaDEnlazada<T>::Iterador iterador() const; //con este metodo, podremos colocar un puntero a la primera direccion para poder recorrer todos los nodos
    ListaDEnlazada<T>::Iterador iteradorR() const;

    void insertarInicio(const T& dato); //para insertar un nuevo nodo por el inicio
    void insertarFinal(const T& dato); //para insertar un nuevo nodo por el final

    void insertar(const Iterador &p,const T &dato); //para insertar en la posicion anterior a la que apunta p

    void borrarInicio(); //borra el elemento del innicio
    void borrarFinal(); //borra el elemento del final

    void borrar(Iterador &p);  //borrar cualquier elemento que nos diga un iterador

    ListaDEnlazada<T> concatena(const ListaDEnlazada<T> &l) const;
    ListaDEnlazada<T> operator+(const ListaDEnlazada<T> &l) const; //necesario para el concatena

    ~ListaDEnlazada(); //destructor
};

//Implementacion
template <class T>
ListaDEnlazada<T>::ListaDEnlazada() : cabecera(0), cola(0), tamanio(0){}

template <class T>
//Recordamos que en el de copia, tenemos un solo objeto, el otro es de nueva creacaion
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada &origen):tamanio(0) {
    // Inicializamos los miembros de la nueva lista como una lista vacía
    cabecera = nullptr;
    cola = nullptr;

    // Creación de un puntero auxiliar para recorrer la lista origen 'l'
    // Empezamos en el primer nodo de la lista a copiar, por eso añadimos el origen
    Nodo<T> *p = origen.cabecera;

    // Recorremos toda la lista origen hasta llegar al final (nullptr)
    while (p != nullptr) {
        // Insertamos el dato del nodo actual al final de nuestra nueva lista.
        // Utilizando el método de nuestra clase insertaFin.
        // (Nota: se puede crear el nodo manualmente, pero usar insertaFin
        // nos evita rehacer la lógica de enganche de punteros ant y sig).
        insertarFinal(p->dato);

        //Avanzamos al siguiente nodo de la lista origen 'l'
        p = p->sig;
    }
}

//Aqui recordamos que ya tenemos los dos objetos creados, entonces lo que tenemos qeu tener en cuetna es que tenemos que eliminar
//los datos del nodo b en primer lugar.
template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(const ListaDEnlazada<T> &orig) {
    if (this!=&orig) {

        //vaciamos la lista hasta que cabecera sea nullptr
        while (cabecera != nullptr) {
            borrarInicio();
        }

        // Creamos un nuevo puntero que apuntará a la cabecera de la lista a copiar
        Nodo<T> *p = orig.cabecera;
        while (p != nullptr) {
            insertarFinal(p->dato);
            p = p->sig;
        }
    }

    return *this;
}

//Los metodos iniciio y fin, permiten tanto leer como escribir.
//Tenemos que tener un control de excepciones, por si la lista esta vacia
//Se devuelve una refencia al dato guardado en el nodo
template<class T>
T& ListaDEnlazada<T>::inicio(){
    if (cabecera==nullptr)
        throw std::logic_error("No existe valor inicial");
    return cabecera->dato; //Lanzamos el dato almacenado en el primer nodo apuntado por la cabecera
};

template<class T>
T& ListaDEnlazada<T>::final(){
    if (cola==nullptr)
        throw std::logic_error("No existe valor final");
    return cola->dato; //Lanzamos el dato almacenado en el ultimo nodo apuntado por cola
};

//Con este metodo, conseguiremos un puntero que se colocara en el primer nodo de la lista
//En caso de que la lista este vacia, nos devolvera un valor nulo
template<class T>
typename ListaDEnlazada<T>::Iterador ListaDEnlazada<T>::iterador() const {
    return Iterador (cabecera); //aqui le pasamos la adireccion del primer nodo al constructor de la clase iterador, para que este haga nodo=cabecera
}

template<class T>
typename ListaDEnlazada<T>::Iterador ListaDEnlazada<T>::iteradorR() const {
    return Iterador (cola);
}

//Tenemos que tener en cuenta, que tenemos que modificar la cabecera, de manera que ahora apunte al nuevo nodo.
//El puntero anterior del nuevo, debe apuntar a nulo
//El puntero siguiente del nuevo, debe apuntar al siguiente nodo (al que apuntaba originalemtne la cabecera)
//El puntero anterior del que antes era el primero, debe apuntar al nuevo nodo
//Tenemso que capturar la excepcion de esta la lista vacia
template <class T>
    void ListaDEnlazada<T>::insertarInicio(const T &dato ){
        Nodo<T> *nuevo=new Nodo<T>(dato,0,cabecera);  //Creamos un nuevo nodo, que nace directamente con la direccion del primer nodo (que pasara a ser el segundo) y nace con anterior=0.

      //Si la lista está vacía
        if (cola==0) {
            cola=nuevo; //el nuevo nodo, tambien será por tanto cola
        }
        //Si la lista tenia elementos
        if (cabecera!=0) {
            cabecera->ant=nuevo; //Enganchamos el antiguo primer nodo, con el nuevo nodo
        }

        cabecera=nuevo; //El nuevo nodo es la cabecera
        tamanio++; //añadimos un elemento mas

}

//Procedimiento similar
//Tenemos que enganchar siguiente del ultimo al nuevo nodo. El anterior del nuevo ya nace con la direccion del anterior nodo.
template <class T>
    void ListaDEnlazada<T>::insertarFinal(const T &dato) {
        Nodo<T> *nuevo=new Nodo<T>(dato,cola,0); //Este nuevo nodo, tendra el dato, anterior=cola, siguiente=0

        //Si la lista esta vacia
        if (cabecera==0) {
            cabecera=nuevo; //la cabecera sera el nuevo nodo
        }

        if (cola!=0)
            cola->sig=nuevo; //reajustamos el que era nodo antiguo, para que apunte al nuevo nodo final

        cola=nuevo; //reajustamos finalmente la cola para que apunte al nuevo nodo final
        tamanio++;
    }

//En este nuevo metodo, tenemos un puntero que apunta  a un nodo
//tendremos que insertar el nuevo justo antes del nodo apuntado
    //En cualquier otro caso, inserccion intermedia
template <class T>
void ListaDEnlazada<T>::insertar(const Iterador &p, const T &dato) {
    if (cabecera==0 || p.nodo==cabecera) {
        insertarInicio(dato);
    } else if (p.nodo==nullptr) {
        insertarFinal(dato);
    } else {
        Nodo<T> *ant = p.nodo->ant;
        Nodo<T> *q = p.nodo;

        Nodo<T> *nuevo = new Nodo<T>(dato, ant, q);
        ant->sig = nuevo;
        q->ant = nuevo;

        tamanio++;
    }
}



//Si borramos el  nodo del inicio, tenemos que hacer que el nodo segundo, apunte a null el anterior
//reaustemos la cabecera
//excepcion para la lista vacia
template<class T>
void ListaDEnlazada<T>::borrarInicio(){
    //en caso de que la lista este vacia
    if (cabecera==0) {
        throw std::out_of_range("Error, lista vacia");
    }
     Nodo<T> *borrado = cabecera; //Creamos un puntero para tener localizado al nodo que vamos a borrar

     //en caso de que haya un solo elemento
     if(cabecera==cola){
        cabecera=nullptr;
        cola=nullptr;
     }else{ //hay mas de un nodo
        cabecera= cabecera->sig; //Movemos la cabecera ahora al segundo nodo, que sera el nuevo primero
        cabecera->ant=0;
     }
        delete borrado;
        tamanio--;
}


//La misma logica, hay que reajustar ahora la cola
template<class T>
void ListaDEnlazada<T>::borrarFinal(){
    if (cola == 0) {
        throw std::out_of_range("Error, lista vacia");
    }
    Nodo<T> *borra = cola;

    if (cabecera == cola) {   // un solo elemento
        cabecera = nullptr;
        cola = nullptr;
    } else {                   // mas de un elemento
        cola = cola->ant;       // la cola retrocede al penultimo nodo
        cola->sig = nullptr;    // el nuevo ultimo nodo ya no tiene nada detras
    }

    delete borra;
    tamanio--;
}

//ahora tenemos un iterador apuntando a un elemento que vamos a borrar
template<class T>
void ListaDEnlazada<T>::borrar(Iterador &p) {
    // Si el iterador es nulo o la lista está vacía, no hacemos nada
    if (p.nodo == 0 || cabecera == 0) {
        throw std::out_of_range("Error");
    }
        // Guardamos el puntero al nodo que vamos a borrar
        Nodo<T> *aBorrar = p.nodo;

        // Avanzamos el iterador al siguiente nodo ANTES de borrarlo
        // para que no quede apuntando a memoria destruida
        p.nodo = p.nodo->sig;


        if (aBorrar == cabecera) {
            borrarInicio();
        }
        else if (aBorrar == cola) {
            borrarFinal();  // Ya gestiona cola, cabecera (si sólo había 1), delete y tama--
        }
        else{
            // Caso intermedio
            aBorrar->ant->sig = aBorrar->sig;
            aBorrar->sig->ant = aBorrar->ant;

            delete aBorrar;
            tamanio--;
        }
}

template<class T>
unsigned ListaDEnlazada<T>::tam() {
    return tamanio;
};

template <class T>
ListaDEnlazada<T> ListaDEnlazada<T>::concatena(const ListaDEnlazada<T> &l) const {
    ListaDEnlazada<T> resultado; // Lista nueva donde guardamos la union

    // Recorremos la lista actual *this usando un contador i
    typename ListaDEnlazada<T>::Iterador it1 = this->iterador();
    for (unsigned int i = 0; i < tamanio; i++) {
        resultado.insertarFinal(it1.dato());
        it1.siguiente();
    }

    // Recorremos la lista pasada por parámetro l usando un contador i
    typename ListaDEnlazada<T>::Iterador it2 = l.iterador();
    for (unsigned int i = 0; i < l.tamanio; i++) {
        resultado.insertarFinal(it2.dato());
        it2.siguiente();
    }

    return resultado;
}

template <class T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator+(const ListaDEnlazada<T> &l) const {
    return this->concatena(l); // Llama al método concatena directamente
}
//VAMOS APROVECHAR LA CREACION DEL MOTO BORRARINICIIO, para ir borrando nodos de las listas
template <class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
//En caso de que la lista ya este vacía, cabecera sera 0, luego no entrará al bucle while
  while(cabecera!= nullptr){
    borrarInicio();  //Ademas, como el metodo ya se encarga tanto de mover cabecera, poner tamanio=0, cola=0....no hace falta que lo hagmamos nosotros
  }
}

#endif //PR1_LISTAENLAZADA_H
