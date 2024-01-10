#include "client_lobby.h"

#include <iostream>
#include <string>

#include <errno.h>

#include "client_acciones.h"
#include "client_parsing.h"
#include "client_protocol.h"
#include "common_liberror.h"

// Metodos privados:


void ClientLobby::recibir_mensajes_del_server(int mensajes_a_recibir) {

    for (int i = 0; i < mensajes_a_recibir; i++) {
        this->protocolo_cliente.obtener_respuesta_de_servidor();
    }
}


// Constructores y metodos publicos:


ClientLobby::ClientLobby(char* ip_server, char* puerto_server):
        protocolo_cliente(ip_server, puerto_server) {}


void ClientLobby::ingresar_al_lobby() {

    std::string comando;  // Que quiere hacer el cliente.
    std::string argumento;

    bool cliente_sigue_conectado = true;

    while (cliente_sigue_conectado) {

        parsear_entrada_estandar(comando, argumento);

        if (comando == CHAT_COMANDO) {
            this->protocolo_cliente.enviar_mensaje_a_servidor(comando, argumento);
        } else if (comando == READ_COMANDO) {
            int mensajes_a_leer = atoi(argumento.c_str());
            this->recibir_mensajes_del_server(mensajes_a_leer);
        } else if (comando == EXIT_COMANDO) {
            cliente_sigue_conectado = false;
        } else {
            throw LibError(errno, "No se cumplio con el formato de los mensajes de cliente "
                                  "indicado en la documentacion");
        }
    }
}
