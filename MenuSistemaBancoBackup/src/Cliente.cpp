//Boris de Le�n 9959-24-6203
// Modificado por Boris de Leon el 10 de mayo
#include "Cliente.h"
#include "Bitacora.h" // Agrega la bitacora
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

Bitacora log; // Instancia global para registrar eventos
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
    clientes.clear();  // Vaciar lista actual
    ifstream archivo("clientes.txt");
    Cliente c;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = 0;
        int campo = 0;
        string datos[4];  // Solo 4 campos ahora (sin saldo)
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[3] = linea; // Direcci�n

        c.codigo = datos[0];
        c.nombre = datos[1];
        c.telefono = datos[2];
        c.direccion = datos[3];

        clientes.push_back(c);
    }

    archivo.close();
    ordenarClientes();
}

// Guarda todos los clientes en el archivo clientes.txt
void Cliente::guardarClientes() {
    ofstream archivo("clientes.txt");
    for (const auto& c : clientes) {
        archivo << c.codigo << "," << c.nombre << "," << c.telefono << "," << c.direccion << "\n";
    }
    archivo.close();
}

// Ordena los clientes alfab�ticamente por nombre
void Cliente::ordenarClientes() {
    sort(clientes.begin(), clientes.end(), [](const Cliente& a, const Cliente& b) {
        return a.nombre < b.nombre;
    });
}
void Cliente::menuClienteCRUD() {
    int opcion;
    do {
        cargarClientes(); // cargar clientes
        limpiarPantalla();
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

    cout << "\n=== Crear Cliente ===";
    cout << "\nC�digo de Cliente: "; getline(cin, c.codigo);  // Colocado primero
    cout << "Nombre: "; getline(cin, c.nombre);
    cout << "Tel�fono: "; getline(cin, c.telefono);
    cout << "Direcci�n: "; getline(cin, c.direccion);

    clientes.push_back(c);
    ordenarClientes();
    guardarClientes();

    cout << "\nCliente agregado correctamente.";
    log.insertar("Admin", 4101, "Clientes", "Crear Cliente");

    pausar();
}

// Borra un cliente por c�digo
void Cliente::borrarCliente() {
    limpiarPantalla();
    string codigo;
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
        log.insertar("Admin", 4104, "Clientes", "Borrar Cliente");

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

    if (modificado) {
        ordenarClientes();
        guardarClientes();
        log.insertar("Admin", 4103, "Clientes", "Modificar Cliente");

        cout << "\nCliente modificado exitosamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Muestra todos los clientes
void Cliente::desplegarClientes() {
    limpiarPantalla();
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
    for (const auto& c : clientes) {
        if (c.codigo == codigoCliente) {
            encontrado = true;
            cout << "Descripci�n del movimiento: ";
            getline(cin, descripcion);

            cout << "Fecha del movimiento (DD/MM/AAAA): ";
            getline(cin, fecha);
            cout << "Monto del movimiento: ";
            cin >> monto;
            cin.ignore();

            ofstream archivo("movimientos.txt", ios::app);
            archivo << codigoCliente << "," << descripcion << "," << fecha << "," << monto  << "\n";
            archivo.close();

            cout << "\nMovimiento registrado correctamente.";
            log.insertar("Admin", 5101, "Movimientos", "Registrar Movimiento");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}


void Cliente::mostrarMovimientos() {
    limpiarPantalla();
    string codigoCliente, linea;
    cout << "\n=== Mostrar Movimientos ===";
    cout << "\nC�digo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    ifstream archivo("movimientos.txt");
    bool hayMovimientos = false;

    while (getline(archivo, linea)) {
        size_t pos = linea.find(',');
        string codigo = linea.substr(0, pos);
        string descripcion = linea.substr(pos + 1);

        if (codigo == codigoCliente) {
            cout << "\n- " << descripcion;
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
    limpiarPantalla();
    cout << "\n=== Contenido del archivo movimientos.txt ===\n";

    ifstream archivo("movimientos.txt");
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << "\n";
    }
    archivo.close();

    pausar();
}

void Cliente::registrarPrestamo() {
    limpiarPantalla();
    string codigoCliente, estado;
    double monto;
    cout << "\n=== Registrar Pr�stamo ===";
    cout << "\nC�digo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    bool encontrado = false;
    for (const auto& c :clientes) {
        if (c.codigo == codigoCliente) {
            encontrado = true;
            cout << "Monto del pr�stamo: ";
            cin >> monto;
            cin.ignore();
            cout << "�Est� pagado? (S�/No): ";
            getline(cin, estado);

            ofstream archivo("prestamos.txt", ios::app);
            archivo << codigoCliente << "," << monto << ", se realizo el pago del prestamo? " << estado << "\n";
            archivo.close();

            cout << "\nPr�stamo registrado correctamente.";
            log.insertar("Admin", 5201, "Pr�stamos", "Registrar Pr�stamo");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

void Cliente::mostrarPrestamos() {
    limpiarPantalla();
    string codigoCliente, linea;
    cout << "\n=== Mostrar Pr�stamos ===";
    cout << "\nC�digo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    ifstream archivo("prestamos.txt");
    bool hayPrestamos = false;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        string codigo = linea.substr(0, pos1);
        string monto = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string estado = linea.substr(pos2 + 1);

        if (codigo == codigoCliente) {
            cout << "\nMonto: Q." << monto << " - Estado: " << estado;
            hayPrestamos = true;
        }
    }

    archivo.close();

    if (!hayPrestamos) {
        cout << "\nNo hay pr�stamos registrados para este cliente.";
    }

    pausar();
}
