#ifndef SERVER_CLIENTE_H
#define SERVER_CLIENTE_H

#include <vector>

#include "common_socket.h"
#include "common_thread.h"
#include "server_broadcast_manager.h"
#include "server_cliente_receptor.h"
#include "server_print_manager.h"
#include "server_protocol.h"


class Cliente: public Thread {
private:
    ServerProtocol protocolo_de_comunicacion;
    BroadcastManager& controlador_del_broadcast;
    PrintManager& controlador_de_impresion;
    ClienteReceptor receptor_de_mensajes;
    Queue<std::vector<char>> cola_de_mensajes;
    std::atomic<bool> estado_comunicador{true};

    /*
    Envia mensajes de la cola de mensajes al cliente asociado a este hilo.
    */
    void enviar_mensajes();

public:
    Cliente(Socket socket_a_asignar, BroadcastManager& controlador_a_asginar,
            PrintManager& controlador_print);

    /*
    Corre el hilo cliente. El hilo cliente se comporta como un emisor de mensajes.
    Este hilo maneja tambien la recepcion de mensajes usando de forma interna (privada)
    otro hilo.
    */
    void run() override;
};


#endif
