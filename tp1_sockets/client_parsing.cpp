#include "client_parsing.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include <arpa/inet.h>
#include <inttypes.h>
#include <string.h>

#define SELECT_CODE 1
#define DIR_CODE 3
#define MOVE_CODE 4
#define JUMP_CODE 5

#define SELECT_COMANDO "select"
#define DIR_COMANDO "dir"
#define MOVE_COMANDO "move"
#define JUMP_COMANDO "jump"

// Privado:

/*
Dado un comando y un argumento, genera un mensaje (vector de chars) formateado con
el formato requerido por el protocolo del servidor.

Se debe respetar el formato definido por el juego:

comando solo puede tomar los valores: "select", "dir", "move", y "jump". Por otras parte,
argumento puede tomar distintos valores dependiendo de quien sea comando; nombre si escenario
en caso de un select, 0 o 1 en caso de un dir, nada en caso de un move, y 0 o 1 en caso de un jump.

ADVERTENCIA: En caso de no respetar el formato, el vector de chars obtenido es indefinido.
*/
std::vector<char> formatear_mensaje_cliente(char* comando, char* argumento) {

    uint8_t codigo_comando;
    std::vector<char> mensaje(sizeof(codigo_comando));

    if (strcmp(comando, SELECT_COMANDO) == 0) {
        codigo_comando = SELECT_CODE;
        uint16_t longitud_nombre_escenario = (uint16_t)strlen(argumento);

        uint16_t len_aux = htons(longitud_nombre_escenario);

        mensaje.resize(sizeof(codigo_comando) + sizeof(longitud_nombre_escenario) +
                               longitud_nombre_escenario,
                       0);

        std::memcpy(&mensaje[0], &codigo_comando, sizeof(codigo_comando));
        std::memcpy(&mensaje[sizeof(codigo_comando)], &len_aux, sizeof(longitud_nombre_escenario));
        std::memcpy(&mensaje[sizeof(codigo_comando) + sizeof(longitud_nombre_escenario)], argumento,
                    longitud_nombre_escenario);

    } else if (strcmp(comando, DIR_COMANDO) == 0) {
        codigo_comando = DIR_CODE;
        uint8_t direccion_de_giro = (uint8_t)atoi(argumento);

        mensaje.resize(sizeof(codigo_comando) + sizeof(direccion_de_giro), 0);

        std::memcpy(&mensaje[0], &codigo_comando, sizeof(codigo_comando));
        std::memcpy(&mensaje[sizeof(codigo_comando)], &direccion_de_giro,
                    sizeof(direccion_de_giro));

    } else if (strcmp(comando, MOVE_COMANDO) == 0) {
        codigo_comando = MOVE_CODE;

        std::memcpy(&mensaje[0], &codigo_comando, sizeof(codigo_comando));

    } else if (strcmp(comando, JUMP_COMANDO) == 0) {
        codigo_comando = JUMP_CODE;
        uint8_t sentido_de_salto = (uint8_t)atoi(argumento);

        mensaje.resize(sizeof(codigo_comando) + sizeof(sentido_de_salto));

        std::memcpy(&mensaje[0], &codigo_comando, sizeof(codigo_comando));
        std::memcpy(&mensaje[sizeof(codigo_comando)], &sentido_de_salto, sizeof(sentido_de_salto));
    }

    return mensaje;
}


// Publico:

std::vector<char> procesar_mensaje() {

    std::vector<char> mensaje_procesado;

    std::string comando, argumento;
    std::cin >> comando >> std::ws;

    if (comando != MOVE_COMANDO) {
        std::getline(std::cin, argumento);
    }

    if (comando.length() > 0) {
        mensaje_procesado =
                formatear_mensaje_cliente((char*)comando.c_str(), (char*)argumento.c_str());
    }

    return mensaje_procesado;
}
