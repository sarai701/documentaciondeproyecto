//Jonathan Samuel Gonzalez
#include "Moneda.h"      // Incluye la definici�n de la clase Moneda
#include "Bitacora.h"    // Incluye la clase Bitacora para registrar eventos
#include <iostream>      // Librer�a para entrada y salida est�ndar (cout, etc.)

using namespace std;     // Permite usar std::string, std::cout, etc., sin prefijo

Bitacora Moneda::bitacoraMoneda;  // Inicializa el objeto est�tico Bitacora para registrar cambios de moneda

string Moneda::moneda = "GTQ";    // Moneda predeterminada del sistema (quetzal)
double Moneda::tasaUSD = 0.13;    // Tasa de conversi�n de 1 quetzal a d�lares (ejemplo: 1 GTQ = 0.13 USD)
double Moneda::tasaEUR = 0.11;    // Tasa de conversi�n de 1 quetzal a euros (ejemplo: 1 GTQ = 0.11 EUR)

// Devuelve el s�mbolo correspondiente a la moneda actual
string Moneda::getSimbolo() {
    if (moneda == "USD") return "$";   // D�lar
    else if (moneda == "EUR") return "�"; // Euro
    return "Q";                         // Quetzal (por defecto)
}

// Convierte una cantidad desde la moneda actual a quetzales
double Moneda::convertirAGtq(double cantidad) {
    if (moneda == "USD") return cantidad / tasaUSD;  // Convierte de USD a GTQ
    else if (moneda == "EUR") return cantidad / tasaEUR; // Convierte de EUR a GTQ
    return cantidad;  // Si ya est� en GTQ, no se modifica
}

// Actualiza las tasas de cambio de USD y EUR respecto al quetzal
void Moneda::actualizarTasas(double usd, double eur) {
    tasaUSD = usd;    // Asigna nueva tasa para USD
    tasaEUR = eur;    // Asigna nueva tasa para EUR
    bitacoraMoneda.insertar("Admin", 4501, "Moneda", "Tasas actualizadas"); // Registra el cambio en la bit�cora
}

// Convierte una cantidad desde quetzales a la moneda seleccionada
double Moneda::convertirDesdeGtq(double cantidad) {
    if (moneda == "USD") return cantidad * tasaUSD;  // Convierte de GTQ a USD
    else if (moneda == "EUR") return cantidad * tasaEUR; // Convierte de GTQ a EUR
    return cantidad;  // Si la moneda es GTQ, no se modifica
}

// Muestra la moneda actual y su s�mbolo en consola
void Moneda::mostrarMoneda() {
    cout << "Moneda actual: " << moneda << " (" << getSimbolo() << ")\n";  // Ej: "Moneda actual: USD ($)"
}
