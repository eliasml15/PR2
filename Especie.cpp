/**
* @file Especie.cpp
* @brief Implementacion clase Especie
* @author Carlos y Elias
* @date 18/09/2026
*/

#include "Especie.h"
#include <iostream>


inline TipoPlanta stringToTipoPlanta(const std::string &texto) {
    if (texto == "ARBUSTO") return TipoPlanta::ARBUSTO;
    if (texto == "CONIFERA") return TipoPlanta::CONIFERA;
    if (texto == "PALMACEA") return TipoPlanta::PALMACEA;
    if (texto == "HERB_PERENNES") return TipoPlanta::HERB_PERENNES;
    if (texto == "FRONDOSA") return TipoPlanta::FRONDOSA;
    if (texto == "TAPIZANTE_TREPADORA") return TipoPlanta::TAPIZANTE_TREPADORA;
    if (texto == "CACTACEA_SUCULENTA") return TipoPlanta::CACTACEA_SUCULENTA;
    if (texto == "SUBTROPICAL_TROPICAL") return TipoPlanta::SUBTROPICAL_TROPICAL;
    if (texto == "HERB_ANUAL") return TipoPlanta::HERB_ANUAL;
    if (texto == "HERB_ANUALES") return TipoPlanta::HERB_ANUALES;
    if (texto == "TAPIZANTE/TREPADORA") return TipoPlanta::TAPIZANTE_TREPADORA;
    if (texto == "CACTACEA/SUCULENTA") return TipoPlanta::CACTACEA_SUCULENTA;
    if (texto == "SUBTROPICAL/TROPICAL") return TipoPlanta::SUBTROPICAL_TROPICAL;
    if (texto == "HERB/ANUAL") return TipoPlanta::HERB_ANUAL;
    if (texto == "HERB/ANUALES") return TipoPlanta::HERB_ANUALES;
    if (texto == "") return TipoPlanta::NO;

    throw std::invalid_argument("stringToTipoPlanta: tipo de planta desconocido: " + texto);
}
inline std::string tipoPlantaToString(TipoPlanta tipo) {
    switch (tipo) {
        case TipoPlanta::ARBUSTO: return "ARBUSTO";
        case TipoPlanta::CONIFERA: return "CONIFERA";
        case TipoPlanta::PALMACEA: return "PALMACEA";
        case TipoPlanta::HERB_PERENNES: return "HERB_PERENNES";
        case TipoPlanta::FRONDOSA: return "FRONDOSA";
        case TipoPlanta::TAPIZANTE_TREPADORA: return "TAPIZANTE_TREPADORA";
        case TipoPlanta::CACTACEA_SUCULENTA: return "CACTACEA_SUCULENTA";
        case TipoPlanta::SUBTROPICAL_TROPICAL: return "SUBTROPICAL_TROPICAL";
        case TipoPlanta::HERB_ANUAL: return "HERB_ANUAL";
        case TipoPlanta::HERB_ANUALES: return "HERB_ANUALES";
        case TipoPlanta::NO: return "";
    }
    return "DESCONOCIDO";
}



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