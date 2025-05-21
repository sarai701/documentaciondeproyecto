//Boris de Le�n 9959-24-6203
//Priscila Guzm�n 9959-23-450
#include "Bitacora.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;

// Estructura para almacenar un registro de bit�cora en formato binario
struct RegistroBitacora {
    char usuario[30];
    int codigo;
    char aplicacion[30];
    char accion[50];
    char fechaHora[30];
};

// Inserta un registro en el archivo binario "bitacora.dat"
void Bitacora::insertar(const string& usuario, int codigo, const string& aplicacion, const string& accion) {
    ofstream archivo("bitacora.dat", ios::binary | ios::app);  // abrir archivo para agregar al final en modo binario
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de bit�cora.\n";
        return;
    }

    RegistroBitacora registro;
    strncpy(registro.usuario, usuario.c_str(), sizeof(registro.usuario) - 1); // copiar usuario a registro
    registro.usuario[sizeof(registro.usuario) - 1] = '\0'; // asegurar terminaci�n nula

    registro.codigo = codigo; // asignar c�digo

    strncpy(registro.aplicacion, aplicacion.c_str(), sizeof(registro.aplicacion) - 1); // copiar aplicaci�n
    registro.aplicacion[sizeof(registro.aplicacion) - 1] = '\0';

    strncpy(registro.accion, accion.c_str(), sizeof(registro.accion) - 1); // copiar acci�n
    registro.accion[sizeof(registro.accion) - 1] = '\0';

    time_t now = time(nullptr); // obtener tiempo actual
    char* fecha = ctime(&now); // convertir tiempo a cadena
    fecha[strcspn(fecha, "\n")] = '\0'; // quitar salto de l�nea
    strncpy(registro.fechaHora, fecha, sizeof(registro.fechaHora) - 1); // copiar fecha y hora
    registro.fechaHora[sizeof(registro.fechaHora) - 1] = '\0';

    archivo.write(reinterpret_cast<char*>(&registro), sizeof(registro)); // escribir registro en archivo
    archivo.close();
}

// Muestra todos los registros almacenados en "bitacora.dat"
void Bitacora::mostrar() {
    ifstream archivo("bitacora.dat", ios::binary); // abrir archivo para lectura binaria
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de bit�cora.\n";
        return;
    }

    RegistroBitacora registro;
    cout << "\n--- BIT�CORA DE USUARIO ---\n";
    while (archivo.read(reinterpret_cast<char*>(&registro), sizeof(registro))) { // leer registro a registro
        cout << "Usuario: " << registro.usuario << "\n"
             << "C�digo: " << registro.codigo << "\n"
             << "Aplicaci�n: " << registro.aplicacion << "\n"
             << "Acci�n: " << registro.accion << "\n"
             << "Fecha y Hora: " << registro.fechaHora << "\n"
             << "-----------------------------\n";
    }

    archivo.close();
}

// Men� simple para interactuar con la bit�cora
void Bitacora::menuBitacora() {
    int opcion;
    do {
        cout << "\n--- MEN� DE BIT�CORA ---\n";
        cout << "1. Desplegar bit�cora\n";
        cout << "2. Regresar al men� principal\n";
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = 0; // para repetir en caso de entrada inv�lida
        }

        switch (opcion) {
            case 1:
                mostrar(); // mostrar registros
                break;
            case 2:
                cout << "Regresando al men� principal...\n";
                break;
            default:
                cout << "Opci�n inv�lida. Intente de nuevo.\n";
        }
    } while (opcion != 2);
}
