#ifndef PR2_CONTROLPARQUES_H
#define PR2_CONTROLPARQUES_H
#include "Especie.h"
#include "ListaDEnlazada.h"
#include "Parque.h"
#include "VDinamico.h"
#include <string>


class ControlParques {
private:
    VDinamico<Especie> varieties;
    ListaDEnlazada<Parque> parks;

public:
    ControlParques();
    ControlParques(const std::string &nomFichEspecies, const std::string &nomFichParques);
    ControlParques(const ControlParques &orig);
    ~ControlParques();

    void asignarEspecieParque(Especie &e, Parque &p);
    int contarEspecieParque(const std::string &ncom);
    VDinamico<Especie*> listadoEspecieSubNbre(const std::string &ncie);
    Parque* buscarParque(const std::string &nParque);

    // Para parejas
    void eliminarParque(const std::string &nombre);
};


#endif //PR2_CONTROLPARQUES_H