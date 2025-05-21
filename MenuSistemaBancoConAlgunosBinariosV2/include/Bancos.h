//Jonathan Samuel Gonzalez
#ifndef BANCOS_H
#define BANCOS_H

#include <string>         // Para el uso de std::string
#include "Bitacora.h"     // Para registrar las acciones realizadas
#include "Moneda.h"       // Para manejar la configuraci�n de moneda

using namespace std;      // Evita tener que escribir std:: antes de string, cout, etc.

// Clase que gestiona la configuraci�n bancaria del sistema
class Bancos {
private:
    string usuario;//bitacora
        // Objeto de bit�cora para registrar acciones del m�dulo Bancos

    string bancoSeleccionado;           // Nombre del banco seleccionado
    string tipoCuentaSeleccionada;      // Tipo de cuenta seleccionada (Corriente o Ahorro)
    string monedaSeleccionada;          // Tipo de moneda seleccionada (GTQ, USD, EUR)

    // M�todos internos para los distintos men�s de selecci�n
    void menuSeleccionBanco();          // Men� para seleccionar banco
    void menuTipoCuenta();              // Men� para seleccionar tipo de cuenta
    void menuTipoMoneda();              // Men� para seleccionar tipo de moneda

public:
    void setUsuario(const string& u);//bitacora
    Bancos();                           // Constructor

    void menuConfiguracion();           // Men� principal de configuraci�n bancaria
    void mostrarConfiguracion();        // Muestra la configuraci�n actual al usuario

    static void limpiarPantalla();      // Limpia la consola
    static void pausar();               // Pausa la ejecuci�n esperando ENTER

    // M�todos para obtener los valores seleccionados
    string getBanco() const;            // Devuelve el banco seleccionado
    string getCuenta() const;           // Devuelve el tipo de cuenta seleccionada
    string getMoneda() const;           // Devuelve la moneda seleccionada
};

#endif
