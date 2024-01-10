#include <iostream>
#include <string>

#include "server_protocol.h"

int main(int argc, char* argv[]) {

    if (argc < 3) {
        return -1;
    }

    ServerProtocol protocolo_de_servidor(argv[1], argv[2]);

    protocolo_de_servidor.iniciar_protocolo();


    return 0;
}
