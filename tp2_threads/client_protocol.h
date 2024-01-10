#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include <errno.h>

#include "client_procesamiento_de_mensajes.h"
#include "common_liberror.h"
#include "common_socket.h"

class ClientProtocol {
private:
    Socket socket_cliente;
    bool socket_esta_cerrado;
    ProcesadorDeMensajes procesador_de_mensajes;


public:
    ClientProtocol(char* ip, char* puerto);

    /*
    Envia un mensaje al servidor a partir de un comando y de su argumento.
    */
    void enviar_mensaje_a_servidor(const std::string& comando, const std::string& argumento);

    std::vector<char> obtener_respuesta_de_servidor();
};


#endif
