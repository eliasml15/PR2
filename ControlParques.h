//
// Created by elias on 08/10/2026.
//

#ifndef PR2_CONTROLPARQUES_H
#define PR2_CONTROLPARQUES_H
#include "Especie.h"
#include "ListaDEnlazada.h"
#include "Parque.h"
#include "VDinamico.h"



class ControlParques {
private:
    VDinamico<Especie*> varieties;
    ListaDEnlazada<Parque*> parks;

public:
    ControlParques();
    ControlParques(const ControlParques &orig);
    ~ControlParques();

    void asignarEspecieParque(Especie &e,Parque &p);
    int contarEspecieParque(const std::string &ncom);
    VDinamico<Especie*> listadoEspecieSubNbre(const std::string &ncie);
    Parque buscarParque(const std::string &nParque);
};


#endif //PR2_CONTROLPARQUES_H