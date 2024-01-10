#include "server_protocol.h"

#include <iostream>
#include <utility>

#include <arpa/inet.h>

#define CODIGO_CHAT 0x05

ServerProtocol::ServerProtocol(Socket socket_aceptado):
        socket_servidor(std::move(socket_aceptado)) {
    this->socket_esta_cerrado = false;
}


std::vector<char> ServerProtocol::recibir_mensaje() {

    uint8_t codigo_mensaje;
    std::vector<char> error(0);

    bool se_recibio_algo = this->socket_servidor.recvall(&codigo_mensaje, sizeof(codigo_mensaje),
                                                         &this->socket_esta_cerrado);

    if (!se_recibio_algo) {
        return error;
    }

    uint16_t longitud_de_mensaje;
    this->socket_servidor.recvall(&longitud_de_mensaje, sizeof(longitud_de_mensaje),
                                  &this->socket_esta_cerrado);

    longitud_de_mensaje = ntohs(longitud_de_mensaje);

    std::vector<char> mensaje(longitud_de_mensaje, 0);

    this->socket_servidor.recvall(mensaje.data(), longitud_de_mensaje, &this->socket_esta_cerrado);

    return mensaje;
}

void ServerProtocol::enviar_mensaje(std::vector<char> mensaje_a_enviar) {
    this->socket_servidor.sendall(mensaje_a_enviar.data(), mensaje_a_enviar.size(),
                                  &this->socket_esta_cerrado);
}
