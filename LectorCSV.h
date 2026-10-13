#ifndef LECTOR_CSV_H
#define LECTOR_CSV_H

#include <cstddef>
#include <string>

#include "Especie.h"
#include "VDinamico.h"
#include "Parque.h"
#include "ListaDEnlazada.h"

// Lee los ficheros arbolado-especies.csv y parques.csv: valores separados
// por comas, donde un valor puede ir entrecomillado y contener comas y
// comillas escapadas ("") dentro de las comillas (formato tipo RFC4180).
// Asume que cada fila logica ocupa una unica linea fisica del fichero.
class LectorCSV {
public:
    bool cargarEspecies(VDinamico<Especie> &vector, const std::string& rutaFichero);
    bool cargarParques(ListaDEnlazada<Parque> &lista, const std::string& rutaFichero);

    std::size_t numeroEspecies() const;
    std::size_t filasDescartadas() const;

private:
    std::size_t numeroEspecies_ = 0;
    std::size_t filasDescartadas_ = 0;

    static std::size_t contarCampos(const std::string& linea);
    static std::string extraerCampo(const std::string& linea, std::size_t indiceObjetivo);
    static void eliminarBOM(std::string& linea);
};

#endif // LECTOR_CSV_H