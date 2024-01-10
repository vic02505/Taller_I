#include "server_broadcast_manager.h"

#include <iostream>


BroadcastManager::BroadcastManager() {}


void BroadcastManager::agregar_cola_a_la_lista(Queue<std::vector<char>>& cola_a_agregar) {
    std::lock_guard<std::mutex> lock(this->mutex_hilos);
    this->lista_de_colas.push_back(cola_a_agregar);
}


void BroadcastManager::agregar_mensaje(std::vector<char> mensaje_a_agregar) {

    std::lock_guard<std::mutex> lock(this->mutex_hilos);

    for (int i = 0; i < (int)lista_de_colas.size(); i++) {
        this->lista_de_colas[i].get().try_push(mensaje_a_agregar);
    }
}


void BroadcastManager::eliminar_cola_de_la_lista(Queue<std::vector<char>>& cola_a_eliminar) {

    std::lock_guard<std::mutex> lck(mutex_hilos);

    bool se_elimino_la_cola = false;
    auto cola = this->lista_de_colas.begin();

    while (cola != this->lista_de_colas.end() && !se_elimino_la_cola) {

        if (&cola->get() == &cola_a_eliminar) {
            cola = lista_de_colas.erase(cola);
            se_elimino_la_cola = true;
        }

        ++cola;
    }
}

int BroadcastManager::clientes_en_linea() { return (int)this->lista_de_colas.size(); }
