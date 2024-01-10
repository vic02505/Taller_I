#include "server_formateo_de_mensajes.h"

#include <cstdint>
#include <cstring>
#include <iostream>

#include <arpa/inet.h>

#include "server_codigos.h"


std::vector<char> FormateoDeMensajes::formatear_cantidad_de_jugadores(int cantidad_de_jugadores) {


    std::vector<char> mensaje_formateado(0);

    uint8_t codigo_mensaje = PLAYER_COUNT_CODIGO;
    uint8_t jugadores_en_linea = cantidad_de_jugadores;

    mensaje_formateado.resize(sizeof(codigo_mensaje) + sizeof(jugadores_en_linea), 0);
    std::memcpy(&mensaje_formateado[0], &codigo_mensaje, sizeof(codigo_mensaje));
    std::memcpy(&mensaje_formateado[sizeof(codigo_mensaje)], &jugadores_en_linea,
                sizeof(jugadores_en_linea));


    return mensaje_formateado;
}


std::vector<char> FormateoDeMensajes::formatear_mensaje_de_chat(std::vector<char> mensaje_de_chat) {

    std::vector<char> mensaje_formateado(0);

    uint8_t codigo_mensaje = CHAT_CODIGO;

    uint16_t longitud_mensaje = mensaje_de_chat.size();

    mensaje_formateado.resize(sizeof(codigo_mensaje) + sizeof(longitud_mensaje) + longitud_mensaje,
                              0);

    longitud_mensaje = htons(longitud_mensaje);

    std::memcpy(&mensaje_formateado[0], &codigo_mensaje, sizeof(codigo_mensaje));
    std::memcpy(&mensaje_formateado[sizeof(codigo_mensaje)], &longitud_mensaje,
                mensaje_de_chat.size());
    std::memcpy(&mensaje_formateado[sizeof(codigo_mensaje) + sizeof(longitud_mensaje)],
                mensaje_de_chat.data(), mensaje_de_chat.size());

    return mensaje_formateado;
}
