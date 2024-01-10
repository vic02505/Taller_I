#include "server_cliente_receptor.h"

#include <iostream>
#include <utility>
#include <vector>

ClienteReceptor::ClienteReceptor(ServerProtocol& protocolo_a_asginar,
                                 BroadcastManager& controlador_a_asginar,
                                 PrintManager& controlador_print,
                                 Queue<std::vector<char>>& cola_a_asignar):
        protocolo_de_comunicacion(protocolo_a_asginar),
        controlador_del_broadcast(controlador_a_asginar),
        controlador_de_impresion(controlador_print),
        cola_de_mensajes(cola_a_asignar),
        formateador() {}


void ClienteReceptor::run() {

    while (this->protocolo_de_comunicacion.socket_esta_cerrado == false) {

        std::vector<char> mensaje_cliente = this->protocolo_de_comunicacion.recibir_mensaje();

        if (this->protocolo_de_comunicacion.socket_esta_cerrado == false) {

            std::vector<char> mensaje_formateado =
                    this->formateador.formatear_mensaje_de_chat(mensaje_cliente);
            this->controlador_del_broadcast.agregar_mensaje(mensaje_formateado);
            this->controlador_de_impresion.mostrar_mensaje_de_cliente(mensaje_cliente);
        }
    }

    this->cola_de_mensajes.close();
    this->controlador_del_broadcast.eliminar_cola_de_la_lista(this->cola_de_mensajes);

    int cantidad_de_jugadores = this->controlador_del_broadcast.clientes_en_linea();
    std::vector<char> mensaje_a_enviar =
            this->formateador.formatear_cantidad_de_jugadores(cantidad_de_jugadores);
    this->controlador_del_broadcast.agregar_mensaje(mensaje_a_enviar);

    this->controlador_de_impresion.mostrar_clientes_en_linea();
}
