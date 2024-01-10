#include <iostream>

#include "server_lobby.h"
#include "server_protocol.h"

#define ARGUMENTOS_ESPERADOS 2

int main(int argc, char* argv[]) {

    try {

        if (argc != ARGUMENTOS_ESPERADOS) {
            std::cerr << "Llamada erronea al programa, se esperaban recibir: "
                      << ARGUMENTOS_ESPERADOS << " argumentos." << std::endl;
            std::cerr << "Enviaste: " << argc << " argumento(s)!!" << std::endl
                      << "Recordar que se espera como unico argumento al puerto del servidor!"
                      << std::endl;
            return 1;
        }

        Lobby lobby;
        lobby.iniciar_lobby(argv[1]);

        return 0;

    } catch (const std::exception& error) {
        std::cerr << "Algo salio mal y una excepcion fue lanzada." << std::endl
                  << error.what() << std::endl;

    } catch (...) {
        std::cerr << "Algo salio mal, y se lanzo una excepcion de tipo desconocido :(";
    }
}
