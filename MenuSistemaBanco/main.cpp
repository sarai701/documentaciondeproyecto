//Programado por Priscila Sarai Guzm�n Calgua 9959-23-450
#include <iostream>
#include <fstream>
#include <string>
#include "Empleados.h"
#include "Cliente.h"
#include "Proveedores.h"
#include "Contabilidad.h"
#include "Auditoria.h"
#include "Usuario.h"
#include <conio.h>
#include "Nominas.h"
#include "Bitacora.h"
#include "Bancos.h"
#include "Moneda.h"
#include <limits>
using namespace std;
// Funci�n para pausar el sistema hasta que el usuario presione ENTER
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
// Funci�n para limpiar errores de entrada en caso de que el usuario ingrese datos no v�lidos
void limpiarBufferEntrada() {
    cin.clear();// Limpia errores de entrada
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora lo que quede en el buffer
}

void realizarBackup() {
    // Crear directorio si no existe (Windows)
    system("mkdir backup 2> nul");

    // Lista de archivos a respaldar
    const char* archivos[] = {
        "clientes.txt", "proveedores.txt", "empleados.txt",
        "movimientos.txt", "prestamos.txt", "bitacora.txt",
        "auditores.txt", "pagos.txt", "salarios.txt"
    };

    // Copiar cada archivo sobrescribiendo el anterior
    for (const char* archivo : archivos) {
        string comando = "copy /Y " + string(archivo) + // /Y para sobrescribir en Windows
                        " backup\\" + string(archivo) + ".bak > nul";
        system(comando.c_str());
    }
}

void menuArchivo(const string& usuario, Bitacora& bitacora) {
    Usuario::limpiarPantalla();
    int opcion;
    do {
        cout << "\n--- MEN� ARCHIVO ---";
        cout << "\n1. Backup";
        cout << "\n2. Volver al Men� General";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        // Validaci�n de entrada
        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "\nEntrada inv�lida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
            case 1:
                realizarBackup();
                cout << "\nBackup realizado exitosamente!\n";
                bitacora.insertar(usuario, 4905, "Sistema", "Backup realizado");
                break;
            case 2:
                return;
            default:
                cout << "\nOpci�n inv�lida.\n";
                break;
        }
        pausar();
        Usuario::limpiarPantalla();
    } while (true);
}
// Muestra el men� Cat�logos, que permite acceder a diferentes m�dulos del sistema
void menuCatalogos(const string& usuario, Bitacora& bitacora, Empleados& empleados, Cliente& cliente, Proveedor& proveedor, Auditoria& auditoria, Nominas& nominas) {
    Usuario::limpiarPantalla();
    int opcion;
    do {
        cout << "\n--- MEN� CAT�LOGOS ---";
        cout << "\n1. N�minas";
        cout << "\n2. Cliente";
        cout << "\n3. Empleados";
        cout << "\n4. Auditor�a";
        cout << "\n5. Proveedores";
        cout << "\n6. Volver al Men� General";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "\nEntrada inv�lida. Intente de nuevo.\n";
            continue;
        }
// Cada caso accede a un m�dulo del sistema y registra la acci�n en la bit�cora
        switch (opcion) {
            case 1:
                nominas.menuNominas();
                bitacora.insertar(usuario, 4000, "Nominas", "Ingres� al m�dulo de N�minas");
                break;
            case 2:
                cliente.menuClienteCRUD();
                bitacora.insertar(usuario, 4100, "Clientes", "Ingres� al m�dulo de Clientes (CRUD)");
                break;
            case 3:
                empleados.menuEmpleados();
                bitacora.insertar(usuario, 4001, "Empleados", "Ingres� al m�dulo de Empleados");
                break;
            case 4:
                auditoria.menuAuditoria();
                bitacora.insertar(usuario, 4400, "Auditor�a", "Ingres� al m�dulo de Auditor�a");
                break;
            case 5:
                proveedor.menuProveedor();
                bitacora.insertar(usuario, 4200, "Proveedores", "Ingres� al m�dulo de Proveedores");
                break;
            case 6:
                return;
            default:
                cout << "\nOpci�n inv�lida.\n";
                break;
        }
        pausar();
        Usuario::limpiarPantalla();
    } while (true);
}
// Muestra el men� Procesos, que incluye movimientos, pr�stamos, contabilidad y configuraci�n bancaria
void menuProcesos(const string& usuario, Bitacora& bitacora, Cliente& cliente, Contabilidad& contabilidad) {
    Usuario::limpiarPantalla();
    Bancos bancos;
    Moneda moneda;
// Configuraci�n bancaria al inicio del men� Procesos
    cout << "\nSeleccione configuraci�n bancaria y moneda para Procesos:\n";
    bancos.menuConfiguracion();
    bitacora.insertar(usuario, 4300, "Procesos", "Configuraci�n bancaria y moneda seleccionada");

    int opcionProcesos;
    do {
        cout << "\n--- MEN� PROCESOS ---" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Contabilidad" << endl;
        cout << "3. Mostrar configuraci�n bancaria" << endl;
        cout << "4. Volver al Men� General" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcionProcesos;
        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "Entrada inv�lida. Intente de nuevo.\n";
            continue;
        }
// Acciones para cada opci�n de clientes
        switch (opcionProcesos) {
            case 1: {
                Usuario::limpiarPantalla();
                int opcionClientes;
                do {
                    cout << "\n--- PROCESOS - CLIENTES ---" << endl;
                    cout << "1. Registrar movimiento" << endl;
                    cout << "2. Mostrar movimientos" << endl;
                    cout << "3. Abrir archivo movimientos.txt" << endl;
                    cout << "4. Registrar pr�stamo" << endl;
                    cout << "5. Mostrar pr�stamos" << endl;
                    cout << "6. Volver" << endl;
                    cout << "Seleccione una opci�n: ";
                    cin >> opcionClientes;
                    if(cin.fail()) {
                        limpiarBufferEntrada();
                        cout << "Entrada inv�lida. Intente de nuevo.\n";
                        continue;
                    }

                    switch (opcionClientes) {
                        case 1:
                            cliente.registrarMovimiento();
                            bitacora.insertar(usuario, 4100, "Clientes", "Movimiento registrado");
                            break;
                        case 2:
                            cliente.mostrarMovimientos();
                            bitacora.insertar(usuario, 4101, "Clientes", "Movimientos mostrados");
                            break;
                        case 3:
                            cliente.abrirArchivoMovimientos();
                            bitacora.insertar(usuario, 4102, "Clientes", "Mostrar movimientos");
                            break;
                        case 4:
                            cliente.registrarPrestamo();
                            bitacora.insertar(usuario, 4103, "Clientes", "Pr�stamo registrado");
                            break;
                        case 5:
                            cliente.mostrarPrestamos();
                            bitacora.insertar(usuario, 4104, "Clientes", "Pr�stamos mostrados");
                            break;
                        case 6:
                            break;
                        default:
                            cout << "Opci�n no v�lida.\n";
                    }
                    pausar();
                    Usuario::limpiarPantalla();
                } while (opcionClientes != 6);
                break;
            }
            case 2:
                contabilidad.menuContabilidad();
                bitacora.insertar(usuario, 4301, "Contabilidad", "Ingres� al m�dulo Contabilidad");
                pausar();
                Usuario::limpiarPantalla();
                break;
            case 3:
                cout << "\n--- Configuraci�n bancaria actual ---\n";
                bancos.mostrarConfiguracion();
                moneda.mostrarMoneda();
                bitacora.insertar(usuario, 4302, "Procesos", "Mostr� configuraci�n bancaria y moneda");
                pausar();
                Usuario::limpiarPantalla();
                break;
            case 4:
                cout << "Volviendo al men� general...\n";
                break;
            default:
                cout << "Opci�n no v�lida.\n";
        }
    } while (opcionProcesos != 4);
}
// Muestra el men� Informes
void menuInformes(const string& usuario, Bitacora& bitacora) {
    Usuario::limpiarPantalla();
    int opcionInformes;
    do {
        cout << "\n--- MEN� INFORMES ---" << endl;
        cout << "1. Bit�cora" << endl;
        cout << "2. Volver al men� principal" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcionInformes;
        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "Entrada inv�lida. Intente de nuevo.\n";
            continue;
        }

        switch (opcionInformes) {
            case 1:
                bitacora.mostrar();// Muestra las acciones realizadas
                bitacora.insertar(usuario, 4990, "Informes", "Bit�cora mostrada");
                break;
            case 2:
                cout << "Volviendo al men� principal...\n";
                break;
            default:
                cout << "Opci�n no v�lida.\n";
        }
        pausar();
        Usuario::limpiarPantalla();
    } while (opcionInformes != 2);
}
// Men� principal del sistema, se accede luego de iniciar sesi�n
void menuGeneral(const string& usuario) {
     // Objetos que usar�n los men�s
    Bitacora bitacora;
    Empleados empleados;
    Cliente cliente;
    Proveedor proveedor;
    Auditoria auditoria;
    Nominas nominas;
    Contabilidad contabilidad;

    int opcion;
    do {
        cout << "\n======= MEN� GENERAL =======";
        cout << "\n1. Archivo";
        cout << "\n2. Cat�logos";
        cout << "\n3. Procesos";
        cout << "\n4. Informes";
        cout << "\n5. Cerrar Sesi�n";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "\nEntrada inv�lida. Intente de nuevo.\n";
            continue;
        }
 // Acciones seg�n la opci�n seleccionada
        switch (opcion) {
            case 1:
                menuArchivo(usuario, bitacora);
                break;
            case 2:
                menuCatalogos(usuario, bitacora, empleados, cliente, proveedor, auditoria, nominas);
                break;
            case 3:
                menuProcesos(usuario, bitacora, cliente, contabilidad);
                break;
            case 4:
                menuInformes(usuario, bitacora);
                break;
            case 5:
                bitacora.insertar(usuario, 4901, "Sistema", "Usuario cerr� sesi�n");
                cout << "\nCerrando sesi�n...\n";
                return;
            default:
                cout << "\nOpci�n inv�lida.\n";
                bitacora.insertar(usuario, 4902, "Sistema", "Opci�n inv�lida en Men� General");
                break;
        }
        pausar();
        Usuario::limpiarPantalla();
    } while (true);
}

int main() {
    Bitacora bitacoraGlobal;// Bit�cora general para registrar

    while (true) {
        string usuarioLogueado;//Variable para guardar el nombre del usuario
        // Llama al men� de autenticaci�n y verifica si el usuario se autentic� correctamente
        if (Usuario::menuAutenticacion(usuarioLogueado)) {
            bitacoraGlobal.insertar(usuarioLogueado, 4900, "Sistema", "Inicio de sesi�n exitoso");
            menuGeneral(usuarioLogueado);
        } else {
            cout << "\nAutenticaci�n fallida.\n";
            bitacoraGlobal.insertar("Desconocido", 4902, "Sistema", "Fall� intento de login");
            break;
        }
    }
    return 0;
}


