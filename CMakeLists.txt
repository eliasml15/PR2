cmake_minimum_required(VERSION 4.0)
project(PR2)

set(CMAKE_CXX_STANDARD 20)

add_executable(PR1 main.cpp VDinamico.h Especie.h Especie.cpp ControlParques.h ControlParques.cpp ListaDEnlazada.h
        Parque.h Parque.cpp LectorCSV.h LectorCSV.cpp TipoPlanta.h)
