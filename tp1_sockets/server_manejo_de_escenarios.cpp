#include "server_manejo_de_escenarios.h"

#include <iostream>
#include <limits>
#include <vector>

#include <string.h>

#define ERROR -1
#define EXITO 0

// Metodos privados:


/*
Dado un nombre se busca el nombre del escenario en el archivo.
Advertencia: Este metodo puede ser usado unicamente por el metodo publico
seleccionar_escenario.
*/
int ManejoDeEscenarios::buscar_escenario_en_file(const char* escenario_a_seleccionar) {

    this->nombre_escenario = "random";
    this->ancho_escenario = -1;
    this->alto_escenario = -1;

    this->file_escenarios >> this->ancho_escenario >> this->alto_escenario >>
            this->nombre_escenario;

    while (this->nombre_escenario != escenario_a_seleccionar) {

        int lineas_a_leer = 0;
        lineas_a_leer = this->alto_escenario + 1;
        std::string basura;  // ignoro las lineas leidas.

        while (lineas_a_leer != 0) {
            std::getline(file_escenarios, basura);
            lineas_a_leer--;
        }

        if (this->file_escenarios.eof()) {
            return ERROR;
        }

        this->file_escenarios >> this->ancho_escenario >> this->alto_escenario >>
                this->nombre_escenario;
    }

    this->file_escenarios.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return EXITO;
}


/*
Se encarga de leer el escenario selccionado del archivo y cargarlo a un map.

Advertencia: Solo usar este metodo en el meotodo publico seleccionar_escenario. Solo usar
una vez se haya buscado un escenario por su nombre en el archivo. De lo contrario el comportamiento
es indefinido.
*/
void ManejoDeEscenarios::cargar_escenario() {

    std::string linea;

    for (int i = 0; i < this->alto_escenario; i++) {
        std::getline(this->file_escenarios, linea);

        for (int j = 0; j < this->ancho_escenario; j++) {
            this->escenario[std::make_pair(i, j)] = linea[j];
        }
    }
}


/*
Genera una copia del escenario.
*/
std::map<std::pair<int, int>, std::string> copiar_escenario(
        const std::map<std::pair<int, int>, std::string>& escenario_original) {
    return escenario_original;
}


// Metodos publicos;

ManejoDeEscenarios::ManejoDeEscenarios(const char* path_file_escenarios):
        file_escenarios(path_file_escenarios, std::ios::in) {
    this->ancho_escenario = -1;
    this->alto_escenario = -1;
    this->nombre_escenario = "random";
}


int ManejoDeEscenarios::seleccionar_escenario(const char* escenario_a_seleccionar) {
    int estado_busqueda = 0;
    estado_busqueda = buscar_escenario_en_file(escenario_a_seleccionar);

    if (estado_busqueda != EXITO) {
        return ERROR;
    }

    cargar_escenario();
    return EXITO;
}

std::map<std::pair<int, int>, std::string> ManejoDeEscenarios::devolver_escenario() {

    return copiar_escenario(this->escenario);
}
