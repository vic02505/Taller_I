#include "server_aceptador.h"

#include <utility>

#include "server_cliente.h"


// Metodos privados:

void ServerAceptador::enviar_cantidad_de_jugadores() {

    int cantidad_de_jugadores = this->controlador_del_broadcast.clientes_en_linea();
    std::vector<char> mensaje_a_enviar =
            this->formateador.formatear_cantidad_de_jugadores(cantidad_de_jugadores);
    this->controlador_del_broadcast.agregar_mensaje(mensaje_a_enviar);
}


void ServerAceptador::limpiar_clientes_desconectados() {

    auto cliente = this->lista_de_clientes.begin();

    while (cliente != this->lista_de_clientes.end()) {

        Thread* cliente_a_chequear = *cliente;

        if (!cliente_a_chequear->is_alive()) {
            cliente_a_chequear->join();
            delete cliente_a_chequear;
            cliente = this->lista_de_clientes.erase(cliente);
        } else {
            ++cliente;
        }
    }
}


void ServerAceptador::limpiar_clientes_de_la_lista() {

    auto cliente = this->lista_de_clientes.begin();

    while (cliente != this->lista_de_clientes.end()) {

        Thread* cliente_a_eliminar = *cliente;
        cliente_a_eliminar->join();
        delete cliente_a_eliminar;
        ++cliente;
    }

    this->lista_de_clientes.clear();
}


// Metodos publicos y constructores:

ServerAceptador::ServerAceptador(char* puerto):
        socket_aceptador(puerto),
        controlador_del_broadcast(),
        controlador_de_impresion(controlador_del_broadcast) {}


void ServerAceptador::dejar_de_aceptar_clientes() {
    this->se_siguen_aceptando_clientes = false;
    this->socket_aceptador.shutdown(2);  // SHUT_RDWR
    this->socket_aceptador.close();
}


void ServerAceptador::run() {

    try {

        while (this->se_siguen_aceptando_clientes) {
            this->enviar_cantidad_de_jugadores();
            Socket socket_comunicador = socket_aceptador.accept();
            Thread* cliente = new Cliente(std::move(socket_comunicador), controlador_del_broadcast,
                                          controlador_de_impresion);
            this->controlador_de_impresion.mostrar_clientes_en_linea();
            this->lista_de_clientes.push_back(cliente);
            cliente->start();
            this->limpiar_clientes_desconectados();
        }

    } catch (const std::exception& e) {
        this->limpiar_clientes_de_la_lista();
    }
}
