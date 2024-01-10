#include <iostream>

#include "client_lobby.h"

#define ARGUMENTOS_ESPERADOS 3

int main(int argc, char* argv[]) {

    try {

        if (argc != ARGUMENTOS_ESPERADOS) {
            std::cerr << "Llamada erronea al programa, se esperaban recibir: "
                      << ARGUMENTOS_ESPERADOS << " argumentos." << std::endl;
            std::cerr << "Enviaste: " << argc << " argumento(s)!!" << std::endl
                      << "Recordar que se esperan recibir: ip como primer argumento, un puerto "
                         "como segundo argumento"
                      << std::endl;
            return 1;
        }

        ClientLobby lobby_cliente(argv[1], argv[2]);
        lobby_cliente.ingresar_al_lobby();

        return 0;

    } catch (const std::exception& error) {

        std::cerr << "Algo salio mal y una excepcion fue lanzada." << std::endl
                  << error.what() << std::endl;


    } catch (...) {
        std::cerr << "Algo salio mal, y se lanzo una excepcion de tipo desconocido :(";
    }
}
