//Programado por Priscila Sarai Guzm�n Calgua 9959-23-450
#ifndef NOMINAS_H
#define NOMINAS_H

#include <string>
#include <vector>
#include "Bitacora.h"
#include "Moneda.h"

using namespace std;

// Estructura que representa a un empleado en el m�dulo de N�minas
struct EmpleadoNomina {
    string nombre;
    string telefono;
    string codigo;
    string puesto;
    string direccion;
    double salario;
};

class Nominas {
private:
    vector<EmpleadoNomina> empleados;   // Lista en memoria de empleados
    string usuario;//bitacora
    void cargarEmpleados();             // Carga los datos desde empleados.txt
    void guardarEmpleados();            // Guarda todos los datos en empleados.txt
    void ordenarEmpleados();            // Ordena los empleados por c�digo
    void guardarNominas();
public:
    void setUsuario(const string& u);//bitacora

    void menuNominas();// Muestra el men� del m�dulo de N�minas
    void crearEmpleado();              // Agrega un nuevo empleado
    void borrarEmpleado();             // Elimina un empleado por c�digo
    void buscarEmpleado();             // Busca un empleado por c�digo
    void modificarEmpleado();          // Modifica un empleado existente
    void desplegarEmpleados();         // Muestra todos los empleados

    void limpiarPantalla();            // Limpia la consola
    void pausar();                     // Espera a que el usuario presione ENTER
};

#endif


