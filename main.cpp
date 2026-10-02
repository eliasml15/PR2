/** @author Carlos Granados de la Torre cgt00032@red.ujaen.es
    @author Elias Martos Linde eml00069@red.ujaen.es
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Especie.h"
#include "VDinamico.h"


//Funcion que nos permite obtener un vector cuyos elementos son punteros al vector original que tienen nombre diferente de vacio
VDinamico<Especie*> getEspNComun(VDinamico<Especie> &vEspecies) {
    VDinamico<Especie*> VNoNulos;//Creamos un vector donde almacenaremos los buenos
    for (int i=0;i<vEspecies.tamlog();i++) {
        if (vEspecies[i].getNCom()!="") {
            VNoNulos.insertar(&vEspecies[i]);
        }
    }
    return VNoNulos;
}


VDinamico<Especie*> getEspPalabra(VDinamico<Especie> &vEspecies, const std::string &palabra) {
    VDinamico<Especie*> vResultado; //Vector dinamico de punteros a Especies con los que cumplen la condicion

    for (unsigned int i = 0; i < vEspecies.tamlog(); i++) {
        std::stringstream ss(vEspecies[i].getNCi());
        std::string primera;
        getline(ss, primera, ' ');   // lee hasta el primer espacio

        if (primera == palabra) {
            vResultado.insertar(&vEspecies[i]);
        }
    }
    return vResultado;
}

int main(int argc, const char * argv[]) {

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;
    char delimitador = ',';

    std::string _codigoEspecie = "";
    std::string _nombreComun = "";
    std::string _nombreCientifico = "";
    std::string _tipoPlanta = "";

    VDinamico<Especie> vaux;


    is.open("../arbolado-especies.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();
        getline(is, fila ); //salto la cabecera

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //Código - Nombre común - Nombre científico - Tipo de planta

                getline(columnas, _codigoEspecie, delimitador);
                getline(columnas, _nombreComun, delimitador);
                getline(columnas, _nombreCientifico, delimitador);
                getline(columnas, _tipoPlanta, delimitador);

                fila="";
                columnas.clear();

                Especie e(_codigoEspecie,_nombreComun,_nombreCientifico,_tipoPlanta);
                vaux.insertar(e);
                contador++;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //EJ1:mostrar los 50 primeros

    std::cout<<"EJERCICIO 1: "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"MOSTRANDO LOS 50 PRIMEROS"<< std::endl;
    for (int i=0;i<50;i++) {
        std::cout<<"Codigo Especie: "<<vaux[i].getCod()<<std::endl;
    }

    //EJ2: ORDENAR
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"EJERCICIO 2: "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ANTES DE ORDENARLO"<<std::endl;
    for (int i=0;i<50;i++) {
        std::cout<<"Codigo Especie: "<<vaux[i].getCod()<<". Nombre Cientifico: "<<vaux[i].getNCi()
        <<". Nombre Comun: "<<vaux[i].getNCom()<<". Tipo de Planta: "<<vaux[i].getTP()<<std::endl;
    }

    vaux.ordenar();
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"DESPUES DE ORDENARLO"<<std::endl;
    for (int i=0;i<50;i++) {
        std::cout<<"Codigo Especie: "<<vaux[i].getCod()<<". Nombre Cientifico: "<<vaux[i].getNCi()
        <<". Nombre Comun: "<<vaux[i].getNCom()<<". Tipo de Planta: "<<vaux[i].getTP()<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    //EJ 3: buscar en O(log n) los codigos: CTA, DMD, HCN,NDOF y JAX, muestra su posicion en el vector, ten en cuenta q puede NO existir
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"EJERCICIO 3: "<<std::endl;

    std::string codigos[]={"CTA","DMD", "HCN","NDOF","JAX"};
    Especie aux("", "", "", "");   //Creamos especie auxiliar

    for (int i = 0; i < 5; i++) {
        aux.setCod(codigos[i]); //Asignamos el nombre a buscar a nuestra nueva especie auxiliar
        int pos = vaux.busquedaDicotomica(aux);   // como el metodo devuelve un entero, declaramos una nueva variable posicion, que almacenara dicho lugar o -1.

        if (pos != -1) {
            std::cout << codigos[i] << "Posicion encontrada: " << pos << std::endl;
        } else {
            std::cout << codigos[i] << "No encontrada" << std::endl;
        }
    }

    //EJ4:
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"EJERCICIO 4: "<<std::endl;

    VDinamico<Especie*> VNoNulos = getEspNComun(vaux);
    std::cout<<"EL TAMAÑO DEL VECTOR de NO nulos es: "<<VNoNulos.tamlog()<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    for (int i=0;i<50;i++) {
        std::cout<<"Codigo Especie: "<<VNoNulos[i]->getCod()<<". Nombre Cientifico: "<<VNoNulos[i]->getNCi()
        <<". Nombre Comun: "<<VNoNulos[i]->getNCom()<<". Tipo de Planta: "<<VNoNulos[i]->getTP()<<std::endl;
    }

    //EJ5:
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"EJERCICIO 5: "<<std::endl;

    int n=vaux.tamlog();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (vaux[j + 1].getCod() < vaux[j].getCod()) {
                Especie aux2 = vaux[j];       // intercambio con una variable auxiliar
                vaux[j] = vaux[j + 1];
                vaux[j + 1] = aux2;
            }
        }
    }
    std::cout<<"MOSTRANDO LOS ÚLTIMOS 50 ELEMENTOS ESPECIE ORDENADOS: "<<std::endl;
    for (int i = n - 1; i >= 0 && i >= n - 50; i--){
        std::cout << "Código Especie: "<<vaux[i].getCod() << "Nombre Cientifico: "
                  << vaux[i].getNCi() << std::endl;
    }


    std::cout<<std::endl;

    //EJ6:
    std::cout<<std::endl;
    std::cout<<"EJERCICIO 6: "<<std::endl;
    VDinamico<Especie*> vJasminum;
    vJasminum=getEspPalabra(vaux, "Jasminum");;
    std::cout << "Especies con la primera palabra Jasminum: " << vJasminum.tamlog() << std::endl;

    return 0;

}

