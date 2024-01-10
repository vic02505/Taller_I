#include "server_logica_de_juego.h"

#include <iostream>
#include <string>

#include "server_acciones_de_juego.h"

#define GUSANO "G"
#define OBSTACULO "X"
#define ESPACIO_LIBRE " "

#define ERROR -1
#define OK 0


// metodos privados:

/*
Se encarga de llevar el gusano al suelo si este se encuentra en el aire.
*/
void LogicaDeJuego::simular_gravedad() {

    while (this->escenario[std::make_pair(this->x + 1, this->y)] != OBSTACULO) {
        this->x += 1;
    }
}


/*
Busca en el mapa la posicion en la que se encuentra en el gusano y se la asigna a los atributos x e
y. Advertencia: Solo usar este metodo durante la inicializacion del juego.
*/
void LogicaDeJuego::cargar_posicion_inicial() {

    std::string elemento_de_escenario;
    bool encontrado = false;

    for (int i = 0; i < this->altura_escenario && !encontrado; i++) {

        for (int j = 0; j < this->ancho_escenario && !encontrado; j++) {

            elemento_de_escenario = this->escenario[std::make_pair(i, j)];

            if (elemento_de_escenario == GUSANO) {
                this->x = i;
                this->y = j;
                encontrado = true;
            }
        }
    }
}


/*
Verifica si la posicion que es pasada por parametros es valida, esto es, si no es un obstaculo.
Recomendacion: Usarla como verificacion previa a una accion que implique mover al gusano de lugar,
para esto debe saberse a priori hacia donde va a ser movido el gusano.
*/
bool LogicaDeJuego::es_posicion_valida(int x_final, int y_final) {

    return this->escenario[std::make_pair(x_final, y_final)] != OBSTACULO;
}


/*
Realiza un salto hacia adelante desde la posicion en la que se encuentra el gusano.
Advertencnia: Este metodo solo puede ser usado por el metodo realizar_salto.

El metodo devuelve un codigo de error o de exito dependiendo de si la accion
fue exitosa o no.
*/
int LogicaDeJuego::realizar_salto_hacia_adelante() {

    switch (this->direccion_gusano) {
        case IZQUIERDA:

            if (this->escenario[std::make_pair(this->x - 1, this->y)] == OBSTACULO) {
                return ERROR;
            }

            this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
            this->x -= 1;
            this->escenario[std::make_pair(this->x, this->y)] = GUSANO;

            for (int i = 1; i <= 2; i++) {

                if (this->escenario[std::make_pair(this->x, this->y - 1)] != OBSTACULO) {
                    this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
                    this->y -= 1;
                    this->escenario[std::make_pair(this->x, this->y)] = GUSANO;
                }
            }

            simular_gravedad();

            break;

        case DERECHA:

            if (this->escenario[std::make_pair(this->x - 1, this->y)] == OBSTACULO) {
                return ERROR;
            }

            this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
            this->x -= 1;
            this->escenario[std::make_pair(this->x, this->y)] = GUSANO;

            for (int i = 1; i <= 2; i++) {

                if (this->escenario[std::make_pair(this->x, this->y + 1)] != OBSTACULO) {
                    this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
                    this->y += 1;
                    this->escenario[std::make_pair(this->x, this->y)] = GUSANO;
                }
            }

            simular_gravedad();

            break;
    }

    return OK;
}


/*
Realiza un salto hacia atras desde la posicion en la que se encuentra el gusano.
Advertencnia: Este metodo solo puede ser usado por el metodo realizar_salto.

El metodo devuelve un codigo de error o de exito dependiendo de si la accion
fue exitosa o no.
*/
int LogicaDeJuego::realizar_salto_hacia_atras() {

    switch (this->direccion_gusano) {
        case IZQUIERDA:

            if (this->escenario[std::make_pair(this->x - 1, this->y)] == OBSTACULO ||
                this->escenario[std::make_pair(this->x - 2, this->y)] == OBSTACULO) {
                return ERROR;
            }

            this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
            this->x -= 2;
            this->escenario[std::make_pair(this->x, this->y)] = GUSANO;

            if (this->escenario[std::make_pair(this->x, this->y + 1)] != OBSTACULO) {
                this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
                this->y += 1;
                this->escenario[std::make_pair(this->x, this->y)] = GUSANO;
            }

            simular_gravedad();


            break;

        case DERECHA:

            if (this->escenario[std::make_pair(this->x - 1, this->y)] == OBSTACULO ||
                this->escenario[std::make_pair(this->x - 2, this->y)] == OBSTACULO) {
                return ERROR;
            }

            this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
            this->x -= 2;
            this->escenario[std::make_pair(this->x, this->y)] = GUSANO;


            if (this->escenario[std::make_pair(this->x, this->y - 1)] != OBSTACULO) {
                this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
                this->y -= 1;
                this->escenario[std::make_pair(this->x, this->y)] = GUSANO;
            }

            simular_gravedad();

            break;
    }

    return OK;
}


/*
Cambia la direccion en la que mira el gusano a la indicada por el parametro
"direccion_a_escoger". Los valores que puede tomar el parametro son indicados en el apartado
direccion de giro del modulo "server_acciones_de_juego.h"
*/
void LogicaDeJuego::cambiar_direccion_gusano(int direccion_a_escoger) {
    this->direccion_gusano = direccion_a_escoger;
}


/*
Mueve al gusano una posiciones hacia la direccion en la que se encuentre mirando
el gusano. En caso de que no sea posible mover al gusano se devuelve un codigo de error.
*/
int LogicaDeJuego::mover_gusano() {

    switch (this->direccion_gusano) {
        case IZQUIERDA:

            if (es_posicion_valida(this->x, this->y - 1)) {
                this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
                this->y--;
                simular_gravedad();
                this->escenario[std::make_pair(this->x, this->y)] = GUSANO;
            } else {
                return ERROR;
            }

            break;

        case DERECHA:

            if (es_posicion_valida(this->x, this->y + 1)) {
                this->escenario[std::make_pair(this->x, this->y)] = ESPACIO_LIBRE;
                this->y++;
                simular_gravedad();
                this->escenario[std::make_pair(this->x, this->y)] = GUSANO;
            } else {
                return ERROR;
            }

            break;
    }

    return OK;
}


/*
Realiza un salto. El parametro "tipo_de_salto" indica la direccion en
la que se realiza el salto. Los valores que puede tomar el parametro
son descritos en el apartado de direcciones de salto del modulo
"server_acciones_de_juego.h"

En caso de que no sea posible realizar el salto se devuelve un codigo de error.
*/
int LogicaDeJuego::realizar_salto(int tipo_de_salto) {

    int estado_salto = OK;

    switch (tipo_de_salto) {
        case ADELANTE:
            estado_salto = realizar_salto_hacia_adelante();
            break;

        case ATRAS:
            estado_salto = realizar_salto_hacia_atras();
            break;
    }

    return estado_salto;
}


// metodos publicos:


void LogicaDeJuego::mostrar_estado() { std::cout << this->y << " " << this->x << std::endl; }

LogicaDeJuego::LogicaDeJuego() {
    this->x = -1;
    this->y = -1;
    this->ancho_escenario = -1;
    this->altura_escenario = -1;
    this->direccion_gusano = -1;
}

void LogicaDeJuego::iniciar_juego(
        const std::map<std::pair<int, int>, std::string> escenario_a_seleccionar, int alto,
        int ancho) {
    this->escenario = escenario_a_seleccionar;
    this->direccion_gusano = IZQUIERDA;
    this->altura_escenario = alto;
    this->ancho_escenario = ancho;
    cargar_posicion_inicial();
}


void LogicaDeJuego::realizar_accion(int tipo_de_accion) {

    switch (tipo_de_accion) {
        case GIRAR_A_LA_IZQUIERDA:
            this->cambiar_direccion_gusano(IZQUIERDA);
            break;

        case GIRAR_A_LA_DERECHA:
            this->cambiar_direccion_gusano(DERECHA);
            break;

        case MOVERSE:
            this->mover_gusano();
            break;

        case SALTAR_HACIA_ADELANTE:
            this->realizar_salto(ADELANTE);
            break;

        case SALTAR_HACIA_ATRAS:
            this->realizar_salto(ATRAS);
            break;
    }
}
