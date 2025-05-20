//Programado por Priscila Sarai Guzm�n Calgua 9959-23-450
#include "Usuario.h"
#include <iostream>
#include <fstream> //Librer�a para archivos de lectura o escritura
#include <conio.h>// Se usa _getch() para ocultar la contrase�a mientras se escribe
#include <cstdlib>
//Objeto global de tipo Botacora para registrar inicio de sesi�n
Bitacora bitacoralogUsuario;
using namespace std;

//Definici�n de la constante que representa el archivo de login
const string Usuario::ARCHIVO_LOGIN = "login.txt";
//Constructor por defecto
Usuario::Usuario() : nombreUsuario(""), contrasena("") {} //Inicializa las variables de nombre de usuario y contrase�a como vac�as
//Inicializa el nombre usuario y contrase�a
Usuario::Usuario(const string& usuario, const string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

//M�todo para obtener el nombre del usuario
string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}
//M�todo para obtener la contrase�a
string Usuario::getContrasena() const {
    return contrasena;
}
//M�todo para crear un nuevo usuario
void Usuario::setNombreUsuario(const string& usuario) {
    nombreUsuario = usuario;
}
//para crear una nueva contrase�a
void Usuario::setContrasena(const string& contrasena) {
    this->contrasena = contrasena;
}

void Usuario::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Funci�n para leer la contrae�a de forma oculta
string leerContrasenaOculta() {
    string contrasena;//Variable que almacena la contrae�a
    char tecla;//Variable para almacenar cada tecla
    while (true) {
        tecla = _getch();//Leee la tecla sin mostrarla
        if (tecla == 13) break;//Si da enter se termina la lectura
        else if (tecla == 8 && !contrasena.empty()) { //si la contrase�a no esta vac�a y si es retroceso
            contrasena.pop_back();//Elimina el ultimo caracter de la contrase�a
            cout << "\b \b";//Borra el caracter en pantalla (retroceso)
        } else if (tecla != 8 && tecla != 13) {
            contrasena += tecla;
            cout << '*';
        }
    }
    cout << endl;
    return contrasena;//Devuelve la contrase�a oculta
}
// M�todo para autenticar al usuario comparando el nombre de usuario y la contrase�a ingresada
bool Usuario::autenticar(const string& usuario, const string& contrasena) const {
    return (this->nombreUsuario == usuario && this->contrasena == contrasena);
}
// M�todo para autenticar al usuario desde un archivo de texto (login.txt)
bool Usuario::autenticarDesdeArchivo(string& usuarioAutenticado) {
    limpiarPantalla();
    string usuarioIngresado, contrasenaIngresada;
    int intentos = 3;
 // Bucle que se ejecuta mientras haya intentos disponibles
    while (intentos > 0) {
        cout << "\n========== INICIO DE SESION ==========";
        cout << "\nUsuario: ";
        cin >> usuarioIngresado;
        cout << "Contrase�a: ";
        contrasenaIngresada = leerContrasenaOculta();

        ifstream archivo("login.txt");//Abre el archivo de login.txt para leer los usuarios registrados
        if (!archivo.is_open()) {
            cout << "\nError al abrir el archivo login.txt\n";
            return false;
        }

        string user, pass;
// Bucle que recorre todos los usuarios y contrase�as del archivo
        while (archivo >> user >> pass) {
            Usuario usuario(user, pass); // Crea un objeto Usuario con los datos del archivo
            if (usuario.autenticar(usuarioIngresado, contrasenaIngresada)) { // Si coinciden
                usuarioAutenticado = usuarioIngresado; // Guarda el nombre del usuario autenticado
                cout << "\nInicio de sesi�n exitoso.\n";
                archivo.close(); // Cierra el archivo
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
//M�todo para registrar un nuevo usuario en el archivo de login.txt
string Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n========== REGISTRO DE NUEVO USUARIO ==========";
    cout << "\nIngrese nombre de usuario: ";
    cin >> nuevoUsuario;
    cout << "Ingrese contrase�a: ";
    nuevaContrasena = leerContrasenaOculta();

    ofstream archivo("login.txt", ios::app); // Abre el archivo login.txt en modo "append" para agregar un nuevo usuario
    if (!archivo.is_open()) {
        cout << "\nError al abrir el archivo login.txt para escribir.\n";
        return "";
    }

    // Escribe el nuevo usuario y su contrase�a en el archivo
    archivo << nuevoUsuario << " " << nuevaContrasena << endl;
    archivo.close();
    cout << "\nUsuario registrado con �xito.\n";
    cout << "\nPresione Enter para continuar";
    cin.ignore();
    cin.get();
    limpiarPantalla();
    return nuevoUsuario;
}

void Usuario::setUsuario(const string& u) {
    usuario = u;
}

// Men� de autenticaci�n que permite al usuario elegir entre iniciar sesi�n, registrarse o salir
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

            case 2:
            {
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
