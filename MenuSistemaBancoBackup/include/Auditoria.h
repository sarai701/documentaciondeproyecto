//Jonathan Samuel Gonzalez Ixpata
#ifndef AUDITORIA_H         // Verifica si AUDITORIA_H no ha sido definido
#define AUDITORIA_H         // Define AUDITORIA_H para evitar inclusiones m�ltiples

#include <string>           // Incluye soporte para cadenas de texto (std::string)
#include <vector>           // Incluye soporte para vectores din�micos (std::vector)
#include "Bitacora.h"       // Incluye la clase para registrar acciones (bit�cora)

using namespace std;        // Evita tener que escribir std:: en cada uso de string o vector

// Estructura para almacenar los datos de un auditor
struct Auditores {
    string nombre;          // Nombre del auditor
    string codigo;          // C�digo identificador del auditor
};

// Declaraci�n de la clase Auditoria
class Auditoria {
private:
    vector<Auditores> auditores; // Lista de auditores almacenados

public:
    void menuAuditoria();          // Muestra el men� principal de auditor�a
    void registrosRealizados();    // Muestra una tabla con registros de auditor�a
    void limpiarPantalla();        // Limpia la pantalla seg�n el sistema operativo
    void pausar();                 // Pausa la ejecuci�n hasta que el usuario presione ENTER

    // Funciones para la gesti�n de auditores
    void submenuAuditor();         // Muestra un submen� con opciones de gesti�n
    void registrarAuditor();       // Permite registrar un nuevo auditor
    void borrarAuditor();          // Elimina un auditor seg�n su c�digo
    void despliegueAuditores();    // Muestra en pantalla todos los auditores registrados
};

#endif  // Fin del include guard
