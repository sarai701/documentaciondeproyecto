//Jonathan Samuel Gonzalez Ixpata
#ifndef AUDITORIA_H
#define AUDITORIA_H

#include <string>
#include <vector>
#include "Bitacora.h"

struct Auditores {
    std::string nombre;
    std::string codigo;
};

class Auditoria {
private:
    std::vector<Auditores> auditores;

public:
    void menuAuditoria();          // Men� principal
    void registrosRealizados();    // Tabla de movimientos
    void limpiarPantalla();        // Limpiar pantalla
    void pausar();                 // Pausar ejecuci�n

    // Funciones para gestionar auditores
    void submenuAuditor();         // Submen� de opciones
    void registrarAuditor();       // Registrar nuevo auditor
    void borrarAuditor();          // Borrar por c�digo
    void despliegueAuditores();    // Mostrar todos los auditores
};

#endif
