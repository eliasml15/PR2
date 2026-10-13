/**
 * @file TipoPlanta.h
 * @brief Enum TipoPlanta y funciones de conversion con el texto del CSV.
 */

#ifndef PR1_TIPOPLANTA_H
#define PR1_TIPOPLANTA_H

#include <string>
#include <stdexcept>

/**
 * @brief Tipos de planta segun el fichero arbolado-especies.csv.
 */
enum TipoPlanta {
    ARBUSTO,
    CONIFERA,
    PALMACEA,
    HERB_PERENNES,
    FRONDOSA,
    TAPIZANTE_TREPADORA,
    CACTACEA_SUCULENTA,
    SUBTROPICAL_TROPICAL,
    HERB_ANUAL,
    HERB_ANUALES,
    NO ///< Tipo de planta vacio o desconocido en el CSV.
};

/**
 * @brief Convierte el texto del CSV (tal cual aparece en la columna) a TipoPlanta.
 * @param texto Texto leido del CSV.
 * @return El valor de TipoPlanta correspondiente.
 * @throw std::invalid_argument Si el texto no coincide con ningun tipo conocido.
 */
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
    if (texto == "") return TipoPlanta::NO;

    throw std::invalid_argument("stringToTipoPlanta: tipo de planta desconocido: " + texto);
}

/**
 * @brief Convierte un TipoPlanta a texto, para mostrarlo por pantalla.
 * @param tipo Valor a convertir.
 * @return Representacion en texto del tipo de planta.
 */
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


#endif //PR1_TIPOPLANTA_H