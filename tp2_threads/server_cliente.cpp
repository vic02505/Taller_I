#include "server_cliente.h"

#include <utility>


void Cliente::enviar_mensajes() {

    std::vector<char> mensaje_a_enviar(0);

    try {
        while (this->protocolo_de_comunicacion.socket_esta_cerrado == false) {
            mensaje_a_enviar = this->cola_de_mensajes.pop();
            this->protocolo_de_comunicacion.enviar_mensaje(mensaje_a_enviar);
        }

    } catch (const std::exception& err) {
        this->estado_comunicador = false;
    }
}


Cliente::Cliente(Socket socket_a_asignar, BroadcastManager& controlador_a_asginar,
                 PrintManager& controlador_print):
        protocolo_de_comunicacion(std::move(socket_a_asignar)),
        controlador_del_broadcast(controlador_a_asginar),
        controlador_de_impresion(controlador_print),
        receptor_de_mensajes(protocolo_de_comunicacion, controlador_del_broadcast,
                             controlador_de_impresion, cola_de_mensajes) {
    this->controlador_del_broadcast.agregar_cola_a_la_lista(this->cola_de_mensajes);
}


void Cliente::run() {
    receptor_de_mensajes.start();
    this->enviar_mensajes();
    receptor_de_mensajes.join();
}
