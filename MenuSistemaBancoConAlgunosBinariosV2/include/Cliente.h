#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>
#include <cstring> // Para usar strncpy
#include <fstream>
using namespace std;

class Cliente {
private:
    // Estructura fija para cliente (para archivos binarios)
    struct RegistroCliente {
        char codigo[10];
        char nombre[50];
        char telefono[15];
        char direccion[100];
    };

    // Estructura fija para movimiento
    struct RegistroMovimiento {
        char codigoCliente[10];
        char descripcion[100];
        char fecha[11];
        double monto;
    };

    // Estructura fija para pr�stamo
    struct RegistroPrestamo {
        char codigoCliente[10];
        double monto;
        char estado[10]; // "S�" o "No"
    };

    string usuario;
    vector<Cliente> clientes;

    // Atributos de instancia del cliente
    string codigo;
    string nombre;
    string telefono;
    string direccion;

    void limpiarPantalla();
    void pausar();

    void ordenarClientes();
    void guardarClientes();
    void cargarClientes();

public:
    void setUsuario(const string& u);

    void menuClienteCRUD();
    void menuCliente();

    void crearCliente();
    void borrarCliente();
    void buscarCliente();
    void modificarCliente();
    void desplegarClientes();

    void registrarMovimiento();
    void mostrarMovimientos();
    void abrirArchivoMovimientos();

    void registrarPrestamo();
    void mostrarPrestamos();
};

#endif
