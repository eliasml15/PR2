//
// Created by elias on 08/10/2026.
//

#ifndef PR2_PARQUE_H
#define PR2_PARQUE_H
#include <string>

#include "VDinamico.h"
#include "Especie.h"

class Parque {
private:
    int cod_parque;
    std::string nbre_parque;

public:
    int getCParque() const;

    void setCParque(int cod_parque);

    std::string getNomParque() const;

    void setNomParque(const std::string &nbre_parque);

private:
    VDinamico<Especie*> contains;
public:
    Parque();
    Parque(const Parque &orig);
    ~Parque();

    void insertarEspecie(Especie *e);
    bool existeNbreCom(std::string ncom);
    bool existeNbreCie(std::string ncie);
};


#endif //PR2_PARQUE_H