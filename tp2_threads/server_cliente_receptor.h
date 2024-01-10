#ifndef SERVER_CLIENTE_RECEPTOR_H
#define SERVER_CLIENTE_RECEPTOR_H

#include <queue>
#include <vector>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_broadcast_manager.h"
#include "server_formateo_de_mensajes.h"
#include "server_print_manager.h"
#include "server_protocol.h"


class ClienteReceptor: public Thread {
private:
    ServerProtocol& protocolo_de_comunicacion;  // Protocolo de comunicacion con cliente;
    BroadcastManager& controlador_del_broadcast;
    PrintManager& controlador_de_impresion;
    Queue<std::vector<char>>& cola_de_mensajes;
    FormateoDeMensajes formateador;

public:
    ClienteReceptor(ServerProtocol& protocolo_a_asginar, BroadcastManager& controlador_a_asginar,
                    PrintManager& controlador_print, Queue<std::vector<char>>& cola_a_asignar);

    /*
    Lanza el hilo receptor. Da inicio a la recepcion de mensajes.
    */
    void run() override;
};


#endif
