#include "client_logica_de_juego.h"

int main(int argc, char* argv[]) {

    if (argc < 3) {
        return -1;
    }

    iniciar_juego(argv[1], argv[2]);

    return 0;
}
