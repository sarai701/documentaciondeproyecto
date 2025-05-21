// Programado por Priscila Sarai Guzm�n Calgua 9959-23-450
#ifndef USUARIO_H
#define USUARIO_H

#include "Bitacora.h"
#include <string>
using namespace std;

// Estructura fija para el almacenamiento binario de usuarios
struct RegistroUsuario {
    char nombreUsuario[30];
    char contrasena[30];
};

class Usuario {
private:
    string usuario;               // Usuario autenticado (para bit�cora)
    string nombreUsuario;         // Almacena el nombre de usuario
    string contrasena;            // Almacena la contrase�a del usuario
    static const string ARCHIVO_LOGIN; // Nombre del archivo binario login.dat

public:
    void setUsuario(const string& u); // Establece el usuario autenticado (bit�cora)

    // Constructor por defecto
    Usuario();

    // Constructor con par�metros
    Usuario(const string& usuario, const string& contrasena);

    // Obtiene el nombre del usuario
    string getNombreUsuario() const;

    // Obtiene la contrase�a del usuario
    string getContrasena() const;

    // Establece/modifica el nombre de usuario
    void setNombreUsuario(const string& usuario);

    // Establece/modifica la contrase�a
    void setContrasena(const string& contrasena);

    // Verifica si usuario y contrase�a coinciden con los almacenados en el objeto
    bool autenticar(const string& usuario, const string& contrasena) const;

    // Autenticaci�n directa desde archivo binario login.dat
    bool autenticarDesdeArchivo(string& usuarioAutenticado);

    // Inicia sesi�n verificando desde archivo binario login.dat
    bool iniciarSesion();

    // Registra nuevo usuario en archivo binario login.dat
    string registrarUsuario();

    // Muestra men� de autenticaci�n
    bool menuAutenticacion(string& usuarioAutenticado);

    // Espera que el usuario presione Enter para continuar
    void pausar();

    // Limpia pantalla (multiplataforma)
    static void limpiarPantalla();
};

#endif
