#include "server_lobby.h"

#include <iostream>

#include "server_aceptador.h"

#define SENIAL_DE_CIERRE_DE_LOBBY 'q'

void Lobby::iniciar_lobby(char* puerto_servidor) {

    ServerAceptador aceptador_de_clientes(puerto_servidor);
    aceptador_de_clientes.start();

    char estado_del_lobby = 'x';  // Sigue funcionando hasta tener como valor q
    while (estado_del_lobby != SENIAL_DE_CIERRE_DE_LOBBY) {
        std::cin >> estado_del_lobby;
    }

    aceptador_de_clientes.dejar_de_aceptar_clientes();
    aceptador_de_clientes.join();
}
