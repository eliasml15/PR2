/**
* @file Especie.cpp
* @brief Implementacion clase Especie
* @author Carlos y Elias
* @date 18/09/2026
*/

#include "Especie.h"
#include <iostream>
inline TipoPlanta convertiratipoplanta(const std::string &texto) {
    if (texto == "ARBUSTO") return ARBUSTO;
    if (texto == "CONIFERA") return CONIFERA;
    if (texto == "PALMACEA") return PALMACEA;
    if (texto == "HERB_PERENNES") return HERB_PERENNES;
    if (texto == "FRONDOSA") return FRONDOSA;
    if (texto == "TAPIZANTE_TREPADORA") return TAPIZANTE_TREPADORA;
    if (texto == "CACTACEA_SUCULENTA") return CACTACEA_SUCULENTA;
    if (texto == "SUBTROPICAL_TROPICAL") return SUBTROPICAL_TROPICAL;
    if (texto == "HERB_ANUAL") return HERB_ANUAL;
    if (texto == "HERB_ANUALES") return HERB_ANUALES;
    if (texto == "") return NO;

    throw std::invalid_argument("stringToTipoPlanta: tipo de planta desconocido: " + texto);
}

inline std::string convertirastring(TipoPlanta tipo) {
    switch (tipo) { //aaqui podemos hacerlo cno swithc porque si soporta tipo entero, no como antes que eran string y por tanto tocaba con if/else
        case ARBUSTO: return "ARBUSTO";
        case CONIFERA: return "CONIFERA";
        case PALMACEA: return "PALMACEA";
        case HERB_PERENNES: return "HERB_PERENNES";
        case FRONDOSA: return "FRONDOSA";
        case TAPIZANTE_TREPADORA: return "TAPIZANTE_TREPADORA";
        case CACTACEA_SUCULENTA: return "CACTACEA_SUCULENTA";
        case SUBTROPICAL_TROPICAL: return "SUBTROPICAL_TROPICAL";
        case HERB_ANUAL: return "HERB_ANUAL";
        case HERB_ANUALES: return "HERB_ANUALES";
        case NO: return "";
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