/**
* @file Especie.h
* @brief Declaracion clase Especie
* @author Carlos y Elias
* @date 18/09/2026
*/

#ifndef PR1_ESPECIE_H
#define PR1_ESPECIE_H
#include <stdexcept>
#include <string>

enum TipoPlanta {
    ARBUSTO,  //ARBUSTO=0
    CONIFERA, //CONIFERA=1....es un tipo de dato que no admite mas que esto, y ademas por debajo podemso decir que son numeros, luego en las comparaciones son mas rapides que los strings por ejemplo
    PALMACEA,
    HERB_PERENNES,
    FRONDOSA,
    TAPIZANTE_TREPADORA ,
    CACTACEA_SUCULENTA,
    SUBTROPICAL_TROPICAL,
    HERB_ANUAL,
    HERB_ANUALES,
    NO // Tipo de planta vacio o desconocido en el CSV.
};
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
    if (texto == "TAPIZANTE/TREPADORA") return TipoPlanta::TAPIZANTE_TREPADORA;
    if (texto == "CACTACEA/SUCULENTA") return TipoPlanta::CACTACEA_SUCULENTA;
    if (texto == "SUBTROPICAL/TROPICAL") return TipoPlanta::SUBTROPICAL_TROPICAL;
    if (texto == "HERB/ANUAL") return TipoPlanta::HERB_ANUAL;
    if (texto == "HERB/ANUALES") return TipoPlanta::HERB_ANUALES;
    if (texto == "") return TipoPlanta::NO;

    throw std::invalid_argument("stringToTipoPlanta: tipo de planta desconocido: " + texto);
}
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

class Especie {
private:
    std::string codigoEspecie;
    std::string nombreComun;
    std::string nombreCientifico;
    TipoPlanta tipoPlanta;   //esto es muy importante. El enum

public:
    /**
    * @brief Constructor por defecto, inicializado como default.
    */
    Especie()=default;

    /**
     * @brief Constructor parametrizado.
     * @param codigo    Codigo que identifica a la especie.
     * @param ncomun   Nombre comun de la especie.
     * @param ncientifico Nombre cientifico de la especie.
     * @param tipo Texto del tipo de planta tal como aparece en el CSV; se convierte a TipoPlanta.
     * @throw std::invalid_argument Si tipo no coincide con ningun TipoPlanta conocido.
     */
    Especie(const std::string &codigo, const std::string &ncomun, const std::string &ncientifico, const std::string &tipo);

    /**
    * @brief Constructor de copia.
    * @param orig Objeto Especie que se copia eficientemente.
    */
    Especie(const Especie &orig);

    /**
     * @brief Destructor. Inicializado por defecto.
     */
    ~Especie()=default;

    /**
    * @brief Operador menor que.
    * @param otra Objeto especie que se va a comparar.
    * @return La Especie con un codigo de Especie menor.
    */
    bool operator<(const Especie& otra) const;

    /**
    * @brief Operador ==.
    * @param otra Objeto especie que se va a comparar.
    * @return Devuelve true si otra es igual que this.
    */
    bool operator==(const Especie& otra) const;

    /**
    * @brief Devuelve el codigo de un objeto Especie
    * @return Devuelve codigoEspecie.
    */
    std::string getCod() const;

    /**
    * @brief Asigna un codigo a un objeto Especie
    * @param cod Nuevo codigoEspecie.
    */
    void setCod(const std::string &cod);

    /**
    * @brief Devuelve el nombre comun de un objeto Especie
    * @return Devuelve nombreComun.
    */
    std::string getNCom() const;

    /**
    * @brief Asigna un nombre comun a un objeto Especie
    * @param ncom Nuevo nombreComun.
    */
    void setNCom(const std::string &ncom);

    /**
    * @brief Devuelve el nombre cientifico de un objeto Especie
    * @return Devuelve nombreCientifico.
    */
    std::string getNCi() const;

    /**
    * @brief Asigna un nombre cientifico a un objeto Especie
    * @param nci Nuevo nombreCientifico.
    */
    void setNCi(const std::string &nci);

    /**
    * @brief Devuelve el tipo de planta de un objeto Especie
    * @return Devuelve tipoPlanta.
    */
    TipoPlanta getTP() const;

    /**
    * @brief Asigna un tipo de Planta a un objeto Especie
    * @param tp Nuevo tipoPlanta.
    */
    void setTP(TipoPlanta tp);

    /**
    * @brief Muestra por pantalla los datos de la especie.
    */
    void mostrarInfo() const;

};


#endif //PR1_ESPECIE_H