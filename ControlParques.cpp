//
// Created by elias on 08/10/2026.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "ControlParques.h"
// Constructor por defecto: varieties y parks quedan vacios
// (lo hacen sus propios constructores por defecto)
ControlParques::ControlParques() {}

// Constructor parametrizado: lee los dos ficheros
ControlParques::ControlParques(const std::string &fParques,const std::string &fEspecies) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;
    char delimitador = ',';

    // ==========================================
    // 1. LECTURA DE ESPECIES (arbolado-especies.csv)
    // ==========================================
    std::string _codigoEspecie = "";
    std::string _nombreComun = "";
    std::string _nombreCientifico = "";
    std::string _tipoPlanta = "";
    int contadorEspecies = 0;

    is.open("../arbolado-especies.csv");
    if (is.good()) {
        clock_t t_ini = clock();
        std::getline(is, fila); // Saltamos la cabecera: Código,Nombre común,Nombre científico,Tipo de planta

        while (std::getline(is, fila)) {
            if (fila != "") {


                columnas.str(fila);

                std::getline(columnas, _codigoEspecie, delimitador);
                std::getline(columnas, _nombreComun, delimitador);
                std::getline(columnas, _nombreCientifico, delimitador);
                std::getline(columnas, _tipoPlanta, delimitador);

                fila = "";
                columnas.clear();

                // Si varieties es VDinamico<Especie>:
                Especie e(_codigoEspecie, _nombreComun, _nombreCientifico, _tipoPlanta);
                varieties.insertar(e);

                contadorEspecies++;
            }
        }
        is.close();
        std::cout << "Especies leídas: " << contadorEspecies
                  << " | Tiempo: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo arbolado-especies.csv" << std::endl;
    }

    // ==========================================
    // 2. LECTURA DE PARQUES (arbolado-parques.csv)
    // ==========================================
    std::string _codParque = "";
    std::string _nombreParque = "";
    int contadorParques = 0;

    is.open("../arbolado-parques.csv");
    if (is.good()) {
        clock_t t_ini = clock();
        std::getline(is, fila); // Saltamos la primera línea (cabecera)

        while (std::getline(is, fila)) {
            if (fila != "") {


                columnas.str(fila);

                // Extraemos el código y el nombre del parque
                std::getline(columnas, _codParque, delimitador);
                std::getline(columnas, _nombreParque, delimitador);

                fila = "";
                columnas.clear();

                Parque p;
                p.setCParque(std::stoi(_codParque)); // Convertimos el string del código a int
                p.setNomParque(_nombreParque);

                // Insertamos en la ListaDEnlazada<Parque> parks
                parks.insertaFin(p); // (Usa insertarFinal(p) si así se llama en tu ListaDEnlazada)

                contadorParques++;
            }
        }
        is.close();
        std::cout << "Parques leídos: " << contadorParques
                  << " | Tiempo: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo arbolado-parques.csv" << std::endl;
    }
}

// Constructor de copia: al ser varieties y parks objetos (no punteros),
// los constructores de copia de VDinamico y ListaDEnlazada ya hacen copia profunda
ControlParques::ControlParques(const ControlParques &orig):varieties(orig.varieties),parks(orig.parks) {

}

// Destructor: no hay que liberar nada a mano, varieties y parks se destruyen solos
//recordamos la relacion de asociacion
ControlParques::~ControlParques() {}

void ControlParques::asignarEspecieParque(Especie &e, Parque &p) {
    p.insertarEspecie(&e);  //utilizamos el metodo del parque para insertar una especie
}

int ControlParques::contarEspecieParque(const std::string &ncom) {
    int contador = 0;

    ListaDEnlazada<Parque>::Iterador it = parks.iterador();  //para recorrer la lista donde se encunetran los nombres, tenemos que crear un iterador que apute al primer nodo de la lista, que lo conseguimos con el metodo iterador()
    while (!it.fin()) { //mientras que no sea nullptr...seguimos recorriendo
        if (it.dato().existeNbreCom(ncom)) { //comprobamos si el dato apuntado por el iterador ya existe en algun parque
            contador++;  //en caso de que si, incrementamos
        }
        it.siguiente(); //avanzamos al siguiente nodo
    }
    return contador;  //una vez recorrida toda la lista, devolvemos numero de veces que hemos encotnrado esa especie
}

//recibimos una subcadena, y tenemos que devolver un vector de punteros a las especies que contienen esa subcadena
VDinamico<Especie*> ControlParques::listadoEspecieSubNbre(const std::string &ncie) {
    VDinamico<Especie*> resultado;  //Creamos el vector de punteros donde almacenaremos el resultado

    for (unsigned int i = 0; i < varieties.tamlog(); i++) {  //Recorremos el vector de las especies
        std::string nombreCientifico = varieties[i].getNCi();  //obteneos y alcamenamos una por una el nombre cientifico que es el campo que nos interesa para ver coincidencia

        if (nombreCientifico.find(ncie) != std::string::npos) { //si nombre cientifico (alguna parque: find) es igual que ncie, entonces devuelve un numero diferente. Sino lo encuentra devuelve npos
            resultado.insertar(&varieties[i]);  //insertamos en el vector de punteros  nuevo creado
        }
    }
    return resultado;
}

Parque* ControlParques::buscarParque(const std::string &nParque) {
    ListaDEnlazada<Parque>::Iterador it = parks.iterador();  //iterador para recorrer la lista de parques

    while (!it.fin()) { //mientras no hayamos llegado al final de la lista
        if (it.dato().getNomParque() == nParque) { //comprobamos si algun nombre de algun parque es igual que el que nos han pasado
            return &it.dato();  //en ese caso, devolvmos una referencia a ese dato
        }
        it.siguiente(); //pasamos al siguiente
    }
    return nullptr; // no existe
}

void ControlParques::eliminarParque(const std::string &nombre) {
    ListaDEnlazada<Parque>::Iterador it = parks.iterador();

    while (!it.fin()) {
        if (it.dato().getNomParque() == nombre) {
            parks.borrar(it);
            return;
        }
        it.siguiente();
    }
    throw std::out_of_range("ControlParques::eliminarParque: no existe el parque ");
}