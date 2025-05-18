// src/asi_command.cpp
#include "asi_command.h"

String ASI_COMMAND::get_param(String& cmd_params,
                              const char* id,
                              bool withspace) {
    // Aquí copias literalmente la implementación de COMMAND::get_param
    // para que funcione igual sin llamar a COMMAND
    static String parameter;
    parameter = "";
    int start = (strlen(id)==0 ? 0 : cmd_params.indexOf(id));
    if (start == -1) return parameter;
    int end = withspace ? -1 : cmd_params.indexOf(" ", start);
    if (end == -1) end = cmd_params.length();
    parameter = cmd_params.substring(start + strlen(id), end);
    parameter.trim();
    return parameter;
}

#ifdef AUTHENTICATION_FEATURE
bool ASI_COMMAND::isLocalPasswordValid(const char* password) {
    return COMMAND::isLocalPasswordValid(password);
}
#endif

bool ASI_COMMAND::execute_internal_command(int cmd,
                                           String cmd_params,
                                           level_authenticate_type auth_level,
                                           ESPResponseStream* espresponse) {
    switch (cmd) {
      case 100: {
        // Ejemplo: [ASI100]P=valor
        String p = get_param(cmd_params, "P=", true);
        espresponse->print("ASI100 ha recibido P=");
        return true;
      }
      case 101: {
#ifdef AUTHENTICATION_FEATURE
        if (auth_level < LEVEL_ADMIN) {
          espresponse->println("Error: nivel admin requerido");
          return true;
        }
#endif
        espresponse->println("ASI101 OK");
        return true;
      }
      // … más casos ASIXXX …
      default:
        return false;  // no era un [ASI], que lo procese COMMAND
    }
}
