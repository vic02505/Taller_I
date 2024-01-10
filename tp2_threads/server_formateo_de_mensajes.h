#ifndef SERVER_FORMATEO_DE_MENSAJES
#define SERVER_FORMATEO_DE_MENSAJES

#include <vector>

// Formateo de los mensajes que son enviados a los clientes.

class FormateoDeMensajes {
public:
    /*
    Formatea la cantidad de jugadores que se encuentran conectados en el
    servidor.
    */
    std::vector<char> formatear_cantidad_de_jugadores(int cantidad_de_jugadores);

    /*
    Formate un mensaje de chat enviado al servidor.
    */
    std::vector<char> formatear_mensaje_de_chat(std::vector<char> mensaje_de_chat);
};


#endif
