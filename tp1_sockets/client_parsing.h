#ifndef CLIENT_PARSING_H
#define CLIENT_PARSING_H

#include <vector>


std::vector<char> formatear_mensaje_cliente(char* comando, char* argumento);

/*
Procesa mensajes de la entrada estandar, devuelve los mensajes con el formato requerido por el
protocolo del cliente.
*/
std::vector<char> procesar_mensaje();

#endif
