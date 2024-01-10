#include "server_protocol.h"

#include <cstring>

#include <netinet/in.h>

#include "common_socket.h"
#include "server_acciones_de_juego.h"

#define SELECT_COMANDO 1
#define DIR_COMANDO 3
#define MOVE_COMANDO 4
#define JUMP_COMANDO 5

#define SIZE_COMANDO 1
#define SIZE_NOMBRE_ESCENARIO 2
#define SIZE_DIRECCION_DE_GIRO 1
#define SIZE_DIRECCION_DE_SALTO 1

#define COMANDO_DE_SELECCION 0
#define COMANDO_DE_ACCION 1

/*
Envia un mensaje al cliente. Este metodo solo puede ser usado una vez que se haya recibido un
mensaje por parte del cliente, y despues de que el mismo haya sido interpretado.

"Por cada meensaje recibido e interpretado debe haber una repsuesta del server al cliente"
*/
void ServerProtocol::enviar_respuesta_a_cliente(int tipo_de_comando) {

    std::vector<char> respuesta;

    uint8_t codigo = 0;
    uint32_t posicion_x_aux = (uint32_t)this->manager_de_juego.x;
    uint32_t posicion_y_aux = (uint32_t)this->manager_de_juego.y;

    uint32_t posicion_x = htonl(posicion_x_aux);
    uint32_t posicion_y = htonl(posicion_y_aux);

    switch (tipo_de_comando) {
        case COMANDO_DE_SELECCION:

            if (this->se_selecciono_escenario) {
                respuesta.resize(sizeof(uint8_t) + 2 * sizeof(uint32_t), 0);
                std::memcpy(&respuesta[0], &codigo, sizeof(codigo));
                std::memcpy(&respuesta[1], &posicion_y, sizeof(posicion_y));
                std::memcpy(&respuesta[5], &posicion_x, sizeof(posicion_x));

                this->socket_servidor.sendall(respuesta.data(), respuesta.size(),
                                              &this->estado_socket);

            } else {
                uint8_t error = 1;
                this->socket_servidor.sendall(&error, sizeof(uint8_t), &this->estado_socket);
            }


            break;

        case COMANDO_DE_ACCION:

            respuesta.resize(2 * sizeof(uint32_t), 0);
            std::memcpy(&respuesta[0], &posicion_y, sizeof(posicion_y));
            std::memcpy(&respuesta[4], &posicion_x, sizeof(posicion_x));

            this->socket_servidor.sendall(respuesta.data(), respuesta.size(), &this->estado_socket);

            break;
    }
}


/*
Procesa la selccion de un escenario.
*/
int ServerProtocol::procesar_seleccion_de_escenario() {

    uint16_t longitud_nombre_escenario_aux = 0;  // se recibe la longitud enviada por el cliente.
    uint16_t longitud_nombre_escenario = 0;      // longitud formateada al endianess del server.
    std::vector<char> nombre_escenario(sizeof(uint16_t), 0);


    this->socket_servidor.recvall(&longitud_nombre_escenario_aux, SIZE_NOMBRE_ESCENARIO,
                                  &this->estado_socket);

    longitud_nombre_escenario = ntohs(longitud_nombre_escenario_aux);

    nombre_escenario.resize(longitud_nombre_escenario + 1);

    this->socket_servidor.recvall(nombre_escenario.data(), longitud_nombre_escenario,
                                  &this->estado_socket);

    int estado_seleccion = 0;
    estado_seleccion =
            this->manager_de_escenarios.seleccionar_escenario((char*)nombre_escenario.data());

    if (estado_seleccion < 0) {
        return -1;
    }

    this->manager_de_juego.iniciar_juego(manager_de_escenarios.devolver_escenario(),
                                         manager_de_escenarios.alto_escenario,
                                         manager_de_escenarios.ancho_escenario);

    this->se_selecciono_escenario = true;

    return 0;
}


/*
Procesa una accion de cambio de direccion, se le indica al manager de juego que debe
cambiar de direccion.
 */
void ServerProtocol::procesar_cambio_de_direccion() {

    uint8_t direccion_de_giro;

    this->socket_servidor.recvall(&direccion_de_giro, SIZE_DIRECCION_DE_GIRO, &this->estado_socket);

    switch (direccion_de_giro) {
        case IZQUIERDA:
            this->manager_de_juego.realizar_accion(GIRAR_A_LA_IZQUIERDA);
            break;

        case DERECHA:
            this->manager_de_juego.realizar_accion(GIRAR_A_LA_DERECHA);
            break;
    }
}


/*
Procesa una accion de movimiento, se le indica al manager de juego que debe realizar un movimiento.
 */
void ServerProtocol::procesar_movimiento() { this->manager_de_juego.realizar_accion(MOVERSE); }


/*
Procesa una accion de salto, se le indica al manager de juego que debe realizar un salto.
 */
void ServerProtocol::procesar_salto() {

    uint8_t direccion_de_salto;

    this->socket_servidor.recvall(&direccion_de_salto, SIZE_DIRECCION_DE_SALTO,
                                  &this->estado_socket);

    switch (direccion_de_salto) {
        case ATRAS:
            this->manager_de_juego.realizar_accion(SALTAR_HACIA_ATRAS);
            break;

        case ADELANTE:
            this->manager_de_juego.realizar_accion(SALTAR_HACIA_ADELANTE);
            break;
    }
}


/*
Recibe y procesa los mensajes recibidos por el cliente. Se asume que los mensajes son enviados en
el formato requerido por el protocolo del servidor.
 */
void ServerProtocol::procesar_mensaje_cliente() {

    uint8_t codigo_comando = 0;

    this->socket_servidor.recvall(&codigo_comando, SIZE_COMANDO, &this->estado_socket);

    switch (codigo_comando) {

        case SELECT_COMANDO:
            this->procesar_seleccion_de_escenario();
            this->enviar_respuesta_a_cliente(COMANDO_DE_SELECCION);
            break;

            if (this->se_selecciono_escenario) {
                case DIR_COMANDO:
                    this->procesar_cambio_de_direccion();
                    this->enviar_respuesta_a_cliente(COMANDO_DE_ACCION);
                    break;

                case MOVE_COMANDO:
                    this->procesar_movimiento();
                    this->enviar_respuesta_a_cliente(COMANDO_DE_ACCION);
                    break;

                case JUMP_COMANDO:
                    this->procesar_salto();
                    this->enviar_respuesta_a_cliente(COMANDO_DE_ACCION);
                    break;
            }
    }
}


// metodos publicos:


ServerProtocol::ServerProtocol(char* puerto, char* path_file_escenarios):
        socket_aceptador(puerto),
        socket_servidor(socket_aceptador.accept()),
        manager_de_escenarios(path_file_escenarios),
        manager_de_juego() {
    this->estado_socket = false;
    this->se_selecciono_escenario = false;
}


void ServerProtocol::iniciar_protocolo() {

    while (!this->estado_socket) {
        procesar_mensaje_cliente();

        if (this->se_selecciono_escenario && !this->estado_socket) {
            this->manager_de_juego.mostrar_estado();
        }
    }
}
