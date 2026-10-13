
#include "Parque.h"



Parque::Parque():cod_parque(0),nbre_parque(""){}

Parque::Parque(int cod_parque, const std::string &nbre_parque):cod_parque(cod_parque),nbre_parque(nbre_parque),contains(){}

Parque::Parque(const Parque &orig):cod_parque(orig.cod_parque),nbre_parque(orig.nbre_parque),contains(orig.contains) {
}
Parque::~Parque() {}


void Parque::insertarEspecie(Especie *e) {
    contains.insertar(e); //nos servimos del metodo que tiene especia
}
bool Parque::existeNbreCom(const std::string &ncom) {
    for (unsigned int i=0;i<contains.tamlog();i++) { //recorremos el vector dinamico de tipo especies
        if (ncom==contains[i]->getNCom()) { //hacemos la comprobacion
            return true;
        }
    }
    return false;
}
bool Parque::existeNbreCie(const std::string &nciet) {
    for (unsigned int i=0;i<contains.tamlog();i++) {
        if (nciet==contains[i]->getNCi()) {
            return true;
        }
    }
    return false;
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