//Programado por Priscila Sarai Guzm�n Calgua 9959-23-450
#ifndef USUARIO_H
#define USUARIO_H
#include "Bitacora.h"

#include <string>
using namespace std;
class Usuario {
private:
    string nombreUsuario;  // Almacena el nombre de usuario
    string contrasena;     // Almacena la contrase�a del usuario
    static const std::string ARCHIVO_LOGIN; // Declaraci�n

public:
    // Constructor por defecto
    // Inicializa el nombre de usuario y la contrase�a como cadenas vac�as
    Usuario();

    // Constructor con par�metros
    // Inicializa el nombre de usuario y la contrase�a con los valores proporcionados
    Usuario(const string& usuario, const std::string& contrasena);

    // M�todo para obtener el nombre de usuario
    // Devuelve el nombre del usuario
    string getNombreUsuario() const;

    // M�todo para obtener la contrase�a
    // Devuelve la contrase�a del usuario
    string getContrasena() const;

    // M�todo para establecer (modificar) el nombre de usuario
    // Recibe un nuevo nombre de usuario y lo asigna
    void setNombreUsuario(const string& usuario);

    // M�todo para establecer (modificar) la contrase�a
    // Recibe una nueva contrase�a y la asigna
    void setContrasena(const string& contrasena);

    // M�todo que verifica si el nombre de usuario y la contrase�a proporcionados son correctos
    // Compara los valores proporcionados con los almacenados en el objeto
    bool autenticar(const string& usuario, const string& contrasena) const;

    // M�todos est�ticos para control de acceso (no dependen de un objeto)

    // Inicia sesi�n verificando los datos desde el archivo "login.txt"
    // Retorna true si la autenticaci�n es exitosa, de lo contrario false
    static bool iniciarSesion();

    // Registra un nuevo usuario en el archivo "login.txt"
    // Recibe el nombre de usuario y la contrase�a y los guarda en el archivo
    // Retorna true si el registro es exitoso, de lo contrario false
    static bool registrarUsuario();

    // Muestra el men� de autenticaci�n (iniciar sesi�n o registrar nuevo usuario)
    // Devuelve true si se inicia sesi�n correctamente, false si se cancela
    static bool menuAutenticacion(string& usuarioAutenticado);

    // M�todo para hacer una pausa y esperar que el usuario presione Enter para continuar
    // Esto ayuda a hacer la interfaz m�s interactiva
    static void pausar();
    static void limpiarPantalla();

    // Funci�n para autenticar desde el archivo
    static bool autenticarDesdeArchivo(string& usuarioAutenticado);


};

#endif

