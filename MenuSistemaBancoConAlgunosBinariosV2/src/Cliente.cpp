//Boris de Le�n 9959-24-6203
// Modificado por Boris de Leon el 10 de mayo
#include "Cliente.h"
#include "Bitacora.h" // Agrega la bitacora
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring> //Para la implementacion de strncpy


Bitacora bitacoralogCliente; // Instancia global para registrar eventos
using namespace std;

// Limpia la pantalla seg�n el sistema operativo
void Cliente::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa el programa hasta que el usuario presione ENTER
void Cliente::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Carga los clientes desde el archivo clientes.txt
void Cliente::cargarClientes() {
    clientes.clear();
    ifstream archivo("clientes.dat", ios::binary);
    RegistroCliente reg;
    while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
        Cliente c;
        c.codigo = reg.codigo;
        c.nombre = reg.nombre;
        c.telefono = reg.telefono;
        c.direccion = reg.direccion;
        clientes.push_back(c);
    }
    archivo.close();
    ordenarClientes();
}



// Guarda todos los clientes en el archivo clientes
void Cliente::guardarClientes() {
    ofstream archivo("clientes.dat", ios::binary | ios::trunc);
    for (const auto& c : clientes) {
        RegistroCliente reg{};
        strncpy(reg.codigo, c.codigo.c_str(), sizeof(reg.codigo) - 1);
        strncpy(reg.nombre, c.nombre.c_str(), sizeof(reg.nombre) - 1);
        strncpy(reg.telefono, c.telefono.c_str(), sizeof(reg.telefono) - 1);
        strncpy(reg.direccion, c.direccion.c_str(), sizeof(reg.direccion) - 1);
        archivo.write(reinterpret_cast<char*>(&reg), sizeof(reg));
    }
    archivo.close();
}



// Ordena los clientes alfab�ticamente por nombre
void Cliente::ordenarClientes() {
    sort(clientes.begin(), clientes.end(), [](const Cliente& a, const Cliente& b) {
        return a.nombre < b.nombre;
    });
}

void Cliente::setUsuario(const string& u) {
    usuario = u;
}

void Cliente::menuClienteCRUD() {
    int opcion;
    do {
        cargarClientes(); // cargar clientes
        limpiarPantalla();
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== MEN� DE CLIENTES =====";
        cout << "\n1. Crear Cliente";
        cout << "\n2. Borrar Cliente";
        cout << "\n3. Buscar Cliente";
        cout << "\n4. Modificar Cliente";
        cout << "\n5. Desplegar Clientes";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearCliente(); break;
            case 2: borrarCliente(); break;
            case 3: buscarCliente(); break;
            case 4: modificarCliente(); break;
            case 5: desplegarClientes(); break;
            case 6: limpiarPantalla(); return;
            default:
                cout << "\nOpci�n inv�lida.";
                pausar();
        }
    } while (true);
}


// Muestra el men� principal
void Cliente::menuCliente() {
    int opcion;
    do {
        cargarClientes(); // Cargar al entrar o despu�s de cada operaci�n
        limpiarPantalla();
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== MEN� DE CLIENTES =====";
        cout << "\n1. Crear Cliente";
        cout << "\n2. Borrar Cliente";
        cout << "\n3. Buscar Cliente";
        cout << "\n4. Modificar Cliente";
        cout << "\n5. Despliegue de Clientes";
        cout << "\n6. Registrar movimiento";
        cout << "\n7. Mostrar movimientos";
        cout << "\n8. Abrir archivo movimientos.txt";
        cout << "\n9. Registrar prestamo";
        cout << "\n10. Mostrar prestamos";
        cout << "\n11. Salir";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearCliente(); break;
            case 2: borrarCliente(); break;
            case 3: buscarCliente(); break;
            case 4: modificarCliente(); break;
            case 5: desplegarClientes(); break;
            case 6: registrarMovimiento(); break;
            case 7: mostrarMovimientos(); break;
            case 8: abrirArchivoMovimientos(); break;
            case 9: registrarPrestamo(); break;
            case 10: mostrarPrestamos(); break;
            case 11:
                limpiarPantalla();
                return;
            default:
                cout << "\nOpci�n inv�lida.";
                pausar();
        }
    } while (true);
}

// Agrega un nuevo cliente
void Cliente::crearCliente() {
    limpiarPantalla();
    Cliente c;

    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Crear Cliente ===";
    cout << "\nC�digo de Cliente: "; getline(cin, c.codigo);  // Colocado primero
    cout << "Nombre: "; getline(cin, c.nombre);
    cout << "Tel�fono: "; getline(cin, c.telefono);
    cout << "Direcci�n: "; getline(cin, c.direccion);

    clientes.push_back(c);
    ordenarClientes();
    guardarClientes();

    cout << "\nCliente agregado correctamente.";
    bitacoralogCliente.insertar(usuario, 4101, "Clientes", "Crear Cliente");

    pausar();
}

// Borra un cliente por c�digo
void Cliente::borrarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Borrar Cliente ===";
    cout << "\nC�digo de Cliente: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Cliente> nuevaLista;

    for (const auto& c : clientes) {
        if (c.codigo != codigo) {
            nuevaLista.push_back(c);
        } else {
            eliminado = true;
        }
    }

    if (eliminado) {
        clientes = nuevaLista;
        guardarClientes();
        bitacoralogCliente.insertar(usuario, 4102, "Clientes", "Borrar Cliente");

        cout << "\nCliente eliminado correctamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Busca un cliente por c�digo
void Cliente::buscarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Buscar Cliente ===";
    cout << "\nC�digo de Cliente: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& c : clientes) {
        if (c.codigo == codigo) {
            cout << "\nCliente encontrado:";
            cout << "\nC�digo    : " << c.codigo;
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTel�fono  : " << c.telefono;
            cout << "\nDirecci�n : " << c.direccion;
            encontrado = true;
            bitacoralogCliente.insertar(usuario, 4103, "Clientes", "Buscar Cliente");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Modifica los datos de un cliente
void Cliente::modificarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Modificar Cliente ===";
    cout << "\nC�digo de Cliente: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& c : clientes) {
        if (c.codigo == codigo) {
            cout << "\nIngrese nueva informaci�n:";
            cout << "\nNuevo C�digo: "; getline(cin, c.codigo);
            cout << "Nuevo Nombre: "; getline(cin, c.nombre);
            cout << "Nuevo Tel�fono: "; getline(cin, c.telefono);
            cout << "Nueva Direcci�n: "; getline(cin, c.direccion);
            modificado = true;
            break;
        }
    }


if (modificado) { // Si se realiz� alguna modificaci�n en el cliente:
    ordenarClientes(); // Ordena la lista de clientes para mantener el orden alfab�tico o l�gico.
    guardarClientes(); // Guarda la lista actualizada de clientes en el archivo correspondiente,
    bitacoralogCliente.insertar(usuario, 4104, "Clientes", "Modificar Cliente"); // Registra la acci�n realizada en la bit�cora del sistema
        cout << "\nCliente modificado exitosamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Muestra todos los clientes
void Cliente::desplegarClientes() {
    limpiarPantalla();
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Clientes Registrados ===\n";

    if (clientes.empty()) {
        cout << "\nNo hay clientes registrados.";
    } else {
        for (const auto& c : clientes) {
            cout << "\n-----------------------------";
            cout << "\nC�digo    : " << c.codigo;  // Muestra primero el c�digo
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTel�fono  : " << c.telefono;
            cout << "\nDirecci�n : " << c.direccion;
        }
        cout << "\n-----------------------------";
        bitacoralogCliente.insertar(usuario, 4105, "Clientes", "Desplegar Cliente");
    }

    pausar();
}

void Cliente::registrarMovimiento() {
    limpiarPantalla();
    cargarClientes();  // Soluci�n agregada

    string codigoCliente, descripcion, fecha;
    double monto=0;
    cout << "\n=== Registrar Movimiento ===";
    cout << "\nC�digo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    bool encontrado = false;
    for (const auto& c : clientes) {   // Recorre cada cliente dentro del vector 'clientes'.
        if (c.codigo == codigoCliente) {
            encontrado = true;
            cout << "Descripci�n del movimiento: ";
            getline(cin, descripcion);

            cout << "Fecha del movimiento (DD/MM/AAAA): ";
            getline(cin, fecha);
            cout << "Monto del movimiento: ";
            cin >> monto;
            cin.ignore();

            ofstream archivo("movimientos.dat", ios::binary | ios::app);
RegistroMovimiento reg{};
strncpy(reg.codigoCliente, codigoCliente.c_str(), sizeof(reg.codigoCliente) - 1);
strncpy(reg.descripcion, descripcion.c_str(), sizeof(reg.descripcion) - 1);
strncpy(reg.fecha, fecha.c_str(), sizeof(reg.fecha) - 1);
reg.monto = monto;
archivo.write(reinterpret_cast<char*>(&reg), sizeof(reg));
archivo.close();

            cout << "\nMovimiento registrado correctamente.";

            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}


void Cliente::mostrarMovimientos() {
    limpiarPantalla();                         // Limpia la pantalla antes de mostrar informaci�n.
    string codigoCliente, linea;               // Declara variables para c�digo del cliente y l�nea le�da.
    cout << "\n=== Mostrar Movimientos ===";   // Muestra t�tulo del men�.
    cout << "\nC�digo del Cliente: ";          // Solicita al usuario ingresar el c�digo del cliente.
    cin.ignore();                             // Limpia el buffer de entrada para evitar errores.
    getline(cin, codigoCliente);              // Lee el c�digo del cliente ingresado por el usuario.

ifstream archivo("movimientos.dat", ios::binary);
RegistroMovimiento reg;
bool hayMovimientos = false;
while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
    if (codigoCliente == reg.codigoCliente) {
        cout << "\n- " << reg.descripcion << " | Fecha: " << reg.fecha << " | Monto: Q" << reg.monto;
        hayMovimientos = true;
    }
}
archivo.close();
if (!hayMovimientos) {
    cout << "\nNo hay movimientos registrados para este cliente.";
}


    pausar();
}

void Cliente::abrirArchivoMovimientos() {
    limpiarPantalla();                       // Limpia la pantalla antes de mostrar contenido.
    cout << "\n=== Contenido del archivo movimientos.txt ===\n";  // Muestra t�tulo.

    ifstream archivo("movimientos.dat", ios::binary);
RegistroMovimiento reg;
while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
    cout << "\nCliente: " << reg.codigoCliente
         << " | Desc: " << reg.descripcion
         << " | Fecha: " << reg.fecha
         << " | Monto: Q" << reg.monto;
}
archivo.close(); // Cierra el archivo despu�s de leerlo.

    pausar();                              // Pausa el programa hasta que el usuario presione ENTER.
}


void Cliente::registrarPrestamo() {
    limpiarPantalla();                                // Limpia pantalla antes de iniciar.
    string codigoCliente, estado;                      // Variables para c�digo y estado del pr�stamo.
    double monto;                                      // Variable para monto del pr�stamo.
    cout << "\n=== Registrar Pr�stamo ===";            // Muestra t�tulo de la funci�n.
    cout << "\nC�digo del Cliente: ";                  // Solicita c�digo del cliente.
    cin.ignore();                                      // Ignora caracteres previos en el buffer.
    getline(cin, codigoCliente);                       // Lee el c�digo del cliente.

    bool encontrado = false;                           // Variable para verificar si cliente existe.
    for (const auto& c :clientes) {                    // Itera sobre todos los clientes.
        if (c.codigo == codigoCliente) {               // Verifica si el c�digo coincide.
            encontrado = true;                         // Marca cliente como encontrado.
            cout << "Monto del pr�stamo: ";            // Solicita monto del pr�stamo.
            cin >> monto;                              // Lee el monto.
            cin.ignore();                              // Limpia buffer despu�s de entrada num�rica.
            cout << "�Est� pagado? (S�/No): ";         // Pregunta estado del pago.
            getline(cin, estado);                       // Lee el estado del pr�stamo.

            ofstream archivo("prestamos.dat", ios::binary | ios::app);
RegistroPrestamo reg{};
strncpy(reg.codigoCliente, codigoCliente.c_str(), sizeof(reg.codigoCliente) - 1);
reg.monto = monto;
strncpy(reg.estado, estado.c_str(), sizeof(reg.estado) - 1);
archivo.write(reinterpret_cast<char*>(&reg), sizeof(reg));
archivo.close();


            cout << "\nPr�stamo registrado correctamente."; // Mensaje de confirmaci�n.

            break;                                     // Sale del ciclo al encontrar el cliente.
        }
    }

    if (!encontrado) {                                 // Si cliente no fue encontrado.
        cout << "\nCliente no encontrado.";            // Muestra mensaje de error.
    }

    pausar();                                         // Pausa hasta que usuario presione ENTER.
}

void Cliente::mostrarPrestamos() {
    limpiarPantalla();
    string codigoCliente;
    cout << "\n=== Mostrar Pr�stamos ===";
    cout << "\nC�digo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    ifstream archivo("prestamos.dat", ios::binary);
    RegistroPrestamo reg;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
        if (codigoCliente == reg.codigoCliente) {
            cout << "\nMonto: Q" << reg.monto << " | Estado: " << reg.estado;
            encontrado = true;
        }
    }
    archivo.close();

    if (!encontrado) {
        cout << "\nNo se encontraron pr�stamos para este cliente.";
    }

    pausar();
}
