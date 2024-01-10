#ifndef SERVER_BROADCAST_MANAGER_H
#define SERVER_BROADCAST_MANAGER_H

/*
El server junto a todos sus hilos se comporta como un broadcaster. Esta clase se encarga
de proporcionar metodos para mantener actualizadas las colas de mensajes de cada cliente, y los
mensajes que contienen las mismas de forma atomica (es un monitor).
*/

#include <mutex>
#include <string>
#include <vector>

#include "common_queue.h"

class BroadcastManager {
private:
    std::vector<std::reference_wrapper<Queue<std::vector<char>>>> lista_de_colas;
    std::mutex mutex_hilos;

public:
    /*
    Constructor.
    */
    BroadcastManager();

    /*
    Agrega una unica cola a la lista de colas.
    */
    void agregar_cola_a_la_lista(Queue<std::vector<char>>& cola_a_agregar);

    /*
    Agrega un mensaje a cada una de las colas de la lista.
    */
    void agregar_mensaje(std::vector<char> mensaje_a_agregar);

    /*
    Elimina una cola de la lista.
    */
    void eliminar_cola_de_la_lista(Queue<std::vector<char>>& cola_a_eliminar);

    /*
    Devuelve cuantos usuarios hay en linea (cuantas colas hay en la lista).
    */
    int clientes_en_linea();
};

#endif
