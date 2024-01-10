#ifndef CLIENT_PROTOCOL_COMANDOS_H
#define CLIENT_PROTOCOL_COMANDOS_H

#include <vector>

#include "common_socket.h"


class ClientProtocol {

    // atributos:
private:
    Socket socket_cliente;
    bool estado_socket_cliente;

    // metodos:
public:
    /*
    Constructor de clase. Los parametros reqeuridos son la ip y puerto del server con el que se
    desea establecer una conexion.

    ADVERTENCIA: El constructor fallara si el servidor no se encuentra a la espera de una conexion.
    Esto es, al momento de construir la clase se intentara establcer conexion automaticamente con el
    servidor referenciado por la ip y su puerto.
    */
    ClientProtocol(char* ip, char* puerto);

    /*
    Envia un mensaje al servidor. mensaje debe haber sido previamente parseado y formateado por la
    clase client_parsing.cpp.
    */
    void enviar_mensaje_a_servidor(std::vector<char> mensaje);

    /*
    Recibe una respuesta del servidor y muestra el estado de la misma en pantalla.

    ADVERTENCIA: Solo usar si se envio un mensaje. Por cada enviar debe haber un recibir.
    */
    void recibir_respuesta_del_servidor(int tipo_de_respuesta);

    /*
    Finaliza la conexion con el servidor.
    */
    void finalizar_protocolo();
};

#endif
