#ifndef SERVER_MANEJO_DE_ESCENARIOS_H
#define SERVER_MANEJO_DE_ESCENARIOS_H

#include <fstream>
#include <map>
#include <string>
#include <utility>

class ManejoDeEscenarios {

    // atributos
private:
    std::map<std::pair<int, int>, std::string> escenario;
    std::fstream file_escenarios;

public:
    std::string nombre_escenario;
    int alto_escenario, ancho_escenario;

    // metodos
private:
    int buscar_escenario_en_file(const char* escenario_a_seleccionar);

    void cargar_escenario();

    void mostrar_escenario();

public:
    /*
    Constructor de clase. Recibe un path a un archivo con escenarios. El constructor abre el
    archivo de forma que se mantenga abierto durante el uso de la clase ManejoDeEscenario.
    En caso de un error al abrir el archivo o que el archivo sea inexistente no se construye
    la clase.
    */
    explicit ManejoDeEscenarios(const char* path_file_escenarios);

    /*
    Recibe un nombre de escenario y lo busca dentro del archivo de escenarios para ser seleccionado.
    */
    int seleccionar_escenario(const char* escenario_a_seleccionar);

    /*
    Devuelve una copia del escenario seleccionado. Antes de usar este metodo debe seleccionarse
    un escenario, de lo contrario el comportamiento es indefinido.
    */
    std::map<std::pair<int, int>, std::string> devolver_escenario();
};

#endif
