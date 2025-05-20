// Boris de Le�n 9959-24-6203
#include "Proveedores.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// Limpia la pantalla seg�n el sistema operativo
// Par�metros: ninguno
// Retorna: void
void Proveedor::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa el programa hasta que el usuario presione ENTER
// Par�metros: ninguno
// Retorna: void
void Proveedor::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Carga los proveedores desde el archivo binario "proveedores.dat"
// Par�metros: ninguno
// Retorna: vector<Proveedor> con los proveedores cargados, ordenados alfab�ticamente por nombre
vector<Proveedor> Proveedor::cargarProveedores() {
    vector<Proveedor> proveedores;
    ifstream archivo("proveedores.dat", ios::binary);
    if (!archivo) {
        // Si no existe archivo, retornar vector vac�o
        return proveedores;
    }

    // Leer hasta el final del archivo
    while (true) {
        Proveedor p;
        size_t size;

        // Leer tama�o y contenido del campo codigo
        if (!archivo.read(reinterpret_cast<char*>(&size), sizeof(size))) break;
        p.codigo.resize(size);
        archivo.read(&p.codigo[0], size);

        // Leer tama�o y contenido del campo nombre
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        p.nombre.resize(size);
        archivo.read(&p.nombre[0], size);

        // Leer tama�o y contenido del campo telefono
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        p.telefono.resize(size);
        archivo.read(&p.telefono[0], size);

        // Leer tama�o y contenido del campo direccion
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        p.direccion.resize(size);
        archivo.read(&p.direccion[0], size);

        proveedores.push_back(p);
    }
    archivo.close();
    ordenarProveedores(proveedores);
    return proveedores;
}

// Guarda todos los proveedores en el archivo binario "proveedores.dat"
// Par�metros:
//   - proveedores: vector de proveedores a guardar
// Retorna: void
void Proveedor::guardarProveedores(const vector<Proveedor>& proveedores) {
    ofstream archivo("proveedores.dat", ios::binary | ios::trunc);
    for (const auto& p : proveedores) {
        size_t size;

        // Guardar codigo con tama�o y datos
        size = p.codigo.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(p.codigo.c_str(), size);

        // Guardar nombre con tama�o y datos
        size = p.nombre.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(p.nombre.c_str(), size);

        // Guardar telefono con tama�o y datos
        size = p.telefono.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(p.telefono.c_str(), size);

        // Guardar direccion con tama�o y datos
        size = p.direccion.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(p.direccion.c_str(), size);
    }
    archivo.close();
}

// Ordena el vector de proveedores alfab�ticamente por nombre
// Par�metros:
//   - proveedores: vector de proveedores a ordenar (por referencia)
// Retorna: void
void Proveedor::ordenarProveedores(vector<Proveedor>& proveedores) {
    sort(proveedores.begin(), proveedores.end(), [](const Proveedor& a, const Proveedor& b) {
        return a.nombre < b.nombre;
    });
}

// Muestra el men� principal para la gesti�n de proveedores
// Par�metros: ninguno
// Retorna: void
void Proveedor::menuProveedor() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== MEN� DE PROVEEDORES =====";
        cout << "\n1. Crear Proveedor";
        cout << "\n2. Borrar Proveedor";
        cout << "\n3. Buscar Proveedor";
        cout << "\n4. Modificar Proveedor";
        cout << "\n5. Despliegue de Proveedores";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearProveedor(); break;
            case 2: borrarProveedor(); break;
            case 3: buscarProveedor(); break;
            case 4: modificarProveedor(); break;
            case 5: desplegarProveedores(); break;
            case 6:
                limpiarPantalla();
                return;
            default:
                cout << "\nOpci�n inv�lida.";
                pausar();
        }
    } while (true);
}

// Crea un nuevo proveedor solicitando datos al usuario y lo guarda
// Par�metros: ninguno
// Retorna: void
void Proveedor::crearProveedor() {
    limpiarPantalla();
    Proveedor p;
    vector<Proveedor> proveedores = cargarProveedores();

    cout << "\n=== Crear Proveedor ===";
    cout << "\nC�digo: "; getline(cin, p.codigo);
    cout << "Nombre: "; getline(cin, p.nombre);
    cout << "Tel�fono: "; getline(cin, p.telefono);
    cout << "Direcci�n: "; getline(cin, p.direccion);

    proveedores.push_back(p);
    ordenarProveedores(proveedores);
    guardarProveedores(proveedores);

    cout << "\nProveedor agregado correctamente.";
    pausar();
}

// Borra un proveedor busc�ndolo por c�digo
// Par�metros: ninguno
// Retorna: void
void Proveedor::borrarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Borrar Proveedor ===";
    cout << "\nC�digo: "; getline(cin, codigo);

    vector<Proveedor> proveedores = cargarProveedores();
    size_t inicial = proveedores.size();

    proveedores.erase(
        remove_if(proveedores.begin(), proveedores.end(), [&](const Proveedor& p) {
            return p.codigo == codigo;
        }),
        proveedores.end()
    );

    if (proveedores.size() < inicial) {
        guardarProveedores(proveedores);
        cout << "\nProveedor eliminado correctamente.";
    } else {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Busca un proveedor por c�digo y muestra su informaci�n
// Par�metros: ninguno
// Retorna: void
void Proveedor::buscarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Buscar Proveedor ===";
    cout << "\nC�digo: "; getline(cin, codigo);

    vector<Proveedor> proveedores = cargarProveedores();
    bool encontrado = false;

    for (const auto& p : proveedores) {
        if (p.codigo == codigo) {
            cout << "\nProveedor encontrado:";
            cout << "\nC�digo    : " << p.codigo;
            cout << "\nNombre    : " << p.nombre;
            cout << "\nTel�fono  : " << p.telefono;
            cout << "\nDirecci�n : " << p.direccion;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Modifica un proveedor existente buscando por c�digo y pidiendo nuevos datos
// Par�metros: ninguno
// Retorna: void
void Proveedor::modificarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Modificar Proveedor ===";
    cout << "\nC�digo: "; getline(cin, codigo);

    vector<Proveedor> proveedores = cargarProveedores();
    bool modificado = false;

    for (auto& p : proveedores) {
        if (p.codigo == codigo) {
            cout << "\nIngrese nueva informaci�n:";
            cout << "\nNuevo Nombre: "; getline(cin, p.nombre);
            cout << "Nuevo Tel�fono: "; getline(cin, p.telefono);
            cout << "Nueva Direcci�n: "; getline(cin, p.direccion);
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarProveedores(proveedores);
        guardarProveedores(proveedores);
        cout << "\nProveedor modificado exitosamente.";
    } else {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Muestra todos los proveedores registrados
// Par�metros: ninguno
// Retorna: void
void Proveedor::desplegarProveedores() {
    limpiarPantalla();
    cout << "\n=== Proveedores Registrados ===\n";

    vector<Proveedor> proveedores = cargarProveedores();
    if (proveedores.empty()) {
        cout << "\nNo hay proveedores registrados.";
    } else {
        for (const auto& p : proveedores) {
            cout << "\n-----------------------------";
            cout << "\nC�digo    : " << p.codigo;
            cout << "\nNombre    : " << p.nombre;
            cout << "\nTel�fono  : " << p.telefono;
            cout << "\nDirecci�n : " << p.direccion;
        }
        cout << "\n-----------------------------";
    }

    pausar();
}
