//Programado por Priscila Sarai Guzm�n Calgua 9959-23-450
#include "Nominas.h"
#include <iostream> //Entrada y salida de datos
#include <fstream>   // Para manejo de archivos lectura y escritura
#include <algorithm> // Para la funci�n sort (orden)
#include "Bitacora.h"
#include "Moneda.h"
#include <string>       // Para string
#include <stdexcept>    // Para runtime_error

// Bit�cora global para registrar acciones realizadas en N�minas
Bitacora bitacoralogNominas;

using namespace std;

// Limpia la pantalla dependiendo del sistema operativo
void Nominas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa hasta que el usuario presione ENTER
void Nominas::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();//Limpia el buffer de entrada
    cin.get();//Espera que el usuario presione ENTER
}

// Carga los empleados desde el archivo "nominas.txt"
void Nominas::cargarEmpleados() {
    empleados.clear();
    ifstream archivo("nominas.txt");//Abre el archivo en modo lectura

    try {
       //verifica si el archivo se puede abrir
       if (!archivo.is_open()) {
       //lanza una excepci�n del tipo runtime_error con el mensaje especifico
       //Si es as� el flujo se lanza a catch
            throw runtime_error("No se pudo abrir el archivo empleados.txt");
        }

        EmpleadoNomina e;
        string linea;
//Procesa l�nea por l�nea
        while (getline(archivo, linea)) {
            size_t pos = 0;
            string datos[5];
//Separa los datos por comas
            for (int i = 0; i < 4; ++i) {
                pos = linea.find(',');
                if (pos == string::npos) throw runtime_error("Formato inv�lido en nominas.txt");
                datos[i] = linea.substr(0, pos);
                linea.erase(0, pos + 1);
            }

            datos[4] = linea;
          //Asigna valores al objeto EmpleadoNomina
            e.nombre = datos[0];
            e.telefono = datos[1];
            e.codigo = datos[2];
            e.direccion = datos[3];
            //stod()convierte de string a double
            //Si datos[4] tiene letras en lugar de n�meros este fallar�
            e.salario = stod(datos[4]);

            empleados.push_back(e);//agrega el empleado al vector
        }

        archivo.close();
        ordenarEmpleados();
//captura cualquier excepci�n derivada de exception
    } catch (const exception& ex) {
    //imprime el mensaje del error lanzado con throw
        cout << "\nError al cargar empleados: " << ex.what() << endl;
    }
}

// Guarda los empleados actuales en "nominas.txt"
void Nominas::guardarEmpleados() {
    try {
        ofstream archivo("nominas.txt");//Modo escritura (sobrescribe)
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo nominas.txt para escritura.");
        }
//Escribe los datos separados por comas
        for (const auto& e : empleados) {
            archivo << e.nombre << "," << e.telefono << "," << e.codigo << ","
                    << e.direccion << "," << e.salario << "\n";
        }

        archivo.close();

    } catch (const exception& ex) {
        cout << "\nError al guardar empleados: " << ex.what() << endl;
    }
}

// Ordena empleados alfab�ticamente por nombre
void Nominas::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const EmpleadoNomina& a, const EmpleadoNomina& b) {
        return a.nombre < b.nombre;
    });
}



void Nominas::setUsuario(const string& u) {
    usuario = u;
}

double leerSalario() {
    string entrada;
    double salario;
    cout << "Salario (GTQ): Q";
    getline(cin, entrada);  // Se lee como string

    try {
        // Intenta convertir a double
        salario = stod(entrada);
    } catch (const invalid_argument& e) {
        throw runtime_error("Entrada inv�lida. Debe ingresar un n�mero para el salario.");
    } catch (const out_of_range& e) {
        throw runtime_error("El salario ingresado es demasiado grande.");
    }

    return salario;
}

// Men� principal de N�minas
void Nominas::menuNominas() {
    int opcion;
    do {
        cargarEmpleados();
        limpiarPantalla();
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== MEN� DE N�MINAS =====";
        cout << "\n1. Crear Empleado";
        cout << "\n2. Borrar Empleado";
        cout << "\n3. Buscar Empleado";
        cout << "\n4. Modificar Empleado";
        cout << "\n5. Despliegue de Empleados";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore(); // Limpieza para uso de getline (buffer)

        switch (opcion) {
            case 1: crearEmpleado(); break;
            case 2: borrarEmpleado(); break;
            case 3: buscarEmpleado(); break;
            case 4: modificarEmpleado(); break;
            case 5: desplegarEmpleados(); break;
            case 6: limpiarPantalla(); return;
            default: cout << "\nOpci�n inv�lida."; pausar(); break;
        }
    } while (true);
}

// Crear y registar un nuevo empleado
void Nominas::crearEmpleado() {
    limpiarPantalla();
    EmpleadoNomina e;

    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Crear Empleado ===";
    cout << "\nNombre: "; getline(cin, e.nombre);
    cout << "Tel�fono: "; getline(cin, e.telefono);
    cout << "C�digo: "; getline(cin, e.codigo);
    cout << "Direcci�n: "; getline(cin, e.direccion);

    bool valido = false;
    while (!valido) {
        try {
            e.salario = leerSalario();
            valido = true;
        } catch (const runtime_error& ex) {
            cout << ex.what() << endl;
            cout << "Intente de nuevo.\n";
        }
    }

    empleados.push_back(e);
    ordenarEmpleados();
    guardarEmpleados();

    bitacoralogNominas.insertar(usuario, 4001, "Nominas", "Crear empleado");
    cout << "\nEmpleado agregado correctamente.";
    pausar();
}


// Borra un empleado existente
void Nominas::borrarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Borrar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "C�digo: "; getline(cin, codigo);

    bool eliminado = false;
    vector<EmpleadoNomina> nuevaLista;

    for (const auto& e : empleados) {
        if (e.nombre != nombre || e.codigo != codigo) {
            nuevaLista.push_back(e);//Mantiene si no coincide
        } else {
            eliminado = true;//se elimina
        }
    }

    if (eliminado) {
        empleados = nuevaLista;
        guardarEmpleados();
        bitacoralogNominas.insertar(usuario, 4002, "Nominas", "Eliminar empleado");
        cout << "\nEmpleado eliminado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Busca un empleado por nombre y c�digo
void Nominas::buscarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Buscar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "C�digo: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nEmpleado encontrado:";
            cout << "\nNombre    : " << e.nombre;
            cout << "\nTel�fono  : " << e.telefono;
            cout << "\nC�digo    : " << e.codigo;
            cout << "\nDirecci�n : " << e.direccion;
            cout << "\nSalario   : " << Moneda::getSimbolo()
                 << Moneda::convertirDesdeGtq(e.salario);
            encontrado = true;
            bitacoralogNominas.insertar(usuario, 4003, "Nominas", "Buscar empleado");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Modifica los datos de un empleado ya registrado
void Nominas::modificarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Modificar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "C�digo: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nIngrese nueva informaci�n:";
            cout << "\nNuevo Nombre: "; getline(cin, e.nombre);
            cout << "Nuevo Tel�fono: "; getline(cin, e.telefono);
            cout << "Nuevo C�digo: "; getline(cin, e.codigo);
            cout << "Nueva Direcci�n: "; getline(cin, e.direccion);
            cout << "Nuevo Salario (GTQ): Q"; cin >> e.salario;
            cin.ignore();
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarEmpleados();
        guardarEmpleados();
        bitacoralogNominas.insertar(usuario, 4004, "Nominas", "Modificar empleado");
        cout << "\nEmpleado modificado exitosamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Muestra todos los empleados registrados
void Nominas::desplegarEmpleados() {
    limpiarPantalla();
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Empleados Registrados ===\n";

    if (empleados.empty()) {
        cout << "\nNo hay empleados registrados.";
    } else {
        for (const auto& e : empleados) {
            cout << "\n-----------------------------";
            cout << "\nNombre    : " << e.nombre;
            cout << "\nTel�fono  : " << e.telefono;
            cout << "\nC�digo    : " << e.codigo;
            cout << "\nDirecci�n : " << e.direccion;
            cout << "\nSalario   : " << Moneda::getSimbolo()
                 << Moneda::convertirDesdeGtq(e.salario);
        }
        cout << "\n-----------------------------";
        bitacoralogNominas.insertar(usuario, 4005, "Nominas", "Ver empleados");
    }

    pausar();
}

