//Jonathan Samuel Gonzalez Ixpata
#include "Auditoria.h"
#include <iostream>
#include <fstream>  // Para leer y escribir archivos
#include "Bitacora.h"

#ifdef _WIN32
#include <cstdlib>  // Para usar system("cls") en Windows
#endif

Bitacora bitacoralog4;
using namespace std;

// Funci�n para limpiar la pantalla dependiendo del sistema operativo
void Auditoria::limpiarPantalla() {
#ifdef _WIN32
    system("cls");  // En Windows
#else
    system("clear");  // En Linux o Mac
#endif
}

// Funci�n para pausar el programa hasta que el usuario presione ENTER
void Auditoria::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}


// Men� principal de Auditor�a
void Auditoria::menuAuditoria() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== MEN� DE AUDITOR�A =====";
        cout << "\n1. Gesti�n de Auditores";
        cout << "\n2. Registros Realizados";
        cout << "\n3. Volver al men� anterior";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: submenuAuditor(); break;
            case 2: registrosRealizados(); break;
            case 3: limpiarPantalla();  // Limpia pantalla antes de regresar al men� principal
                return;  // Regresa al men� anterior
            default:
                cout << "\n�Opci�n inv�lida!";
                pausar();
        }
    } while (true);
}

// Submen� para gestionar auditores
void Auditoria::submenuAuditor() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== GESTI�N DE AUDITORES =====";
        cout << "\n1. Registrar Auditor";
        cout << "\n2. Borrar Auditor";
        cout << "\n3. Desplegar Auditores";
        cout << "\n4. Volver";
        cout << "\nSeleccione: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: registrarAuditor(); break;
            case 2: borrarAuditor(); break;
            case 3: despliegueAuditores(); break;
            case 4: limpiarPantalla();  // Limpia pantalla antes de regresar al men� principal
                return;;
            default:
                cout << "\n�Opci�n inv�lida!";
                pausar();
        }
    } while (true);
}

// Registrar nuevo auditor
void Auditoria::registrarAuditor() {
    limpiarPantalla();
    Auditores a;

    cout << "\n=== REGISTRAR AUDITOR ===";
    cout << "\nNombre: ";
    getline(cin, a.nombre);
    cout << "C�digo: ";
    getline(cin, a.codigo);

    auditores.push_back(a);

    // Guardar en archivo
    ofstream archivo("auditores.txt", ios::app);
    archivo << a.nombre << "," << a.codigo << "\n";
    archivo.close();

    cout << "\n�Auditor registrado!";
    bitacoralog4.insertar("Admin", 4301, "Auditoria", "Registrar");
    pausar();
}

// Borrar auditor por c�digo
void Auditoria::borrarAuditor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== BORRAR AUDITOR ===";
    cout << "\nC�digo del auditor: ";
    getline(cin, codigo);

    vector<Auditores> nuevaLista;
    bool eliminado = false;

    for (const auto& a : auditores) {
        if (a.codigo != codigo) {
            nuevaLista.push_back(a);
        } else {
            eliminado = true;
        }
    }

    if (eliminado) {
        auditores = nuevaLista;
        ofstream archivo("auditores.txt");
        for (const auto& a : auditores) {
            archivo << a.nombre << "," << a.codigo << "\n";
        }
        archivo.close();
        cout << "\n�Auditor eliminado!";
    } else {
        cout << "\n�C�digo no encontrado!";
    }
    bitacoralog4.insertar("Admin", 4302, "Auditoria", "Borrar");

    pausar();
}

// Mostrar todos los auditores
void Auditoria::despliegueAuditores() {
    limpiarPantalla();
    ifstream archivo("auditores.txt");

    cout << "\n=== LISTA DE AUDITORES ===";
    cout << "\nNombre\t\tC�digo\n";

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(",");
        string nombre = linea.substr(0, pos);
        string codigo = linea.substr(pos + 1);

        cout << nombre << "\t\t" << codigo << "\n";
    }

    archivo.close();
     bitacoralog4.insertar("Admin", 4303, "Auditoria", "Desplegar");
    pausar();
}

// Tabla gen�rica de registros
void Auditoria::registrosRealizados() {
    limpiarPantalla();
    cout << "\n=== REGISTROS DE AUDITOR�A ===";
    cout << "\nFecha\t\tAcci�n\t\tUsuario";
    cout << "\n2023-10-01\tRevisi�n\tAuditor1";
    cout << "\n2023-10-02\tVerificaci�n\tAuditor2";
    bitacoralog4.insertar("Admin", 4304, "Auditoria", "registrosRealizados");
    pausar();
}
