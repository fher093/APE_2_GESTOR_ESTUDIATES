#ifndef GESTORESTUDIANT_H
#define GESTORESTUDIANT_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>      // para limpiar el buffer de entrada
#include "Estudiante.h"

using namespace std;

class GestorEstudiante {

private:
    // vector principal de estudiantes, maximo 20
    vector<Estudiante> estudiantes;

    // tope maximo del curso
    static const int MAX_ESTUDIANTES = 20;

    // limpiarBuffer()
    void limpiarBuffer() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }



    float leerFloat(string mensaje) { //Lee un numero decimal del usuario con validacion basica.
        float valor;
        while (true) {
            cout << mensaje;
            if (cin >> valor) {
                limpiarBuffer();
                return valor;
            } else {
                cout << "  Dato invalido, ingresa un numero." << endl;
                cin.clear();
                limpiarBuffer();
            }
        }
    }


    int leerEntero(string mensaje) { // Igual que leerFloat pero para enteros.
        int valor;
        while (true) {
            cout << mensaje;
            if (cin >> valor) {
                limpiarBuffer();
                return valor;
            } else {
                cout << "  Dato invalido, ingresa un numero entero." << endl;
                cin.clear();
                limpiarBuffer();
            }
        }
    }


    string leerTexto(string mensaje) { // Lee una linea de texto completa (con espacios).
        string texto;
        cout << mensaje;
        getline(cin, texto);
        return texto;
    }

public:

    // constructor por defecto, el vector empieza vacio
    GestorEstudiante() {}


    int buscar(string cedula) {
        for (int i = 0; i < (int)estudiantes.size(); i++) {
            if (estudiantes[i].getCedula() == cedula) {
                return i;  // encontrado, devuelve su posicion
            }
        }
        return -1;  // no se encontro
    }


    // mostrarListado()
    // Imprime todos los estudiantes con su autonumerico (1, 2, 3...)
    void mostrarListado() {
        if (estudiantes.empty()) {
            cout << "  No hay estudiantes registrados." << endl;
            return;
        }
        cout << "\n--- LISTADO DE ESTUDIANTES ---" << endl;
        for (int i = 0; i < (int)estudiantes.size(); i++) {
            cout << "\n[" << (i + 1) << "] ";
            estudiantes[i].mostrarDatos();
        }
        cout << "------------------------------" << endl;
    }


    // Muestra el listado y da acceso al submenu 
    void menuEstudiantes() {
        int opcion;
        do {
            mostrarListado();

            cout << "\n-- SUBMENU ESTUDIANTES --" << endl;
            cout << "1. Insertar estudiante" << endl;
            cout << "2. Modificar estudiante" << endl;
            cout << "3. Eliminar estudiante" << endl;
            cout << "4. Volver al menu principal" << endl;
            opcion = leerEntero("Opcion: ");

            switch (opcion) {
                case 1: insertarEstudiante(); break;
                case 2: modificarEstudiante(); break;
                case 3: eliminarEstudiante(); break;
                case 4: cout << "Regresando al menu principal..." << endl; break;
                default: cout << "Opcion invalida." << endl;
            }

        } while (opcion != 4);
    }



    void insertarEstudiante() { 
        char repetir;
        do {
            // si ya hay 20 estudiantes no se puede agregar mas
            if ((int)estudiantes.size() >= MAX_ESTUDIANTES) {
                cout << "  El curso ya tiene el maximo de "
                     << MAX_ESTUDIANTES << " estudiantes." << endl;
                return;
            }

            cout << "\n-- NUEVO ESTUDIANTE --" << endl;
            string ced  = leerTexto("Cedula          : ");
            string nom  = leerTexto("Nombres         : ");
            string ape  = leerTexto("Apellidos       : ");
            string fNac = leerTexto("Fecha de nac.   : ");

            // se crea el objeto con el constructor parametrizado
            Estudiante nuevoEst(ced, nom, ape, fNac);

            // push_back agrega el objeto al final del vector
            estudiantes.push_back(nuevoEst);

            cout << "  Estudiante registrado correctamente." << endl;

            cout << "Deseas registrar otro estudiante? (s/n): ";
            cin >> repetir;
            limpiarBuffer();

        } while (repetir == 's' || repetir == 'S');
    }

    // modificarEstudiante()
    // El usuario indica el autonumerico del estudiante a editar.
    void modificarEstudiante() {
        if (estudiantes.empty()) {
            cout << "  No hay estudiantes para modificar." << endl;
            return;
        }

        mostrarListado();
        int num = leerEntero("Numero del estudiante a modificar: ");
        int indice = num - 1;  // el usuario ve desde 1, el vector desde 0

        // se valida que el numero ingresado sea valido
        if (indice < 0 || indice >= (int)estudiantes.size()) {
            cout << "  Numero invalido." << endl;
            return;
        }

        cout << "\n-- MODIFICAR DATOS (deja vacio para no cambiar) --" << endl;

        // usuario no escribe nada (deja el campo en blanco)
        string nuevo;

        nuevo = leerTexto("Nuevos nombres (actual: " + estudiantes[indice].getNombres() + "): ");
        if (!nuevo.empty()) estudiantes[indice].setNombres(nuevo);

        nuevo = leerTexto("Nuevos apellidos (actual: " + estudiantes[indice].getApellidos() + "): ");
        if (!nuevo.empty()) estudiantes[indice].setApellidos(nuevo);

        nuevo = leerTexto("Nueva fecha nac. (actual: " + estudiantes[indice].getFechaNacimiento() + "): ");
        if (!nuevo.empty()) estudiantes[indice].setFechaNacimiento(nuevo);

        cout << "  Datos actualizados correctamente." << endl;
    }

    // eliminarEstudiante()
    void eliminarEstudiante() {
        if (estudiantes.empty()) {
            cout << "  No hay estudiantes registrados para eliminar." << endl;
            return;
        }

        mostrarListado();
        int num = leerEntero("Numero del estudiante a eliminar: ");
        int indice = num - 1;

        if (indice < 0 || indice >= (int)estudiantes.size()) {
            cout << "  Numero invalido." << endl;
            return;
        }

        cout << "  Se eliminara a: "
             << estudiantes[indice].getNombres() << " "
             << estudiantes[indice].getApellidos() << endl;

        cout << "Confirmar eliminacion? (s/n): ";
        char conf;
        cin >> conf;
        limpiarBuffer();

        if (conf == 's' || conf == 'S') {

            // begin() es el inicio del vector, + indice llega al elemento
            estudiantes.erase(estudiantes.begin() + indice);
            cout << "  Estudiante eliminado." << endl;
        } else {
            cout << "  Eliminacion cancelada." << endl;
        }
    }


    void menuCalificaciones() {
        char seguir = 's';
        while (seguir == 's' || seguir == 'S') {
            string ced = leerTexto("\nIngresa la cedula del estudiante: ");

            // buscar() devuelve el indice o -1
            int indice = buscar(ced);

            if (indice == -1) {
                cout << "  No se encontro un estudiante con esa cedula." << endl;
                cout << "Deseas intentar con otra cedula? (s/n): ";
                cin >> seguir;
                limpiarBuffer();
                continue;
            }

            // se encontro, se muestran sus datos
            cout << "\n-- ESTUDIANTE ENCONTRADO --" << endl;
            estudiantes[indice].mostrarDatos();

            // submenu de calificaciones
            int opcion;
            do {
                cout << "\nCalificaciones actuales:" << endl;
                estudiantes[indice].mostrarNotas();

                if (estudiantes[indice].notasLlenas()) {
                    cout << "  Se han ingresado todas las calificaciones posibles (maximo 7)." << endl;
                    break;  
                }

                cout << "\n1. Agregar nota" << endl;
                cout << "2. Modificar nota" << endl;
                cout << "3. Eliminar nota" << endl;
                cout << "4. Terminar" << endl;
                opcion = leerEntero("Opcion: ");

                switch (opcion) {
                    case 1: {
                        float n = leerFloat("  Nueva nota: ");
                        if (estudiantes[indice].agregarNota(n))
                            cout << "  Nota agregada." << endl;
                        break;
                    }
                    case 2: {
                        int pos = leerEntero("  Numero de nota a modificar: ") - 1;
                        float n = leerFloat("  Nuevo valor: ");
                        if (!estudiantes[indice].modificarNota(pos, n))
                            cout << "  Numero de nota invalido." << endl;
                        else
                            cout << "  Nota modificada." << endl;
                        break;
                    }
                    case 3: {
                        int pos = leerEntero("  Numero de nota a eliminar: ") - 1;
                        if (!estudiantes[indice].eliminarNota(pos))
                            cout << "  Numero de nota invalido." << endl;
                        else
                            cout << "  Nota eliminada." << endl;
                        break;
                    }
                    case 4: cout << "  Saliendo de calificaciones." << endl; break;
                    default: cout << "  Opcion invalida." << endl;
                }

            } while (opcion != 4 && !estudiantes[indice].notasLlenas());

            // se pregunta si quiere gestionar las notas de otro estudiante
            cout << "Deseas ingresar calificaciones de otro estudiante? (s/n): ";
            cin >> seguir;
            limpiarBuffer();
        }
    }

    void promedioEstudiante() {
        string ced = leerTexto("\nIngresa la cedula del estudiante: ");
        int indice = buscar(ced);

        if (indice == -1) {
            cout << "  No se encontro un estudiante con la cedula: " << ced << endl;
            return;
        }

        cout << "\n-- PROMEDIO DEL ESTUDIANTE --" << endl;
        cout << "Nombre     : " << estudiantes[indice].getNombres()
             << " " << estudiantes[indice].getApellidos() << endl;
        cout << "Fecha nac. : " << estudiantes[indice].getFechaNacimiento() << endl;

        if (!estudiantes[indice].tieneNotas()) {
            cout << "  No tiene calificaciones registradas aun." << endl;
        } else {
            cout << "Promedio   : " << estudiantes[indice].calcularPromedio() << endl;
        }
    }


    void promedioCurso() {
        cout << "\n-- PROMEDIO GENERAL DEL CURSO --" << endl;

        float sumaTotal = 0.0;
        int conteoConNotas = 0;  // solo se cuentan quienes tienen notas

        for (int i = 0; i < (int)estudiantes.size(); i++) {
            if (estudiantes[i].tieneNotas()) {
                sumaTotal += estudiantes[i].calcularPromedio();
                conteoConNotas++;
            }
        }

        if (conteoConNotas == 0) {
            cout << "  No se han registrado calificaciones de estudiantes." << endl;
        } else {
            cout << "  Promedio general: " << (sumaTotal / conteoConNotas) << endl;
            cout << "  (basado en " << conteoConNotas << " estudiante(s) con notas)" << endl;
        }
    }

};  

#endif 
