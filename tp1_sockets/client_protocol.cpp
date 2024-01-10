#include "client_protocol.h"

#include <iostream>

#include <netinet/in.h>

#define SIZE_SELECCION 9
#define SIZE_ACCION 8

#define SELECCION 1
#define ACCION 0

#define FALLO_LA_SELECCION_DE_ESCENARIO "fallo"

#define ERROR_DE_SELECCION 1

// Todos los metodos son publicos.


ClientProtocol::ClientProtocol(char* ip, char* puerto): socket_cliente(ip, puerto) {
    this->estado_socket_cliente = false;
}


void ClientProtocol::enviar_mensaje_a_servidor(std::vector<char> mensaje) {

    this->socket_cliente.sendall(mensaje.data(), mensaje.size(), &this->estado_socket_cliente);
}

void ClientProtocol::recibir_respuesta_del_servidor(int tipo_de_respuesta) {

    // posiciones del gusano recibidas por el servidor.
    uint32_t x_aux;
    uint32_t y_aux;

    // posiciones del gusano formateadas al endianess del client.
    uint32_t x;
    uint32_t y;

    switch (tipo_de_respuesta) {
        case SELECCION:

            uint8_t estado_selecion;
            this->socket_cliente.recvall(&estado_selecion, sizeof(uint8_t),
                                         &this->estado_socket_cliente);

            if (estado_selecion == ERROR_DE_SELECCION) {
                std::cout << FALLO_LA_SELECCION_DE_ESCENARIO << std::endl;
                break;
            }

            this->socket_cliente.recvall(&y_aux, sizeof(y_aux), &this->estado_socket_cliente);
            this->socket_cliente.recvall(&x_aux, sizeof(x_aux), &this->estado_socket_cliente);

            y = ntohl(y_aux);
            x = ntohl(x_aux);


            std::cout << y << " " << x << std::endl;

            break;

        default:
            this->socket_cliente.recvall(&y_aux, sizeof(y_aux), &this->estado_socket_cliente);
            this->socket_cliente.recvall(&x_aux, sizeof(x_aux), &this->estado_socket_cliente);

            y = ntohl(y_aux);
            x = ntohl(x_aux);

            std::cout << y << " " << x << std::endl;
            break;
    }
}

void ClientProtocol::finalizar_protocolo() { this->socket_cliente.close(); }
