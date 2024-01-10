#include <iostream>
#include <string>

#include "client_parsing.h"
#include "client_protocol.h"

// Funciones publicas:

void iniciar_juego(char* ip, char* puerto) {

    std::vector<char> mensaje_server;
    ClientProtocol protocolo_cliente(ip, puerto);

    while (!std::cin.eof()) {

        mensaje_server = procesar_mensaje();

        if (mensaje_server.size() > 0) {
            protocolo_cliente.enviar_mensaje_a_servidor(mensaje_server);
            protocolo_cliente.recibir_respuesta_del_servidor((uint8_t)mensaje_server[0]);
        }
    }

    protocolo_cliente.finalizar_protocolo();
}
