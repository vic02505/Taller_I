#include "client_protocol.h"

#include <iostream>

#include <arpa/inet.h>

#include "client_acciones.h"


// Constructores y metodos publicos:


ClientProtocol::ClientProtocol(char* ip, char* puerto): socket_cliente(ip, puerto) {
    this->socket_esta_cerrado = false;
}

void ClientProtocol::enviar_mensaje_a_servidor(const std::string& comando,
                                               const std::string& argumento) {

    std::vector<char> mensaje_a_enviar = this->procesador_de_mensajes(comando, argumento);

    if (this->socket_esta_cerrado == true) {
        throw LibError(errno, "El socket se cerro y no se pudo enviar el mensaje al servidor");
    }

    this->socket_cliente.sendall(mensaje_a_enviar.data(), mensaje_a_enviar.size(),
                                 &this->socket_esta_cerrado);
}


std::vector<char> ClientProtocol::obtener_respuesta_de_servidor() {

    std::vector<char> respuesta;

    if (this->socket_esta_cerrado == true) {
        throw LibError(errno, "El socket se cerro y no se pudo recibir el mensaje del servidor");
    }

    uint8_t codigo_respuesta;
    uint16_t longitud_mensaje;

    uint8_t cantidad_de_jugadores;

    std::vector<char> mensaje_aux(0);
    std::string mensaje;

    this->socket_cliente.recvall(&codigo_respuesta, sizeof(codigo_respuesta),
                                 &this->socket_esta_cerrado);

    switch (codigo_respuesta) {
        case CHAT_CODIGO_RCV:
            this->socket_cliente.recvall(&longitud_mensaje, sizeof(longitud_mensaje),
                                         &this->socket_esta_cerrado);
            longitud_mensaje = ntohs(longitud_mensaje);
            mensaje_aux.resize(longitud_mensaje, 0);

            this->socket_cliente.recvall(&mensaje_aux[0], longitud_mensaje,
                                         &this->socket_esta_cerrado);
            mensaje = std::string(mensaje_aux.begin(), mensaje_aux.end());
            std::cout << mensaje << std::endl;
            break;
        case PLAYER_COUNT_CODIGO:
            this->socket_cliente.recvall(&cantidad_de_jugadores, sizeof(cantidad_de_jugadores),
                                         &this->socket_esta_cerrado);
            std::cout << "Jugadores " << (int)cantidad_de_jugadores;
            std::cout << ", esperando al resto de tus amigos..." << std::endl;

            break;

        default:
            throw("El formato de mensajes enviado por el servidor no es el esperado");
            break;
    }


    return respuesta;
}
