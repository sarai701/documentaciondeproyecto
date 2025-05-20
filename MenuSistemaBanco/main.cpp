//Programado por Priscila Sarai Guzm�n Calgua 9959-23-450
#include <iostream>      // Biblioteca para entrada y salida est�ndar (cin, cout)
#include <fstream>       // Biblioteca para manejo de archivos (ifstream, ofstream)
#include <string>
#include "Empleados.h"
#include "Cliente.h"
#include "Proveedores.h"
#include "Contabilidad.h"
#include "Auditoria.h"
#include "Usuario.h"
#include <conio.h>       // Biblioteca para funciones de consola (como getch)
#include "Nominas.h"
#include "Bitacora.h"
#include "Bancos.h"
#include "Moneda.h"
#include <limits>        // Biblioteca para usar limits, como numeric_limits (para manejar buffers)

using namespace std;

// Funci�n para pausar el sistema hasta que el usuario presione ENTER
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    // Ignorar cualquier entrada pendiente en el buffer hasta encontrar salto de l�nea
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Esperar a que el usuario presione ENTER
    cin.get();
}

// Funci�n para limpiar errores de entrada y vaciar el buffer
void limpiarBufferEntrada() {
    cin.clear(); // Limpia cualquier error previo de cin (como entrada no num�rica cuando se esperaba un n�mero)
    // Ignora todo lo que quede en el buffer de entrada para evitar problemas en lecturas siguientes
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}

void realizarBackup() { //Crea un carpeta llamado "backup" si no existe
    // Crear directorio si no existe (Windows)
    system("mkdir backup 2> nul");  //El "2> nul" redirige cualquier mensaje de error (por ejemplo, si ya existe) para no mostrarlo.
    //Si los archivos de respaldo ya existen, se sobrescriben autom�ticamente.
    // Lista de archivos a respaldar
    const char* archivos[] = {
        "clientes.txt", "proveedores.txt", "empleados.txt",
        "movimientos.txt", "prestamos.txt", "bitacora.txt",
        "auditores.txt", "pagos.txt", "salarios.txt"
    };

    // Copiar cada archivo sobrescribiendo el anterior
    for (const char* archivo : archivos) {
        string comando = "copy /Y " + string(archivo) + // - copy /Y: copia el archivo y sobrescribe el existente sin preguntar
                        " backup\\" + string(archivo) + ".bak > nul"; //archivo.bak: destino del archivo, con extensi�n .bak
        system(comando.c_str());                                      //// - > nul: redirige la salida est�ndar para evitar mostrar mensajes
    }
}


// Funci�n que muestra el men� Archivo, recibe el usuario actual y un objeto bit�cora para registrar acciones
void menuArchivo(const string& usuario, Bitacora& bitacora) {
    Usuario::limpiarPantalla(); // Llama a m�todo para limpiar la pantalla (generalmente usando sistema operativo)
    int opcion;                 // Variable para guardar la opci�n seleccionada por el usuario

    do {
        // Mostrar las opciones disponibles en el men� Archivo
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n--- MEN� ARCHIVO ---";
        cout << "\n1. Backup";
        cout << "\n2. Volver al Men� General";
        cout << "\nSeleccione una opci�n: ";

        cin >> opcion;// Leer la opci�n ingresada

        // Validar que la entrada sea correcta y no haya fallado la lectura
        if(cin.fail()) {
            limpiarBufferEntrada();  // Limpiar buffer y errores si la entrada fue inv�lida
            cout << "\nEntrada inv�lida. Intente de nuevo.\n";
            continue; // Volver a mostrar el men�
        }

        switch (opcion) {
            case 1:
                realizarBackup();
                cout << "\nBackup realizado exitosamente!\n";
                bitacora.insertar(usuario, 4905, "Sistema", "Backup realizado");
                break;

            case 2:
                // Opci�n para regresar al men� general, salir de este men�
                return;

            default:
                cout << "\nOpci�n inv�lida.\n";
                break;
        }

        pausar();
        Usuario::limpiarPantalla();

    } while (true);
}

// Funci�n que muestra el men� Cat�logos con varias opciones para gestionar diferentes m�dulos del sistema
void menuCatalogos(const string& usuario, Bitacora& bitacora, Empleados& empleados, Cliente& cliente, Proveedor& proveedor, Auditoria& auditoria, Nominas& nominas) {
    Usuario::limpiarPantalla();
    int opcion;// Variable para almacenar la opci�n del usuario

    do {
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n--- MEN� CAT�LOGOS ---";
        cout << "\n1. N�minas";
        cout << "\n2. Cliente";
        cout << "\n3. Empleados";
        cout << "\n4. Auditor�a";
        cout << "\n5. Proveedores";
        cout << "\n6. Volver al Men� General";
        cout << "\nSeleccione una opci�n: ";

        cin >> opcion;

        // Validar entrada, asegur�ndose que sea correcta y sin errores
        if(cin.fail()) {
            limpiarBufferEntrada();  // Limpiar buffer y errores si la entrada fue inv�lida
            cout << "\nEntrada inv�lida. Intente de nuevo.\n";
            continue;// Volver a mostrar el men�
        }

        // Seg�n la opci�n, se accede al m�dulo correspondiente y se registra la acci�n en bit�cora
        switch (opcion) {
            case 1:
                // Acceder al men� de n�minas
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
    } while (true); // Ciclo hasta que se salga con la opci�n 6
}

// Men� de Procesos que incluye movimientos de clientes, contabilidad y configuraci�n bancaria
void menuProcesos(const string& usuario, Bitacora& bitacora, Cliente& cliente, Contabilidad& contabilidad) {
    Usuario::limpiarPantalla();

    Bancos bancos; // Objeto para manejar configuraci�n bancaria
    bancos.setUsuario(usuario);
    Moneda moneda; // Objeto para manejar tipo de moneda
    contabilidad.setUsuario(usuario);


    // Al iniciar el men� de procesos, solicita configuraci�n bancaria
    cout << "\nSeleccione configuraci�n bancaria:\n";
    cout << "\nUsuario: " << usuario << endl;
    bancos.menuConfiguracion(); // Muestra opciones para configurar banco y moneda
    bitacora.insertar(usuario, 4300, "Procesos", "Configuraci�n bancaria");

    int opcionProcesos;
    do {
        cout << "\nUsuario: " << usuario << endl;
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

        // Seg�n la opci�n elegida en el men� de procesos
        switch (opcionProcesos) {
            case 1: {
                Usuario::limpiarPantalla();
                int opcionClientes;
                do {
                    // Submen� para procesos relacionados con clientes
                    cout << "\nUsuario: " << usuario << endl;
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

                    // Acciones espec�ficas para clientes seg�n opci�n
                    switch (opcionClientes) {
                        case 1:
                            cliente.registrarMovimiento(); // Registra un movimiento bancario
                            bitacora.insertar(usuario, 4106, "Clientes", "Movimiento registrado");
                            break;
                        case 2:
                            cliente.mostrarMovimientos(); // Muestra los movimientos registrados
                            bitacora.insertar(usuario, 4107, "Clientes", "Movimientos mostrados");
                            break;
                        case 3:
                            cliente.abrirArchivoMovimientos(); // Abre archivo externo con movimientos
                            bitacora.insertar(usuario, 4108, "Clientes", "Mostrar movimientos");
                            break;
                        case 4:
                            cliente.registrarPrestamo(); // Registra un pr�stamo para el cliente
                            bitacora.insertar(usuario, 4109, "Clientes", "Pr�stamo registrado");
                            break;
                        case 5:
                            cliente.mostrarPrestamos(); // Muestra pr�stamos registrados
                            bitacora.insertar(usuario, 4110, "Clientes", "Pr�stamos mostrados");
                            break;
                        case 6:
                            break; // Sale del submen� clientes
                        default:
                            cout << "Opci�n no v�lida.\n";
                    }
                    pausar();
                    Usuario::limpiarPantalla();
                } while (opcionClientes != 6);
                break;
            }
            case 2:
                // Men� para m�dulo de Contabilidad
                contabilidad.menuContabilidad();
                bitacora.insertar(usuario, 4301, "Contabilidad", "Ingres� al m�dulo Contabilidad");
                pausar();
                Usuario::limpiarPantalla();
                break;
            case 3:
                // Muestra configuraci�n actual del banco y moneda
                cout << "\n--- Configuraci�n bancaria actual ---\n";
                bancos.mostrarConfiguracion();
                moneda.mostrarMoneda();
                bitacora.insertar(usuario, 4302, "Procesos", "Mostr� configuraci�n bancaria y moneda");
                pausar();
                Usuario::limpiarPantalla();
                break;
            case 4:
                cout << "Volviendo al men� general...\n"; // Opci�n para regresar al men� general
                break;
            default:
                cout << "Opci�n no v�lida.\n"; // Mensaje si la opci�n no existe
        }
    } while (opcionProcesos != 4); // Se repite hasta que el usuario decida salir
}

// Men� para mostrar informe (bitacora)
void menuInformes(const string& usuario, Bitacora& bitacora) {
    Usuario::limpiarPantalla();
    int opcionInformes;
    do {
        cout << "\nUsuario: " << usuario << endl;
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
                bitacora.mostrar(); // Muestra todas las acciones registradas en la bit�cora
                bitacora.insertar(usuario, 4990, "Informes", "Bit�cora mostrada"); // Registra la acci�n
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

// Men� principal
void menuGeneral(const string& usuario) {
    // Crea los objetos necesarios para los diferentes m�dulos del sistema
    Bitacora bitacora;
    Empleados empleados;
    empleados.setUsuario(usuario);
    Cliente cliente;
    cliente.setUsuario(usuario);
    Proveedor proveedor;
    proveedor.setUsuario(usuario);
    Auditoria auditoria;
    auditoria.setUsuario(usuario);
    Nominas nominas;
    nominas.setUsuario(usuario);
    Contabilidad contabilidad;

    int opcion;
    do {
        cout << "\nUsuario: " << usuario << endl;
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

        // Ejecuta la funci�n correspondiente al m�dulo seleccionado
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
                // Registra en bit�cora que el usuario cerr� sesi�n y termina el programa
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
        Usuario usuario;
        // Llama al men� de autenticaci�n y verifica si el usuario se autentic� correctamente
         if (usuario.menuAutenticacion(usuarioLogueado)) {

            menuGeneral(usuarioLogueado);
        } else {
            cout << "\nAutenticaci�n fallida.\n";
            bitacoraGlobal.insertar("Desconocido", 4902, "Sistema", "Fall� intento de login");
            break;
        }
    }
    return 0;
}


