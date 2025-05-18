// src/asi_command.h


#include "espcom.h"    // para ESPResponseStream
#include <Arduino.h>   // para String
#include "command.h"   // para level_authenticate_type

class ASI_COMMAND {
public:
    // Ejecuta un comando ASI; devuelve true si lo manejó
    static bool execute_internal_command(int cmd,
                                         String cmd_params,
                                         level_authenticate_type auth_level,
                                         ESPResponseStream* espresponse);

    // Copia/adapta COMMAND::get_param :contentReference[oaicite:0]{index=0}:contentReference[oaicite:1]{index=1}
    static String get_param(String& cmd_params,
                            const char* id,
                            bool withspace = false);

#ifdef AUTHENTICATION_FEATURE
    // (Opcional) validar contraseña local igual a COMMAND::isLocalPasswordValid :contentReference[oaicite:2]{index=2}:contentReference[oaicite:3]{index=3}
    static bool isLocalPasswordValid(const char* password);
#endif
};

#endif // ASI_COMMAND_H
