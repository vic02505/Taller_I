#include "server_print_manager.h"

#include <string>

PrintManager::PrintManager(BroadcastManager& controlador_a_asginar):
        controlador_del_broadcast(controlador_a_asginar) {}

void PrintManager::mostrar_clientes_en_linea() {
    std::lock_guard<std::mutex> lck(mutex_hilos);
    std::cout << "Jugadores " << this->controlador_del_broadcast.clientes_en_linea()
              << ", esperando al resto de tus amigos..." << std::endl;
}

void PrintManager::mostrar_mensaje_de_cliente(std::vector<char> mensaje) {
    std::lock_guard<std::mutex> lck(mutex_hilos);

    std::string mensaje_a_imprimir;
    mensaje_a_imprimir = std::string(mensaje.begin(), mensaje.end());
    mensaje_a_imprimir += "\n";
    std::cout << mensaje_a_imprimir;
}
