//Karla Ruiz 9959-24-6859
#include "Empleados.h" // Incluye el encabezado de la clase Empleados.
#include <iostream>    // Incluye la biblioteca est�ndar de entrada/salida.
#include <fstream>     // Incluye la biblioteca para manejo de archivos.
#include <algorithm>   // Incluye funciones de algoritmos, como sort.
#include "Bitacora.h"  // Incluye el encabezado de la clase Bitacora.

using namespace std; // Permite usar elementos del espacio de nombres std sin prefijo.

Bitacora bitacoralogEmpleados; // Inicializa una instancia est�tica de Bitacora para registrar acciones.

void Empleados::limpiarPantalla() { // M�todo para limpiar la pantalla seg�n el sistema operativo.
#ifdef _WIN32
    system("cls"); // Comando para limpiar la pantalla en Windows.
#else
    system("clear"); // Comando para limpiar la pantalla en sistemas Unix.
#endif
}

void Empleados::pausar() { // M�todo para pausar la ejecuci�n del programa.
    cout << "\nPresione ENTER para continuar..."; // Mensaje para el usuario.
    cin.ignore(); // Ignora el car�cter de nueva l�nea.
    cin.get(); // Espera a que el usuario presione ENTER.
}

void Empleados::cargarEmpleados() { // M�todo para cargar empleados desde un archivo.
    empleados.clear(); // Limpia el vector de empleados actual.
    ifstream archivo("empleados.txt"); // Abre el archivo para lectura.
    Empleado e; // Crea una instancia de Empleado.
    string linea; // Variable para almacenar cada l�nea del archivo.

    while (getline(archivo, linea)) { // Lee el archivo l�nea por l�nea.
        size_t pos = 0; // Variable para almacenar la posici�n de la coma.
        string datos[4]; // Array para almacenar los datos del empleado.

        for (int i = 0; i < 3; ++i) { // Extrae los primeros tres campos.
            pos = linea.find(','); // Encuentra la posici�n de la coma.
            datos[i] = linea.substr(0, pos); // Obtiene el substring hasta la coma.
            linea.erase(0, pos + 1); // Elimina la parte procesada de la l�nea.
        }
        datos[3] = linea; // Almacena el �ltimo campo.

        e.nombre = datos[0]; // Asigna el nombre del empleado.
        e.codigo = datos[1]; // Asigna el c�digo del empleado.
        e.puesto = datos[2]; // Asigna el puesto del empleado.
        e.telefono = datos[3]; // Asigna el tel�fono del empleado.

        empleados.push_back(e); // Agrega el empleado al vector.
    }

    archivo.close(); // Cierra el archivo.
    ordenarEmpleados(); // Ordena la lista de empleados.
}

void Empleados::guardarEmpleados() { // M�todo para guardar empleados en un archivo.
    ofstream archivo("empleados.txt"); // Abre el archivo para escritura.
    for (const auto& e : empleados) { // Itera sobre cada empleado.
        archivo << e.nombre << "," << e.codigo << "," << e.puesto << "," << e.telefono << "\n"; // Escribe los datos en el archivo.
    }
    archivo.close(); // Cierra el archivo.
}

void Empleados::ordenarEmpleados() { // M�todo para ordenar empleados alfab�ticamente por nombre.
    sort(empleados.begin(), empleados.end(), [](const Empleado& a, const Empleado& b) {
        return a.nombre < b.nombre; // Compara los nombres de los empleados.
    });
}

void Empleados::menuEmpleados() { // M�todo para mostrar el men� principal de empleados.
    int opcion; // Variable para almacenar la opci�n seleccionada por el usuario.
    do {
        cargarEmpleados(); // Carga la lista de empleados antes de mostrar el men�.
        limpiarPantalla(); // Limpia la pantalla.
        cout << "\n===== MEN� DE EMPLEADOS ====="; // Muestra el encabezado del men�.
        cout << "\n1. Crear Empleado"; // Opci�n para crear un nuevo empleado.
        cout << "\n2. Borrar Empleado"; // Opci�n para borrar un empleado.
        cout << "\n3. Buscar Empleado"; // Opci�n para buscar un empleado.
        cout << "\n4. Modificar Empleado"; // Opci�n para modificar un empleado.
        cout << "\n5. Desplegar Empleados"; // Opci�n para mostrar todos los empleados.
        cout << "\n6. Salir"; // Opci�n para salir del men�.
        cout << "\nSeleccione una opci�n: "; // Solicita al usuario que seleccione una opci�n.
        cin >> opcion; // Lee la opci�n ingresada por el usuario.
        cin.ignore(); // Ignora el car�cter de nueva l�nea.

        switch (opcion) { // Estructura de control para manejar la opci�n seleccionada.
            case 1: crearEmpleado(); break; // Llama al m�todo para crear un empleado.
            case 2: borrarEmpleado(); break; // Llama al m�todo para borrar un empleado.
            case 3: buscarEmpleado(); break; // Llama al m�todo para buscar un empleado.
            case 4: modificarEmpleado(); break; // Llama al m�todo para modificar un empleado.
            case 5: desplegarEmpleados(); break; // Llama al m�todo para mostrar todos los empleados.
            case 6:
                limpiarPantalla(); // Limpia la pantalla al salir.
                return; // Sale del m�todo.
            default:
                cout << "\nOpci�n inv�lida."; // Informa al usuario que la opci�n es inv�lida.
                pausar(); // Pausa la ejecuci�n.
        }
    } while (true); // Repite el ciclo hasta que se seleccione una opci�n v�lida.
}

void Empleados::crearEmpleado() { // M�todo para crear un nuevo empleado.
    limpiarPantalla(); // Limpia la pantalla.
    Empleado e; // Crea una instancia de Empleado.
    cout << "\n=== Crear Empleado ==="; // Encabezado del proceso de creaci�n.
    cout << "\nNombre: "; getline(cin, e.nombre); // Solicita el nombre.
    cout << "C�digo: "; getline(cin, e.codigo); // Solicita el c�digo.
    cout << "Puesto de trabajo: "; getline(cin, e.puesto); // Solicita el puesto.
    cout << "Tel�fono: "; getline(cin, e.telefono); // Solicita el tel�fono.

    empleados.push_back(e); // Agrega el nuevo empleado al vector.
    ordenarEmpleados(); // Ordena la lista de empleados.
    guardarEmpleados(); // Guarda la lista actualizada en el archivo.

    bitacoralogEmpleados.insertar("Admin", 4006, "Empleados", "Crear empleado"); // Registra la acci�n en la bit�cora.
    cout << "\nEmpleado agregado correctamente."; // Mensaje de confirmaci�n.
    pausar(); // Pausa la ejecuci�n.
}

void Empleados::borrarEmpleado() { // M�todo para borrar un empleado.
    limpiarPantalla(); // Limpia la pantalla.
    string nombre, codigo; // Variables para almacenar el nombre y c�digo del empleado a borrar.
    cout << "\n=== Borrar Empleado ==="; // Encabezado del proceso de borrado.
    cout << "\nNombre: "; getline(cin, nombre); // Solicita el nombre.
    cout << "C�digo: "; getline(cin, codigo); // Solicita el c�digo.

    bool eliminado = false; // Variable para indicar si se elimin� el empleado.
    vector<Empleado> nuevaLista; // Vector temporal para almacenar empleados restantes.

    for (const auto& e : empleados) { // Itera sobre cada empleado.
        if (e.nombre != nombre || e.codigo != codigo) { // Si no coincide con el empleado a borrar.
            nuevaLista.push_back(e); // Agrega a la nueva lista.
        } else {
            eliminado = true; // Marca que se elimin� un empleado.
        }
    }

    if (eliminado) { // Si se elimin� un empleado.
        empleados = nuevaLista; // Actualiza la lista de empleados.
        guardarEmpleados(); // Guarda la lista actualizada en el archivo.
        bitacoralogEmpleados.insertar("Admin", 4007, "Empleados", "Borrar empleado"); // Registra la acci�n en la bit�cora.
        cout << "\nEmpleado eliminado correctamente."; // Mensaje de confirmaci�n.
    } else {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontr� al empleado.
    }

    pausar(); // Pausa la ejecuci�n.
}

void Empleados::buscarEmpleado() { // M�todo para buscar un empleado.
    limpiarPantalla(); // Limpia la pantalla.
    string nombre, codigo; // Variables para almacenar el nombre y c�digo del empleado a buscar.
    cout << "\n=== Buscar Empleado ==="; // Encabezado del proceso de b�squeda.
    cout << "\nNombre: "; getline(cin, nombre); // Solicita el nombre.
    cout << "C�digo: "; getline(cin, codigo); // Solicita el c�digo.

    bool encontrado = false; // Variable para indicar si se encontr� el empleado.

    for (const auto& e : empleados) { // Itera sobre cada empleado.
        if (e.nombre == nombre && e.codigo == codigo) { // Si se encuentra el empleado.
            cout << "\nEmpleado encontrado:"; // Mensaje de confirmaci�n.
            cout << "\nNombre   : " << e.nombre; // Muestra el nombre.
            cout << "\nC�digo   : " << e.codigo; // Muestra el c�digo.
            cout << "\nPuesto   : " << e.puesto; // Muestra el puesto.
            cout << "\nTel�fono : " << e.telefono; // Muestra el tel�fono.
            bitacoralogEmpleados.insertar("Admin", 4008, "Empleados", "Buscar empleado"); // Registra la acci�n en la bit�cora.
            encontrado = true; // Marca que se encontr� al empleado.
            break; // Sale del bucle.
        }
    }

    if (!encontrado) { // Si no se encontr� el empleado.
        cout << "\nEmpleado no encontrado."; // Mensaje informando que no se encontr�.
    }

    pausar(); // Pausa la ejecuci�n.
}

void Empleados::modificarEmpleado() { // M�todo para modificar informaci�n de un empleado.
    limpiarPantalla(); // Limpia la pantalla.
    string nombre, codigo; // Variables para almacenar el nombre y c�digo del empleado a modificar.
    cout << "\n=== Modificar Empleado ==="; // Encabezado del proceso de modificaci�n.
    cout << "\nNombre: "; getline(cin, nombre); // Solicita el nombre.
    cout << "C�digo: "; getline(cin, codigo); // Solicita el c�digo.

    bool modificado = false; // Variable para indicar si se modific� el empleado.

    for (auto& e : empleados) { // Itera sobre cada empleado.
        if (e.nombre == nombre && e.codigo == codigo) { // Si se encuentra el empleado.
            cout << "\nIngrese nueva informaci�n:"; // Mensaje para ingresar nueva informaci�n.
            cout << "\nNuevo Nombre: "; getline(cin, e.nombre); // Solicita el nuevo nombre.
            cout << "Nuevo C�digo: "; getline(cin, e.codigo); // Solicita el nuevo c�digo.
            cout << "Nuevo Puesto: "; getline(cin, e.puesto); // Solicita el nuevo puesto.
            cout << "Nuevo Tel�fono: "; getline(cin, e.telefono); // Solicita el nuevo tel�fono.
            modificado = true; // Marca que se modific� el empleado.
            break; // Sale del bucle.
        }
    }

    if (modificado) { // Si se modific� el empleado.
        ordenarEmpleados(); // Ordena la lista de empleados.
        guardarEmpleados(); // Guarda la lista actualizada en el archivo.
        bitacoralogEmpleados.insertar("Admin", 4009, "Empleados", "Modificar empleado"); // Registra la acci�n en la bit�cora.
        cout << "\nEmpleado modificado correctamente."; // Mensaje de confirmaci�n.
    } else {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontr� al empleado.
    }

    pausar(); // Pausa la ejecuci�n.
}

void Empleados::desplegarEmpleados() { // M�todo para mostrar todos los empleados.
    limpiarPantalla(); // Limpia la pantalla.
    cout << "\n=== Empleados Registrados ===\n"; // Encabezado de la lista de empleados.

    if (empleados.empty()) { // Si no hay empleados registrados.
        cout << "\nNo hay empleados registrados."; // Mensaje informando que no hay empleados.
    } else {
        for (const auto& e : empleados) { // Itera sobre cada empleado.
            cout << "\n----------------------------"; // L�nea divisoria.
            cout << "\nNombre   : " << e.nombre; // Muestra el nombre.
            cout << "\nC�digo   : " << e.codigo; // Muestra el c�digo.
            cout << "\nPuesto   : " << e.puesto; // Muestra el puesto.
            cout << "\nTel�fono : " << e.telefono; // Muestra el tel�fono.
        }
        cout << "\n----------------------------"; // L�nea divisoria final.
        bitacoralogEmpleados.insertar("Admin", 4010, "Empleados", "Desplegar empleados"); // Registra la acci�n en la bit�cora.
    }

    pausar(); // Pausa la ejecuci�n.
}
