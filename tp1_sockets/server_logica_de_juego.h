#ifndef SERVER_LOGICA_DE_JUEGO_H
#define SERVER_LOGICA_DE_JUEGO_H

#include <map>
#include <string>
#include <utility>

#include "server_manejo_de_escenarios.h"


class LogicaDeJuego {

    // Atributos:
public:
    int x, y;  // posicion del gusano, es inicializada una vez se llama al constructor.

private:
    std::map<std::pair<int, int>, std::string> escenario;
    int ancho_escenario, altura_escenario;
    int direccion_gusano;  // el gusano comienza mirando a la izquierda por defecto.

    // Metodos:

private:
    void simular_gravedad();

    void mostrar_escenario();

    void cargar_posicion_inicial();

    bool es_posicion_valida(int x_final, int y_final);

    bool es_salto_hacia_adelante_valido(int direccion_de_salto);

    bool es_salto_hacia_atras_valido(int direccion_de_salto);

    int realizar_salto_hacia_adelante();

    int realizar_salto_hacia_atras();

    void cambiar_direccion_gusano(int direccion_a_escoger);

    int mover_gusano();

    int realizar_salto(int tipo_de_salto);

public:
    /*
    Muestra el estado del juego; Las posiciones en las que se encuentra el gusano.
    */
    void mostrar_estado();

    /*
    Constructor de clase. Crea una manejador para la logica del juego. Al crearse, el
    juego se econtrara en un estado invalido.
    */
    LogicaDeJuego();

    /*
    Da inicio a un juego indicandole el mapa en el que se desea jugar, y las dimensiones del mismo.
    */
    void iniciar_juego(std::map<std::pair<int, int>, std::string> escenario_a_seleccionar, int alto,
                       int ancho);

    /*
    Realiza una accion del gusano. tipos de accion debe ser algunas de las acciones
    de juegos descritas en el apartado de acciones de juego del modulo
    "server_acciones_de_juego.h".
    */
    void realizar_accion(int tipo_de_accion);
};

#endif
