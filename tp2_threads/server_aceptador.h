#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <atomic>
#include <queue>
#include <vector>

#include "common_socket.h"
#include "common_thread.h"
#include "server_broadcast_manager.h"
#include "server_formateo_de_mensajes.h"
#include "server_print_manager.h"
#include "server_protocol.h"

class ServerAceptador: public Thread {
private:
    std::vector<Thread*> lista_de_clientes;
    Socket socket_aceptador;  // acepta pedidos de conexion de clientes.
    BroadcastManager controlador_del_broadcast;
    PrintManager controlador_de_impresion;
    std::atomic<bool> se_siguen_aceptando_clientes{true};
    FormateoDeMensajes formateador;

    void enviar_cantidad_de_jugadores();


    /*
    Limpia del servidor a los clientes que se desconectaron en
    algun momento de su ejecucion.

    NOTA: Lo que hace este metodo es limpiar basura del servidor, solo
    limpia a los clientes que se desconectaron por cuenta propia.
    */
    void limpiar_clientes_desconectados();


    /*
    Finaliza la conexion con TODOS los clientes.

    NOTA: Solo usar este metodo para manejar el cierre del aceptador.
    */
    void limpiar_clientes_de_la_lista();

public:
    explicit ServerAceptador(char* puerto);

    /*
    Finaliza el aceptador. Se desconectan todos los clientes y se dejan de
    aceptar mas clientes.

    NOTA: Es reponsabilidad del usuario de la biblioteca decidir cuando se dejan
    de aceptar clientes.
    */
    void dejar_de_aceptar_clientes();


    /*
    Correr el hilo aceptador.

    Al correr el hilo aceptador se empiezan a aceptar clientes que desean conectarse
    al sevidor.

    NOTA: Es reponsabilidad del usuario de la biblioteca decidir cuando se dejan
    de aceptar clientes.
    */
    void run() override;
};


#endif
