#include <iostream>
using namespace std;
#include "ControlParques.h"
#include "Especie.h"
#include "Parque.h"
#include "ListaDEnlazada.h"
#include "TipoPlanta.h"


void mostrar(ListaDEnlazada<int> &l) {
    ListaDEnlazada<int>::Iterador it=l.iterador();
    while (!it.fin()) {
        cout<<it.dato()<<"  ";
        it.siguiente();
    }

}

int main() {


    cout << endl << "PRUEBA1: LISTA DOBLE:" << endl;
    
        //Creamos la lista de enteros vacia
        ListaDEnlazada<int> lista;

        //Insertamos valores de 101 a 200
        for (int i = 101; i <= 200; i++)
            lista.insertarFinal(i);
        mostrar(lista);

        //insertamos por el comienzo del 98 a 1
        for (int i = 98; i >= 1; i--)
            lista.insertarInicio(i);
        mostrar(lista);

        //insertamos el 100 delante de 101
        ListaDEnlazada<int>::Iterador it = lista.iterador(); //it llegara hasta la posicion 101
        while (it.dato() != 101) {
            it.siguiente();
        }
        //insertar inserta el dato 100 DELANTE de 101
        lista.insertar(it, 100);
        mostrar(lista);

        //inserta el dato 99 detras del 98
        ListaDEnlazada<int>::Iterador it2 = lista.iterador();
        while (it2.dato() != 98) {
            it2.siguiente();
        }//termina el while y apunta al dato 98

        it2.siguiente();//avanzamos una posicion para insertar DELANTE de 98+1
        lista.insertar(it2, 99);//insertando el dato detras de 98
        mostrar(lista);

        //borramos los 10 primeros datos
        for (int i = 0; i < 10; i++) {
            lista.borrarInicio();
        }
        //borramos los 10 ultimos datos
        for (int i = 0; i < 10; i++) {
            lista.borrarFinal();
        }
        mostrar(lista);

        //borramos los multiplos de 10
        //creamos un iterador auxiliar que nos va a servir para el borrado
        ListaDEnlazada<int>::Iterador itsig;
        it = lista.iterador();
        while (!it.fin()) {
            if (it.dato() % 10 == 0) {
                itsig = it;
                itsig.siguiente();
                lista.borrar(it);
                it = itsig;
            } else
                it.siguiente();
        }

        cout << " LISTA FINAL:" << endl;
        mostrar(lista);


    //PRUEBA II::probar funcionalidad de ControlParques
    try{

        cout << "Comienzo de lectura de los ficheros" << endl;
        ControlParques control("../arbolado-especies.csv","../parques.csv");
        //en el controlparques, nos aseguramos de que lo metemos en el vector dinamico y ademas lo ordenamos de menor a mayor por su codigo

        //Prueba 1: declaramos un puntero de tipo parque, que almacenara el resultado de la busqueda
        if (Parque* p=control.buscarParque("PARQUE PRINCESA LEONOR")) {
            if (p->existeNbreCom("Eucalipto rojo")) {   //p apunta al parque que hemos encontrado
                cout << "El parque: PARQUE PRINCESA LEONOR contiene Eucalipto rojo" << endl;
            }else {
                cout << "El parque: PARQUE PRINCESA LEONOR NO contiene Eucalipto rojo" << endl;
            }
        }
        if (Parque* p=control.buscarParque("PARQUE PRINCESA LEONOR")) {
            if (p->existeNbreCom("Arce de sierra")) {
                cout << "El parque: PARQUE PRINCESA LEONOR contiene Arce de sierra" << endl;
            }else {
                cout << "El parque: PARQUE PRINCESA LEONOR NO contiene Arce de sierra" << endl;
            }
        }

        //Prueba 2:
        if (Parque* p=control.buscarParque("PARQUE MADRID RIO")) {
            if (p && p->existeNbreCie("Hebe floribunda")) {
                cout << "El parque: PARQUE MADRID RIO contiene Hebe floribunda" << endl;
            }else {
                cout << "El parque: PARQUE MADRID RIO NO contiene Hebe floribunda" << endl;
            }
        }
        if (Parque* p=control.buscarParque("PARQUE MADRID RIO")) {
            if (p && p->existeNbreCie("Ananas comosus")) {
                cout << "El parque: PARQUE MADRID RIO contiene Ananas comosus" << endl;
            }else {
                cout << "El parque: PARQUE MADRID RIO NO contiene Ananas comosus" << endl;
            }
        }

        //aptdo 3
        if (Parque* p=control.buscarParque("PARQUE JUAN CARLOS III")) {
            cout << "PARQUE JUAN CARLOS III existe con codigo: " << p->get_cod_parque() << endl;
        }else
            cout << "PARQUE JUAN CARLOS III NO existe" << endl;

        if (Parque* p=control.buscarParque("VIVERO DE MIGAS CALIENTES")) {
            cout << "VIVERO DE MIGAS CALIENTES existe con codigo: " << p->get_cod_parque() << endl;
        }else
            cout << "VIVERO DE MIGAS CALIENTES NO existe" << endl;

        //aptdo 4
        VDinamico<Especie*> listado=control.listadoEspeciesSubNbre("rosa");
        for (int i=0; i<listado.tama(); i++) {
            cout << i << " Codigo= " << listado[i]->getcodigoEspecie() <<
                " NombreCient.=" << listado[i]->getnombre_cientifico() <<
                " NombreComun=" << listado[i]->getnombre_comun() <<
                " TipoPlanta=" << tipoPlantaToString(listado[i]->gettipo_planta()) <<  endl;
        }

        //aptdo 5
        int cont= control.contarEspecieParque("Abeto");
        cout << "No. Parques con especie Abeto: " << cont << endl;

        //PAREJAS 1
        cout << "ANTES " << control.contarEspecieParque("Abeto");
        control.EliminaEspecieNbreComun("Abeto");
        cout << "\nDESPUES " << control.contarEspecieParque("Abeto");

        //PAREJAS 2
        cout << "Intentando Borrar VIVERO DE MIGAS CALIENTES....";
        control.eliminarParque( "VIVERO DE MIGAS CALIENTES");
        if (Parque* p=control.buscarParque("VIVERO DE MIGAS CALIENTES")) {
            cout << "\nVIVERO DE MIGAS CALIENTES existe con codigo: " << p->get_cod_parque() << endl;
        }else
            cout << "\nVIVERO DE MIGAS CALIENTES NO existe" << endl;

        cout << endl << "FIN DE LA APLICACION....";

    }catch (std::out_of_range &e){
        std::cerr << e.what() << std::endl;
    }catch (std::runtime_error &e){
        std::cerr << "Excepcion en fichero: " << e.what() << std::endl;
    }catch (std::bad_alloc &e){
        std::cerr << "No hay memoria suficiente para el objeto dinamico" << std::endl;
    }

    return 0;

}