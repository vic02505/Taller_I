#ifndef CLIENT_PROCESAMIENTO_DE_MENSAJES_H
#define CLIENT_PROCESAMIENTO_DE_MENSAJE_H

#include <string>
#include <vector>

class ProcesadorDeMensajes {
private:
    /*
    Recibe un argumento y comando obtenidos de la entrada estandar, los procesa, generando
    y devolviendo un vector de chars con el mensaje formateado correspondiente a la
    entrada estandar obtenida.
    */
    std::vector<char> formatear_mensaje(const std::string& comando, const std::string& argumento);


    /*
    Procesa un mensaje escrito por el cliente via stdin. La funcion procesa un unico
    mensaje, obteniendo como salida un vector de chars formateado al formato definido
    en el enunciado.

    NOTA IMPORTANTE: Esta funcion no maneja errores referentes al formato de mensajes
    esperado vs como envia los mensajes del cliente. En caso de no cumplir con  el formato
    esperado, se enviara un vector de char con size de 1 (byte), cuyo unico valor es un cero.
    */
    std::vector<char> procesar_mensaje(const std::string& comando, const std::string& argumento);

public:
    std::vector<char> operator()(const std::string& comando, const std::string& argumento);
};

#endif
