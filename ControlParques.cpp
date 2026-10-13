#include "ControlParques.h"
#include "LectorCSV.h"
#include <stdexcept>

// Constructor por defecto: varieties y parks quedan vacios
// (lo hacen sus propios constructores por defecto)
ControlParques::ControlParques() {}

// Constructor parametrizado: lee los dos ficheros con LectorCSV,
// ordena varieties y despues enlaza especies con parques.
ControlParques::ControlParques(const std::string &nomFichEspecies, const std::string &nomFichParques) {

    LectorCSV lector;

    // ---------- 1. Cargar especies ----------
    if (!lector.cargarEspecies(varieties, nomFichEspecies)) {
        throw std::runtime_error("ControlParques: no se pudo abrir el fichero de especies: " + nomFichEspecies);
    }

    // Ordenamos ANTES de enlazar nada, porque despues no se puede reordenar
    // sin invalidar los punteros que guardaran los Parque::contains
    varieties.ordenar();

    // ---------- 2. Cargar parques ----------
    if (!lector.cargarParques(parks, nomFichParques)) {
        throw std::runtime_error("ControlParques: no se pudo abrir el fichero de parques: " + nomFichParques);
    }

    // ---------- 3. Enlazar especies con parques ----------
    for (unsigned int i = 0; i < varieties.tamlog(); i++) {
        TipoPlanta tipo = varieties[i].getTP();

        bool tipoDeParPares = (tipo == ARBUSTO || tipo == CONIFERA || tipo == PALMACEA
                             || tipo == HERB_PERENNES || tipo == FRONDOSA);

        ListaDEnlazada<Parque>::Iterador it = parks.iterador();
        while (!it.fin()) {
            bool esPar = (it.dato().getCParque() % 2 == 0);

            if ((tipoDeParPares && esPar) || (!tipoDeParPares && !esPar)) {
                asignarEspecieParque(varieties[i], it.dato());
            }
            it.siguiente();
        }
    }
}

// Constructor de copia: al ser varieties y parks objetos (no punteros),
// los constructores de copia de VDinamico y ListaDEnlazada ya hacen copia profunda
ControlParques::ControlParques(const ControlParques &orig)
    : varieties(orig.varieties), parks(orig.parks) {
}

// Destructor: no hay que liberar nada a mano, varieties y parks se destruyen solos
ControlParques::~ControlParques() {}

void ControlParques::asignarEspecieParque(Especie &e, Parque &p) {
    p.insertarEspecie(&e);
}

int ControlParques::contarEspecieParque(const std::string &ncom) {
    int contador = 0;

    ListaDEnlazada<Parque>::Iterador it = parks.iterador();
    while (!it.fin()) {
        if (it.dato().existeNbreCom(ncom)) {
            contador++;
        }
        it.siguiente();
    }
    return contador;
}

VDinamico<Especie*> ControlParques::listadoEspecieSubNbre(const std::string &ncie) {
    VDinamico<Especie*> resultado;

    for (unsigned int i = 0; i < varieties.tamlog(); i++) {
        std::string nombreCientifico = varieties[i].getNCi();

        if (nombreCientifico.find(ncie) != std::string::npos) {
            resultado.insertar(&varieties[i]);
        }
    }
    return resultado;
}

Parque* ControlParques::buscarParque(const std::string &nParque) {
    ListaDEnlazada<Parque>::Iterador it = parks.iterador();

    while (!it.fin()) {
        if (it.dato().getNomParque() == nParque) {
            return &it.dato();
        }
        it.siguiente();
    }
    return nullptr; // no existe
}

void ControlParques::eliminarParque(const std::string &nombre) {
    ListaDEnlazada<Parque>::Iterador it = parks.iterador();

    while (!it.fin()) {
        if (it.dato().getNomParque() == nombre) {
            parks.borrar(it);
            return;
        }
        it.siguiente();
    }
    throw std::out_of_range("ControlParques::eliminarParque: no existe el parque " + nombre);
}