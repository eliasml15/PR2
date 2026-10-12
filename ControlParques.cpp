//
// Created by elias on 08/10/2026.
//
#include <sstream>
#include <string>
#include "ControlParques.h"
ControlParques::ControlParques(){}
ControlParques::ControlParques(const ControlParques &orig):varieties(orig.varieties),parks(orig.parks){}
ControlParques::~ControlParques(){}

void ControlParques::asignarEspecieParque(Especie &e,Parque &p) {
    p.insertarEspecie(&e);
}

int ControlParques::contarEspecieParque(const std::string &ncom) {
    int c=0;
    for (int i=0;i<varieties.tamlog();i++) {
        if (varieties[i]->getNCom()==ncom)
            c++;
    }
    return c;
}

VDinamico<Especie*> ControlParques::listadoEspecieSubNbre(const std::string &ncie) {
        VDinamico<Especie*> vResultado;

        for (unsigned int i = 0; i < varieties.tamlog(); i++) {
            if (varieties[i]->getNCi().find(ncie)!=std::string::npos) {
                vResultado.insertar(varieties[i]);
            }
        }
        return vResultado;
}

Parque ControlParques::buscarParque(const std::string &nParque) {

    Nodo<Parque*> *q=parks.iterador().nodo;
    while (q->dato!=parks.final()) {
        if (q->dato->getNomParque()==nParque) {
            return *q->dato;
        }
        q=q->sig;
    }
    throw std::logic_error("No se encontró el parque");
}