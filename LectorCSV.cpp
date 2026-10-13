#include "LectorCSV.h"

#include <fstream>
#include <iostream>
#include "Especie.h"
#include "VDinamico.h"

/**
 * @brief Carga el fichero CSV indicado en el VDinamico de especies.
 *
 * Cada linea se analiza y, si tiene el numero de campos esperado, se
 * construye una Especie que se inserta en el vector. Las filas con un
 * numero de campos distinto del esperado se descartan (ver filasDescartadas()).
 *
 * @param vector Vector dinamico donde se van insertando las especies leidas.
 * @param rutaFichero Ruta del fichero CSV a leer.
 * @return true si el fichero se ha podido abrir, false en caso contrario.
 */
bool LectorCSV::cargarEspecies(VDinamico<Especie> &vector, const std::string& rutaFichero) {
    filasDescartadas_ = 0;

    std::ifstream fichero(rutaFichero);
    if (!fichero.is_open()) {
        return false;
    }

    std::string linea;
    if (std::getline(fichero, linea)) {
        eliminarBOM(linea);
    }

    //Declaradas fuera del bucle por eficiencia
    std::string codigo, nombreComun, nombreCientifico, tipoPlanta;
    while (std::getline(fichero, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (contarCampos(linea) != 4) {
            ++filasDescartadas_;
            continue;
        }

        codigo = extraerCampo(linea, 0);
        nombreComun = extraerCampo(linea, 1);
        nombreCientifico = extraerCampo(linea, 2);
        tipoPlanta = extraerCampo(linea, 3);

        vector.insertar(Especie(codigo, nombreComun, nombreCientifico, tipoPlanta));
    }
    numeroEspecies_ = vector.tamlog();
    return true;
}

/**
 * @brief Carga el fichero CSV de parques en la lista doblemente enlazada.
 *
 * Cada linea se analiza y, si tiene el numero de campos esperado (2:
 * cod_parque, nbre_parque), se construye un Parque que se inserta al
 * final de la lista, en el mismo orden en que aparece en el fichero.
 *
 * @param lista Lista doblemente enlazada donde se van insertando los parques leidos.
 * @param rutaFichero Ruta del fichero CSV a leer.
 * @return true si el fichero se ha podido abrir, false en caso contrario.
 */
bool LectorCSV::cargarParques(ListaDEnlazada<Parque> &lista, const std::string& rutaFichero) {
    filasDescartadas_ = 0;

    std::ifstream fichero(rutaFichero);
    if (!fichero.is_open()) {
        return false;
    }

    std::string linea;
    if (std::getline(fichero, linea)) {
        eliminarBOM(linea);
    }

    std::string codStr, nombre;
    while (std::getline(fichero, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (contarCampos(linea) != 2) {
            ++filasDescartadas_;
            continue;
        }

        codStr = extraerCampo(linea, 0);
        nombre = extraerCampo(linea, 1);

        int cod = std::stoi(codStr);
        lista.insertarFinal(Parque(cod, nombre));
    }
    return true;
}

/**
 * @brief Número de especies leídas correctamente.
 * @return Cantidad de especies cargadas durante la última llamada a cargar().
 */
std::size_t LectorCSV::numeroEspecies() const {
    return numeroEspecies_;
}

/**
 * @brief Número de filas descartadas por no tener el número de campos esperado.
 * @return Cantidad de filas descartadas durante la última llamada a cargar()/cargarParques().
 */
std::size_t LectorCSV::filasDescartadas() const {
    return filasDescartadas_;
}

/**
 * @brief Cuenta los campos de una línea CSV sin almacenarlos.
 *
 * Tiene en cuenta comillas envolventes y comillas escapadas ("") dentro
 * de un campo entrecomillado, tal como especifica RFC4180.
 *
 * @param linea Línea física a analizar.
 * @return Número de campos que contiene la línea.
 */
std::size_t LectorCSV::contarCampos(const std::string& linea) {
    std::size_t numCampos = 1;
    bool dentroComillas = false;
    const std::size_t n = linea.size();

    for (std::size_t i = 0; i < n; ) {
        const char c = linea[i];

        if (dentroComillas) {
            if (c == '"') {
                if (i + 1 < n && linea[i + 1] == '"') {
                    i += 2;
                } else {
                    dentroComillas = false;
                    ++i;
                }
            } else {
                ++i;
            }
        } else if (c == '"') {
            dentroComillas = true;
            ++i;
        } else if (c == ',') {
            ++numCampos;
            ++i;
        } else {
            ++i;
        }
    }

    return numCampos;
}

/**
 * @brief Extrae un único campo (por índice) de una línea CSV.
 *
 * Recorre la línea completa pero solo acumula el contenido del campo
 * solicitado; el resto de campos se descarta sin llegar a almacenarse.
 * Tiene en cuenta comillas envolventes y comillas escapadas ("").
 *
 * @param linea Línea física a analizar.
 * @param indiceObjetivo Índice (base 0) del campo a extraer.
 * @return Contenido del campo solicitado.
 */
std::string LectorCSV::extraerCampo(const std::string& linea, std::size_t indiceObjetivo) {
    std::string campo;
    std::size_t indiceActual = 0;
    bool dentroComillas = false;
    const std::size_t n = linea.size();

    for (std::size_t i = 0; i < n; ) {
        const char c = linea[i];

        if (dentroComillas) {
            if (c == '"') {
                if (i + 1 < n && linea[i + 1] == '"') {
                    if (indiceActual == indiceObjetivo) {
                        campo += '"';
                    }
                    i += 2;
                } else {
                    dentroComillas = false;
                    ++i;
                }
            } else {
                if (indiceActual == indiceObjetivo) {
                    campo += c;
                }
                ++i;
            }
        } else if (c == '"') {
            dentroComillas = true;
            ++i;
        } else if (c == ',') {
            if (indiceActual == indiceObjetivo) {
                return campo;
            }
            ++indiceActual;
            ++i;
        } else {
            if (indiceActual == indiceObjetivo) {
                campo += c;
            }
            ++i;
        }
    }

    return campo;
}

/**
 * @brief Elimina el BOM UTF-8 (0xEF 0xBB 0xBF) al inicio de la línea, si existe.
 * @param linea Línea a modificar in-place.
 */
void LectorCSV::eliminarBOM(std::string& linea) {
    static const char bom[3] = { static_cast<char>(0xEF), static_cast<char>(0xBB), static_cast<char>(0xBF) };
    if (linea.size() >= 3 && linea[0] == bom[0] && linea[1] == bom[1] && linea[2] == bom[2]) {
        linea.erase(0, 3);
    }
}