/**
 * @file VDinamico.h
 * @brief Declaracion e implementacion de la clase plantilla VDinamico (vector dinamico).
 * @author Carlos y Elias
 * @date 18/09/2026
 */

#ifndef PR1_VDINAMICO_H
#define PR1_VDINAMICO_H
#include <climits>
#include <exception>
#include <algorithm>
#include <stdexcept>


template<typename T>
class VDinamico {
    T *v=nullptr;   ///< Puntero al array dinamico de datos.
    unsigned int tamfisico; ///< Tamanio fisico (capacidad reservada para una potencia de 2)
    unsigned int tamlogico; ///< Tamanio logico (numero de elementos utiles).

public:
    /**
    * @brief Constructor por defecto. Tamanio logico 0 y fisico 1.
    */
    VDinamico();

    /**
     * @brief Constructor parametrizado.
     * @param tamlog Tamanio logico inicial. El fisico sera la potencia de 2  igual o inmediatamente superior.
     * @param dato   Valor con el que se rellenan los tamlog elementos.
     */
    VDinamico(unsigned int n, T &dato);

    /**
    * @brief Constructor de copia.
    * @param origen Vector que se copia.
    */
    VDinamico(const VDinamico<T> &origen);

    /**
     * @brief Constructor de copia parcial/semicopia.
     * @param origen Vector del que se copia.
     * @param posicionInicial Primera posicion logica a copiar.
     * @param numElementos    Numero de elementos a copiar.
     * @throw std::out_of_range Si el rango solicitado se sale del tamanio logico de origen.
     */
    VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial, unsigned int numElementos);

    /**
     * @brief Destructor. Libera la memoria del array dinamico.
     */
    ~VDinamico();

    /**
    * @brief Operador de asignacion.
    * @param arr Vector del que se copian los datos.
    * @return Referencia al propio objeto (permite el encadenamiento).
    */
    VDinamico<T> &operator=(const VDinamico<T> &arr);

    /**
     * @brief Acceso a un dato para lectura o escritura.
     * @param posicion Posicion logica del dato.
     * @return Referencia al dato en la posicion pos.
     * @throw std::out_of_range Si pos >= tamanio logico.
     */
    T& operator[](unsigned int posicion);

    /**
     * @brief Inserta un dato en una posicion.
     * @param dato Dato a insertar.
     * @param pos  Posicion de insercion. Si vale UINT_MAX se inserta al final.
     * @throw std::out_of_range Si pos es mayor que el tamanio logico.
     */
    void insertar(const T& dato, unsigned int pos=UINT_MAX);

    /**
     * @brief Elimina un dato de una posicion.
     * @param pos Posicion a borrar. Si vale UINT_MAX se elimina el ultimo dato.
     * @return Copia del dato eliminado.
     * @throw std::out_of_range Si el vector esta vacio o pos es incorrecta.
     */
    T borrar (unsigned int pos=UINT_MAX);

    /**
     * @brief Ordena el vector de menor a mayor.
     * @pre T debe tener implementado operator< y operator==.
     */
    void ordenar();

    /**
    * @brief Busqueda binaria (dicotomica) de un dato.
    * @param dato Dato a localizar.
    * @return Posicion del dato, o -1 si no se encuentra.
    * @pre El vector debe estar ordenado y T implementar operator< y operator==.
    */
    int busquedaDicotomica(const T& dato);

    /**
    * @brief Devuelve el tamanio logico del vector.
    * @return Numero de elementos almacenados.
    */
    unsigned long int tamlog() {
        return tamlogico;
    }

};






template<typename T>
VDinamico<T>::VDinamico():tamfisico(1),tamlogico(0) {

    v = new T[tamfisico];
}


template<typename T> ///< n es el tamlogico del vector
VDinamico<T>::VDinamico(const unsigned int n, T &dato) {
    tamfisico=1;
    tamlogico=n;

    while (tamfisico<n) {
        tamfisico*=2;
    }
    v=new T[tamfisico];

    for (int i=0;i<n;i++) {
        v[i]=dato;
    }
}


template<typename T> //suponemos que el vector que nos dan, tiene un tamaño válido.
VDinamico<T>::VDinamico(const VDinamico<T> &orig):tamfisico(orig.tamfisico),tamlogico(orig.tamlogico) {

    v=new T[tamfisico];
    for (int i=0;i<tamlogico;i++) {
        v[i]=orig.v[i];
    }
}


template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial, unsigned int numElementos) {
    if (posicionInicial>=origen.tamlogico) {
        throw std::out_of_range("Error: [VDinamico<T>::VDinamico] Posicion Inicial fuera de rango");
    }
    if (posicionInicial+numElementos>origen.tamlogico) {
        throw std::out_of_range("Error: [VDinamico<T>::VDinamico] El numero de elementos a copiar provoca una salida del vector");
    }
    tamfisico=1;
    while (tamfisico<numElementos) {
        tamfisico*=2;
    }
    v=new T[tamfisico];
    tamlogico=numElementos;

    int t=0; //contador de posiciones del nuevo vector
    for (unsigned int i=posicionInicial;t<numElementos;i++) {
        v[t]=origen.v[i];
        t++;
    }
}


template<class T>
   VDinamico<T>::~VDinamico(){
    if (v!=nullptr) {
        delete [] v;
    }
}


template<typename T>
VDinamico<T>& VDinamico<T>::operator=(const VDinamico<T> &orig) {
    if (&orig!=this) {
        delete[] v; //esto nos evitara fugas de memoria. Liberamos memoria a la que apuntaba v
        tamfisico=orig.tamfisico;
        v=new T[tamfisico];
        tamlogico=orig.tamlogico;
        for (int i=0;i<tamlogico;i++) {
            v[i]=orig.v[i];
        }
    }
    return *this;
}


template<typename T>
T& VDinamico<T>::operator[](unsigned int p) {
    if (p>=tamlogico) {
        throw std::out_of_range("Error: [VDinamico<T>::operator[] ] Posicion fuera de rango");
    }
    return v[p];
}



template <typename T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos) {
    if (pos==UINT_MAX) {
        pos=tamlogico; //A espensas de comprobar si se puede insertar, pero ya sabemos que si o si, nuestra posicion sera el tamaño logico
    }else if (pos > tamlogico) {
        throw std::out_of_range("Error: [VDinamico<T>:: insertar]. Posicion incorrecta, ya que sobrepasas el tamanio logico");
    }

    if (tamlogico==tamfisico) {
        tamfisico*=2;
        T *vaux=new T[tamfisico];
        for (unsigned int i = 0; i <tamlogico; ++i) {
            vaux[i] = v[i];
        }
        delete []v;
        v=vaux;
    }
        //1º caso, no entra (UINT_MAX)
        for (unsigned int i = tamlogico; i>pos; --i) {
            v[i]=v[i-1];
        }
    v[pos]=dato;
    tamlogico++;
}

template<class T>
   T VDinamico<T>:: borrar(unsigned int pos) {
    if (tamlogico==0) {
        throw std::out_of_range("Error: [VDinamico<T>:: borrar] No hay que borrar nada");
    }
    if (pos==UINT_MAX) {
        pos=tamlogico-1;
    } else if (pos>=tamlogico) {
        throw std::out_of_range("Error: [VDinamico<T>:: borrar]. Posicion incorrecta");
    }

    T aux=v[pos];  // guardamos el dato que vamos a borrar para devolverlo

    // Desplazamos a la izquierda, machacando el dato
    for (unsigned int i=pos;i<tamlogico-1;i++) {
        v[i]=v[i+1];
    }

    tamlogico--; //reajustamos el tamaño

    if (tamlogico*3<tamfisico && tamfisico>1) { //hay que tener cuidado si nos quedamos con un solo elemento
        tamfisico /=2;
        T *vaux=new T[tamfisico];
        for (unsigned int i=0;i<tamlogico;i++) {
            vaux[i]=v[i];
        }
        delete []v;
        v=vaux;
    }
    return aux;
}

template<class T>
void VDinamico<T>::ordenar(){
    std::sort(v,v+tamlogico);
}

template<class T>
int VDinamico<T>::busquedaDicotomica(const T& dato) {
    int einf=0;
    int esup=tamlogico-1;
    int medio;

    while (einf<=esup) {
        medio=(einf+esup)/2;
        if (v[medio]==dato)
            return medio;
        else if (v[medio]<dato)
            einf=medio+1;
        else
            esup=medio-1;
    }
    return -1;
}


#endif //PR1_VDINAMICO_H