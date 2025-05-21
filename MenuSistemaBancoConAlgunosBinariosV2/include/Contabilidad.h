//Jonathan Samuel GOnzalez Ixpata
#ifndef CONTABILIDAD_H
#define CONTABILIDAD_H

#include <iostream>
#include <fstream>
#include <string>
#include "Bitacora.h"

class Contabilidad {
public:
    void setUsuario(const string& u);//bitacora
    void menuContabilidad();               // Men� principal
    void registroNomina();                 // Opci�n 1: Registrar pago
    void desplegarRegistroSalarios();      // Opci�n 2: Generar salarios.txt
    void limpiarPantalla();                // Limpiar pantalla
    void pausar();                         // Pausar ejecuci�n


private:
    string usuario;//bitacora
    };

#endif
