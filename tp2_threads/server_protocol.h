#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <vector>

#include "common_socket.h"

class ServerProtocol {
private:
    Socket socket_servidor;

public:
    bool socket_esta_cerrado;

public:
    explicit ServerProtocol(Socket socket_aceptado);

    std::vector<char> recibir_mensaje();

    void enviar_mensaje(std::vector<char> mensaje_a_enviar);
};

#endif
