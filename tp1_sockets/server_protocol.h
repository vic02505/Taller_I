#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "common_socket.h"
#include "server_logica_de_juego.h"
#include "server_manejo_de_escenarios.h"

class ServerProtocol {
private:
    Socket socket_aceptador;
    Socket socket_servidor;
    bool estado_socket;

    ManejoDeEscenarios manager_de_escenarios;
    bool se_selecciono_escenario;

    LogicaDeJuego manager_de_juego;

    void enviar_respuesta_a_cliente(int tipo_de_comando);

    int procesar_seleccion_de_escenario();

    void procesar_cambio_de_direccion();

    void procesar_movimiento();

    void procesar_salto();

    void procesar_mensaje_cliente();


public:
    /*
    Constructor de clase. Se debe especificar el puerto en el que el servidor debe aceptar una
    comunicacion, tambien debe especificarse el path al archivo donde se encuentran los escenarios
    del juego. Una vez llamado al constructor, el protocolo quedara en espera hasta que haya
    alguienq desee establecer una conexion con el.
    */
    explicit ServerProtocol(char* puerto, char* path_file_escenarios);

    /*
    Da inicio al protolo. Esto es, a recibir mensajes de un cliente hasta que este finalice (el
    cliente) la conexion.
    */
    void iniciar_protocolo();
};
#endif
