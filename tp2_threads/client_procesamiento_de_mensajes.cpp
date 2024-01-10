#include "client_procesamiento_de_mensajes.h"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>

#include "client_acciones.h"
#include "common_liberror.h"


// Metodos privados:


std::vector<char> ProcesadorDeMensajes::formatear_mensaje(const std::string& comando,
                                                          const std::string& argumento) {

    std::vector<char> mensaje_formateado(0);

    if (comando != CHAT_COMANDO) {
        throw LibError(errno, "El comando indicado para ser enviado al servidor no es valido\n");
    }
    uint8_t codigo_comando;
    codigo_comando = CHAT_CODIGO_SENDER;

    uint16_t longitud_mensaje_de_chat = argumento.size();
    uint16_t longitud_mensaje_de_chat_aux = htons(longitud_mensaje_de_chat);

    mensaje_formateado.resize(
            sizeof(codigo_comando) + sizeof(longitud_mensaje_de_chat) + longitud_mensaje_de_chat,
            0);

    std::memcpy(&mensaje_formateado[0], &codigo_comando, sizeof(codigo_comando));
    std::memcpy(&mensaje_formateado[sizeof(codigo_comando)], &longitud_mensaje_de_chat_aux,
                sizeof(longitud_mensaje_de_chat));
    std::memcpy(&mensaje_formateado[sizeof(codigo_comando) + sizeof(longitud_mensaje_de_chat)],
                argumento.c_str(), longitud_mensaje_de_chat);


    return mensaje_formateado;
}


std::vector<char> ProcesadorDeMensajes::procesar_mensaje(const std::string& comando,
                                                         const std::string& argumento) {

    std::vector<char> mensaje_procesado;

    mensaje_procesado = formatear_mensaje(comando, argumento);

    return mensaje_procesado;
}


// Metodos publicos:

// functor:
std::vector<char> ProcesadorDeMensajes::operator()(const std::string& comando,
                                                   const std::string& argumento) {
    return this->procesar_mensaje(comando, argumento);
}
