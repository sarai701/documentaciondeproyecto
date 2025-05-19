//Boris de Le�n 9959-24-6203
// Modificado por Boris de Leon el 10 de mayo
#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>
#include "Bitacora.h" // L�nea nueva


using namespace std;

class Cliente {
private:
    vector<Cliente> clientes; // Lista de clientes en memoria
    void cargarClientes();         // Carga desde clientes.txt
    void guardarClientes();        // Guarda toda la lista en clientes.txt
    void ordenarClientes();        // Ordena alfab�ticamente por nombre

public:
    string codigo;            // C�digo del cliente
    string nombre;            // Nombre del cliente
    string telefono;          // Tel�fono del cliente
    string direccion;         // Direcci�n del cliente

    void menuCliente();            // Muestra el men� de opciones para clientes
    void crearCliente();           // Crea un nuevo cliente
    void borrarCliente();          // Borra un cliente por c�digo
    void buscarCliente();          // Busca un cliente por c�digo
    void modificarCliente();       // Modifica un cliente existente
    void desplegarClientes();      // Muestra todos los clientes

    void limpiarPantalla();        // Limpia la pantalla de la consola
    void pausar();                 // Pausa el programa hasta que se presione ENTER

        // Nuevas funciones para movimientos y pr�stamos
    void registrarMovimiento();         // Agrega un movimiento a un cliente
    void mostrarMovimientos();          // Muestra los movimientos de un cliente
    void abrirArchivoMovimientos();     // Abre el archivo de texto de movimientos

    void registrarPrestamo();           // Registra un pr�stamo activo
    void mostrarPrestamos();            // Muestra pr�stamos de un cliente
    void menuClienteCRUD();
};

#endif
