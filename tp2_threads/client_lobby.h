#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include "client_protocol.h"

class ClientLobby {
private:
    ClientProtocol protocolo_cliente;

    /*
    Recibe del servidor la cantidad de mensajes especificadas en el parametro
    mensajes_a_recibir.

    NOTA: Este metodo es bloqueante. Es decir, se quedara en espera hasta que se
    reciba la cantida de mensajes especificados por el parametro.
    */
    void recibir_mensajes_del_server(int mensajes_a_recibir);


public:
    /*
    Constructor. Se encarga de conectar el cliente al lobby si todo sale bien.
    */
    ClientLobby(char* ip_server, char* puerto_server);

    /*
    Permite el ingreso de un cliente al lobby del juego. ip y puerto
    deben ser el ip y el puerto correspondientes al server donde se
    encuentra alojado el juego.

    EL procedimiento se encarga del manejo del lobby desde la perespectiva del cliente.
    */
    void ingresar_al_lobby();
};

#endif
