#ifndef PR2_PARQUE_H
#define PR2_PARQUE_H
#include <string>
#include "VDinamico.h"
#include "Especie.h"

class Parque {
private:
    int cod_parque;
    std::string nbre_parque;
    VDinamico<Especie*> contains; //RELACION DE ASOCIACION CON ESPECIE. ES DINAMICA


public:
    Parque();
    Parque(int cod_parque,std::string &nbre_parque);
    Parque(const Parque &orig);
    ~Parque();

    //sert y getters
    int getCParque() const;
    void setCParque(int cod_parque);
    std::string getNomParque() const;
    void setNomParque(const std::string &nbre_parque);


    void insertarEspecie(Especie *e);
    bool existeNbreCom(const std::string &ncom);
    bool existeNbreCie(const std::string &nciet);
};


#endif //PR2_PARQUE_H