#ifndef SERVER_LOBBY_H
#define SERVER_LOBBY_H

// Manejo del lobby desde la perspectiva del servidor.

class Lobby {
public:
    /*
    Inicia la ejecucion del lobby desde la perspectiva del servidor.
    (recepcion de mensajes, envio de mensajes a clientes).
    */
    void iniciar_lobby(char* puerto_servidor);
};


#endif
