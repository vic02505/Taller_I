#include "client_parsing.h"

#include "client_acciones.h"


void parsear_entrada_estandar(std::string& comando, std::string& argumento) {

    std::cin >> comando;
    if (comando != EXIT_COMANDO) {
        std::cin >> std::ws;
        std::getline(std::cin, argumento);
    }
}
