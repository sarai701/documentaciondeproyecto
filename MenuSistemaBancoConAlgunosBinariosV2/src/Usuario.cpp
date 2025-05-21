// Programado por Priscila Sarai Guzm�n Calgua 9959-23-450

#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <conio.h> // Para _getch()
#include <cstring> // Para strcpy, strcmp
#include <cstdlib> // Para system()

using namespace std;

// Objeto global de bit�cora para registrar actividades de login
Bitacora bitacoralogUsuario;

// Definici�n del archivo binario de login
const string Usuario::ARCHIVO_LOGIN = "login.dat";

// Constructor por defecto
Usuario::Usuario() : nombreUsuario(""), contrasena("") {}

// Constructor con par�metros
Usuario::Usuario(const string& usuario, const string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

// Devuelve el nombre de usuario
string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}

// Devuelve la contrase�a
string Usuario::getContrasena() const {
    return contrasena;
}

// Establece el nombre de usuario
void Usuario::setNombreUsuario(const string& usuario) {
    nombreUsuario = usuario;
}

// Establece la contrase�a
void Usuario::setContrasena(const string& contrasena) {
    this->contrasena = contrasena;
}

// Establece el nombre del usuario autenticado (para bit�cora)
void Usuario::setUsuario(const string& u) {
    usuario = u;
}

// Limpia la pantalla seg�n el sistema operativo
void Usuario::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Funci�n para ocultar la contrase�a mientras se escribe
string leerContrasenaOculta() {
    string contrasena;
    char tecla;
    while (true) {
        tecla = _getch();
        if (tecla == 13) break; // Enter
        else if (tecla == 8 && !contrasena.empty()) {
            contrasena.pop_back();
            cout << "\b \b"; // Borrar car�cter en pantalla
        } else if (tecla != 8 && tecla != 13) {
            contrasena += tecla;
            cout << '*';
        }
    }
    cout << endl;
    return contrasena;
}

// Autenticaci�n directa (comparaci�n interna)
bool Usuario::autenticar(const string& usuario, const string& contrasena) const {
    return (this->nombreUsuario == usuario && this->contrasena == contrasena);
}

// Verifica usuario/contrase�a desde el archivo binario login.dat
bool Usuario::autenticarDesdeArchivo(string& usuarioAutenticado) {
    limpiarPantalla();
    string usuarioIngresado, contrasenaIngresada;
    int intentos = 3;

    while (intentos > 0) {
        cout << "\n========== INICIO DE SESION ==========";
        cout << "\nUsuario: ";
        cin >> usuarioIngresado;
        cout << "Contrase�a: ";
        contrasenaIngresada = leerContrasenaOculta();

        ifstream archivo(ARCHIVO_LOGIN, ios::binary);
        if (!archivo.is_open()) {
            cout << "\nError al abrir el archivo " << ARCHIVO_LOGIN << "\n";
            return false;
        }

        RegistroUsuario reg;
        // Recorre todos los registros del archivo
        while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(RegistroUsuario))) {
            if (usuarioIngresado == reg.nombreUsuario && contrasenaIngresada == reg.contrasena) {
                usuarioAutenticado = usuarioIngresado;
                cout << "\nInicio de sesi�n exitoso.\n";
                archivo.close();
                cout << "\nPresione una tecla para continuar";
                cin.ignore();
                cin.get();
                limpiarPantalla();
                return true;
            }
        }

        archivo.close();
        intentos--;
        cout << "\nUsuario o contrase�a incorrectos. Intentos restantes: " << intentos << endl;
    }

    cout << "\nDemasiados intentos fallidos. Acceso denegado.\n";
    return false;
}

// Registra un nuevo usuario en el archivo binario login.dat
string Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n========== REGISTRO DE NUEVO USUARIO ==========";
    cout << "\nIngrese nombre de usuario: ";
    cin >> nuevoUsuario;
    cout << "Ingrese contrase�a: ";
    nuevaContrasena = leerContrasenaOculta();

    // Crear estructura con datos de longitud fija
    RegistroUsuario reg;
    strncpy(reg.nombreUsuario, nuevoUsuario.c_str(), sizeof(reg.nombreUsuario));
    reg.nombreUsuario[sizeof(reg.nombreUsuario) - 1] = '\0'; // Seguridad
    strncpy(reg.contrasena, nuevaContrasena.c_str(), sizeof(reg.contrasena));
    reg.contrasena[sizeof(reg.contrasena) - 1] = '\0';

    ofstream archivo(ARCHIVO_LOGIN, ios::binary | ios::app);
    if (!archivo.is_open()) {
        cout << "\nError al abrir el archivo " << ARCHIVO_LOGIN << " para escritura.\n";
        return "";
    }

    archivo.write(reinterpret_cast<const char*>(&reg), sizeof(RegistroUsuario));
    archivo.close();

    cout << "\nUsuario registrado con �xito.\n";
    cout << "\nPresione Enter para continuar";
    cin.ignore();
    cin.get();
    limpiarPantalla();

    return nuevoUsuario;
}

// Pausa para permitir que el usuario lea un mensaje antes de continuar
void Usuario::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Muestra men� de autenticaci�n (inicio de sesi�n o registro)
bool Usuario::menuAutenticacion(string& usuarioAutenticado) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== SISTEMA DE ACCESO =====";
        cout << "\n1. Iniciar sesi�n";
        cout << "\n2. Registrar nuevo usuario";
        cout << "\n3. Salir";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                if (autenticarDesdeArchivo(usuarioAutenticado)) {
                    bitacoralogUsuario.insertar(usuarioAutenticado, 1000, "Usuario", "Inicio de sesi�n exitoso");
                    return true;
                }
                bitacoralogUsuario.insertar("Desconocido", 4902, "Usuario", "Intento de inicio de sesi�n fallido");
                break;

            case 2: {
                string nuevoUsuario = registrarUsuario();
                if (!nuevoUsuario.empty()) {
                    bitacoralogUsuario.insertar(nuevoUsuario, 1001, "Usuario", "Registro de nuevo usuario");
                }
                break;
            }

            case 3:
                cout << "\nSaliendo...\n";
                return false;

            default:
                cout << "\nOpci�n no v�lida.\n";
                break;
        }
    } while (true);

    return false;
}
