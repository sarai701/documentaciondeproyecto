//Karla Patricia Ruiz Ordo�ez 9959-24-6859
#include "Cuentas.h" // Incluye el encabezado de la clase Cuentas.
#include <iostream>  // Incluye la biblioteca est�ndar de entrada/salida.

Bitacora bitacoralogCuentas; // Inicializa una instancia est�tica de Bitacora.

using namespace std; // Permite usar elementos del espacio de nombres std sin prefijo.
void Cuentas::setUsuario(const string& u) {
    usuario = u;
}
Cuentas::Cuentas() { // Constructor de la clase Cuentas.
    tipoCuentaSeleccionada = "No configurada"; // Inicializa tipoCuentaSeleccionada con un valor por defecto.
}

void Cuentas::menuTipoCuenta(const string& bancoNombre) { // M�todo para mostrar el men� de tipos de cuenta.
    int opcion; // Variable para almacenar la opci�n seleccionada por el usuario.
    do {
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== TIPO DE CUENTA =====\n"; // Imprime el encabezado del men�.
        cout << "--------------------------------------\n"; // L�nea divisoria.
        cout << " Banco:    " << bancoNombre << "\n"; // Muestra el nombre del banco.
        cout << "--------------------------------------\n"; // L�nea divisoria.
        cout << "\n1. Cuenta Corriente"; // Opci�n 1 del men�.
        cout << "\n2. Cuenta de Ahorro"; // Opci�n 2 del men�.
        cout << "\nSeleccione una opci�n: "; // Solicita al usuario que seleccione una opci�n.
        cin >> opcion; // Lee la opci�n ingresada por el usuario.
        cin.ignore(); // Ignora el car�cter de nueva l�nea dejado en el buffer.

        switch (opcion) { // Estructura de control para manejar la opci�n seleccionada.
            case 1: // Si la opci�n es 1.
                tipoCuentaSeleccionada = "Corriente"; // Establece tipoCuentaSeleccionada a "Corriente".
                bitacoralogCuentas.insertar(usuario, 4610, "Cuentas", "Cuenta Corriente"); // Registra la selecci�n en la bit�cora.
                return; // Sale del m�todo.
            case 2: // Si la opci�n es 2.
                tipoCuentaSeleccionada = "Ahorro"; // Establece tipoCuentaSeleccionada a "Ahorro".
                bitacoralogCuentas.insertar(usuario, 4611, "Cuentas", "Cuenta de Ahorro"); // Registra la selecci�n en la bit�cora.
                return; // Sale del m�todo.
            default: // Si la opci�n no es v�lida.
                cout << "Opci�n inv�lida.\n"; // Informa al usuario que la opci�n es inv�lida.
                break; // Contin�a el ciclo.
        }
    } while (true); // Repite el ciclo hasta que se seleccione una opci�n v�lida.
}

string Cuentas::getTipoCuenta() const { // M�todo para obtener el tipo de cuenta seleccionada.
    return tipoCuentaSeleccionada; // Devuelve el tipo de cuenta seleccionada.
}
