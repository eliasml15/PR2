//
// Created by elias on 08/10/2026.
//

#include "Parque.h"



Parque::Parque():cod_parque(0),nbre_parque(""){}
Parque::Parque(const Parque &orig):cod_parque(orig.cod_parque),nbre_parque(orig.nbre_parque),contains(orig.contains) {
}
Parque::~Parque() {}

void Parque::insertarEspecie(Especie *e) {
    contains.insertar(e);
}
bool Parque::existeNbreCom(std::string ncom) {
    for (int i=0;i<contains.tamlog();i++) {
        if (ncom==contains[i]->getNCom()) {
            return true;
        }
    }
}
bool Parque::existeNbreCie(std::string ncie) {
    for (int i=0;i<contains.tamlog();i++) {
        if (ncie==contains[i]->getNCi()) {
            return true;
        }
    }
}

int Parque::getCParque() const {
    return cod_parque;
}

void Parque::setCParque(int c) {
    this->cod_parque = c;
}

std::string Parque::getNomParque() const {
    return nbre_parque;
}

void Parque::setNomParque(const std::string &n) {
    this->nbre_parque = n;
}