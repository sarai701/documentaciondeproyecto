//Jonathan Samuel Gonzalez Ixpata
#include "Auditoria.h"
#include <iostream>       // Para entrada y salida est�ndar
#include <fstream>        // Para leer y escribir archivos
#include "Bitacora.h"     // Para registrar acciones en la bit�cora

#ifdef _WIN32
#include <cstdlib>        // Para usar system("cls") en Windows
#endif

Bitacora bitacoralogAuditoria;    // Objeto global para registrar acciones en la bit�cora
using namespace std;

// Funci�n para limpiar la pantalla dependiendo del sistema operativo
void Auditoria::limpiarPantalla() {
#ifdef _WIN32
    system("cls");        // Limpia la pantalla en Windows
#else
    system("clear");      // Limpia la pantalla en Linux o Mac
#endif
}

// Funci�n para pausar el programa hasta que el usuario presione ENTER
void Auditoria::pausar() {
    cout << "\nPresione ENTER para continuar...";  // Mensaje para el usuario
    cin.ignore();        // Ignora entrada previa
    cin.get();           // Espera a que el usuario presione ENTER
}

void Auditoria::setUsuario(const string& u) {
    usuario = u;
}

// Men� principal de Auditor�a
void Auditoria::menuAuditoria() {
    int opcion;          // Variable para almacenar la opci�n del usuario
    do {
        limpiarPantalla();    // Limpia pantalla antes de mostrar el men�
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== MEN� DE AUDITOR�A =====";
        cout << "\n1. Gesti�n de Auditores";
        cout << "\n2. Registros Realizados";
        cout << "\n3. Volver al men� anterior";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;        // Lee la opci�n del usuario
        cin.ignore();         // Limpia el buffer

        switch (opcion) {
            case 1: submenuAuditor(); break;             // Ir al submen� de auditores
            case 2: registrosRealizados(); break;        // Mostrar registros de auditor�a
            case 3: limpiarPantalla(); return;           // Volver al men� anterior
            default:
                cout << "\n�Opci�n inv�lida!";           // Mensaje de error
                pausar();                                // Pausar para que el usuario vea el mensaje
        }
    } while (true);      // Bucle infinito hasta que se seleccione la opci�n 3
}

// Submen� para gestionar auditores
void Auditoria::submenuAuditor() {
    int opcion;          // Variable para almacenar la opci�n del usuario
    do {
        limpiarPantalla();    // Limpia pantalla antes de mostrar el submen�
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== GESTI�N DE AUDITORES =====";
        cout << "\n1. Registrar Auditor";
        cout << "\n2. Borrar Auditor";
        cout << "\n3. Desplegar Auditores";
        cout << "\n4. Volver";
        cout << "\nSeleccione: ";
        cin >> opcion;        // Lee la opci�n del usuario
        cin.ignore();         // Limpia el buffer

        switch (opcion) {
            case 1: registrarAuditor(); break;           // Registrar un nuevo auditor
            case 2: borrarAuditor(); break;              // Eliminar un auditor existente
            case 3: despliegueAuditores(); break;        // Mostrar la lista de auditores
            case 4: limpiarPantalla(); return;           // Volver al men� anterior
            default:
                cout << "\n�Opci�n inv�lida!";           // Mensaje de error
                pausar();                                // Pausar para que el usuario vea el mensaje
        }
    } while (true);      // Bucle infinito hasta que se seleccione la opci�n 4
}

// Registrar nuevo auditor
void Auditoria::registrarAuditor() {
    limpiarPantalla();           // Limpia la pantalla
    Auditores a;                 // Crear objeto auditor

    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== REGISTRAR AUDITOR ===";
    cout << "\nNombre: ";
    getline(cin, a.nombre);      // Leer nombre del auditor
    cout << "C�digo: ";
    getline(cin, a.codigo);      // Leer c�digo del auditor

    auditores.push_back(a);      // Agregar auditor al vector

    ofstream archivo("auditores.txt", ios::app);   // Abrir archivo para agregar datos
    archivo << a.nombre << "," << a.codigo << "\n"; // Escribir datos en el archivo
    archivo.close();              // Cerrar archivo

    cout << "\n�Auditor registrado!";              // Confirmaci�n
    bitacoralogAuditoria.insertar(usuario, 4301, "Auditoria", "Registrar"); // Registrar acci�n en bit�cora
    pausar();                      // Esperar al usuario
}

// Borrar auditor por c�digo
void Auditoria::borrarAuditor() {
    limpiarPantalla();            // Limpia la pantalla
    string codigo;                // Variable para almacenar el c�digo
    cout << "\n=== BORRAR AUDITOR ===";
    cout << "\nC�digo del auditor: ";
    getline(cin, codigo);         // Leer c�digo del auditor

    vector<Auditores> nuevaLista; // Lista temporal para los que no ser�n eliminados
    bool eliminado = false;       // Bandera para saber si se elimin� un auditor

    for (const auto& a : auditores) {
        if (a.codigo != codigo) {
            nuevaLista.push_back(a);  // Mantener auditores que no coincidan
        } else {
            eliminado = true;         // Se encontr� y elimin� el auditor
        }
    }

    if (eliminado) {
        auditores = nuevaLista;      // Reemplazar lista original con la nueva
        ofstream archivo("auditores.txt");  // Reescribir el archivo completo
        for (const auto& a : auditores) {
            archivo << a.nombre << "," << a.codigo << "\n"; // Escribir auditor no eliminado
        }
        archivo.close();             // Cerrar archivo
        cout << "\n�Auditor eliminado!";    // Confirmaci�n
    } else {
        cout << "\n�C�digo no encontrado!"; // Mensaje si no se encuentra el c�digo
    }

    bitacoralogAuditoria.insertar(usuario, 4302, "Auditoria", "Borrar"); // Registrar acci�n en bit�cora
    pausar();                    // Esperar al usuario
}

// Mostrar todos los auditores
void Auditoria::despliegueAuditores() {
    limpiarPantalla();           // Limpia la pantalla
    ifstream archivo("auditores.txt");   // Abrir archivo de auditores

    cout << "\n=== LISTA DE AUDITORES ===";
    cout << "\nNombre\t\tC�digo\n";

    string linea;                // Variable para leer l�nea del archivo
    while (getline(archivo, linea)) {
        size_t pos = linea.find(",");       // Buscar posici�n de la coma
        string nombre = linea.substr(0, pos);  // Extraer nombre
        string codigo = linea.substr(pos + 1); // Extraer c�digo

        cout << nombre << "\t\t" << codigo << "\n";  // Mostrar datos
    }

    archivo.close();             // Cerrar archivo
    bitacoralogAuditoria.insertar(usuario, 4303, "Auditoria", "Desplegar"); // Registrar acci�n en bit�cora
    pausar();                    // Esperar al usuario
}

// Tabla gen�rica de registros
void Auditoria::registrosRealizados() {
    limpiarPantalla();           // Limpia la pantalla
    cout << "\n=== REGISTROS DE AUDITOR�A ===";
    cout << "\nFecha\t\tAcci�n\t\tUsuario";
    cout << "\n2023-10-01\tRevisi�n\tAuditor1";       // Registro de ejemplo
    cout << "\n2023-10-02\tVerificaci�n\tAuditor2";    // Registro de ejemplo
    bitacoralogAuditoria.insertar(usuario, 4304, "Auditoria", "registrosRealizados"); // Registrar acci�n en bit�cora
    pausar();                    // Esperar al usuario
}
