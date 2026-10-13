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
    Parque(int cod_parque,const std::string &nbre_parque);
    Parque(const Parque &orig);
    ~Parque();

    //sert y getters
    int getCParque() const;
    void setCParque(int cod_parque);
    std::string getNomParque() const;
    void setNomParque(const std::string &nbre_parque);


    void insertarEspecie(Especie *e); //metodo que sirve para insertar una especie en un parque, mediante esa relacion de asociacion
    bool existeNbreCom(const std::string &ncom); //dado un nombre de una especie, indica si existe o no dentro del parque
    bool existeNbreCie(const std::string &nciet); //nos dan un nombre cientifico y tenemos que ver si existe esa especie
};


#endif //PR2_PARQUE_H