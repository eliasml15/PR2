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

    // Cargar especies
    if (!lector.cargarEspecies(varieties, nomFichEspecies)) {
        throw std::runtime_error("ControlParques: no se pudo abrir el fichero de especies: ");
    }

    // Ordenamos ANTES de enlazar nada, porque despues no se puede reordenar
    // sin invalidar los punteros que guardaran los Parque::contains
    varieties.ordenar();

    //  Cargar parques
    if (!lector.cargarParques(parks, nomFichParques)) {
        throw std::runtime_error("ControlParques: no se pudo abrir el fichero de parques: " );
    }

    //  Enlazar especies con parques
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
//recordamos la relacion de asociacion
ControlParques::~ControlParques() {}

void ControlParques::asignarEspecieParque(Especie &e, Parque &p) {
    p.insertarEspecie(&e);  //utilizamos el metodo del parque para insertar una especie
}

int ControlParques::contarEspecieParque(const std::string &ncom) {
    int contador = 0;

    ListaDEnlazada<Parque>::Iterador it = parks.iterador();  //para recorrer la lista donde se encunetran los nombres, tenemos que crear un iterador que apute al primer nodo de la lista, que lo conseguimos con el metodo iterador()
    while (!it.fin()) { //mientras que no sea nullptr...seguimos recorriendo
        if (it.dato().existeNbreCom(ncom)) { //comprobamos si el dato apuntado por el iterador ya existe en algun parque
            contador++;  //en caso de que si, incrementamos
        }
        it.siguiente(); //avanzamos al siguiente nodo
    }
    return contador;  //una vez recorrida toda la lista, devolvemos numero de veces que hemos encotnrado esa especie
}


//recibimos una subcadena, y tenemos que devolver un vector de punteros a las especies que contienen esa subcadena
VDinamico<Especie*> ControlParques::listadoEspecieSubNbre(const std::string &ncie) {
    VDinamico<Especie*> resultado;  //Creamos el vector de punteros donde almacenaremos el resultado

    for (unsigned int i = 0; i < varieties.tamlog(); i++) {  //Recorremos el vector de las especies
        std::string nombreCientifico = varieties[i].getNCi();  //obteneos y alcamenamos una por una el nombre cientifico que es el campo que nos interesa para ver coincidencia

        if (nombreCientifico.find(ncie) != std::string::npos) { //si nombre cientifico (alguna parque: find) es igual que ncie, entonces devuelve un numero diferente. Sino lo encuentra devuelve npos
            resultado.insertar(&varieties[i]);  //insertamos en el vector de punteros  nuevo creado
        }
    }
    return resultado;
}

Parque* ControlParques::buscarParque(const std::string &nParque) {
    ListaDEnlazada<Parque>::Iterador it = parks.iterador();  //iterador para recorrer la lista de parques

    while (!it.fin()) { //mientras no hayamos llegado al final de la lista
        if (it.dato().getNomParque() == nParque) { //comprobamos si algun nombre de algun parque es igual que el que nos han pasado
            return &it.dato();  //en ese caso, devolvmos una referencia a ese dato
        }
        it.siguiente(); //pasamos al siguiente
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
    throw std::out_of_range("ControlParques::eliminarParque: no existe el parque ");
}