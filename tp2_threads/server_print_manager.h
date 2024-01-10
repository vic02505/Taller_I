#ifndef PRINT_MANAGER_H
#define PRINT_MANAGER_H

#include <iostream>
#include <mutex>
#include <vector>

#include "server_broadcast_manager.h"


class PrintManager {
private:
    std::mutex mutex_hilos;
    BroadcastManager& controlador_del_broadcast;  // SOLO USAR PARA MIRAR LOS CLIENTES EN LINEA!


public:
    explicit PrintManager(BroadcastManager& controlador_a_asignar);

    void mostrar_clientes_en_linea();

    void mostrar_mensaje_de_cliente(std::vector<char> mensaje);
};


#endif
