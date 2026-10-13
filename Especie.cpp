/**
* @file Especie.cpp
* @brief Implementacion clase Especie
* @author Carlos y Elias
* @date 18/09/2026
*/

#include "Especie.h"
#include <iostream>

Especie::Especie(const std::string &codigo, const std::string &ncomun, const std::string &ncientifico, const std::string &tipo):
codigoEspecie(codigo),nombreComun(ncomun),nombreCientifico(ncientifico),tipoPlanta(stringToTipoPlanta(tipo)) {
}

Especie::Especie(const Especie &orig):codigoEspecie(orig.codigoEspecie),nombreComun(orig.nombreComun),
nombreCientifico(orig.nombreCientifico),tipoPlanta(orig.tipoPlanta){}

bool Especie::operator<(const Especie& otra) const{
    if (this->codigoEspecie<otra.codigoEspecie)
        return true;
    else
        return false;
}

bool Especie::operator==(const Especie& otra) const {
    if (this->codigoEspecie==otra.codigoEspecie)
        return true;
    else
        return false;
}

std::string Especie::getCod() const {
    return codigoEspecie;
}

void Especie::setCod(const std::string &cod) {
    codigoEspecie = cod;
}

std::string Especie::getNCom() const {
    return nombreComun;
}

void Especie::setNCom(const std::string &ncom) {
    nombreComun = ncom;
}

std::string Especie::getNCi() const {
    return nombreCientifico;
}

void Especie::setNCi(const std::string &nci) {
    nombreCientifico = nci;
}

TipoPlanta Especie::getTP() const {
    return tipoPlanta;
}

void Especie::setTP(TipoPlanta tp) {
    tipoPlanta = tp;
}

void Especie::mostrarInfo() const {
    std::cout << " Codigo=" << codigoEspecie
              << " NombreComun=" << nombreComun
              << " NombreCientifico=" << nombreCientifico
              << " TipoPlanta=" << tipoPlantaToString(tipoPlanta)
              << std::endl;
}