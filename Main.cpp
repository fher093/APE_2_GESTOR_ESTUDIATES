/*
    Main.cpp
    Punto de entrada del programa. Contiene el menu principal
    y crea la instancia del gestor que maneja todo lo demas.
    Las clases Estudiante y GestorEstudiante viven en sus .h
*/

#include <iostream>
#include "Estudiante.h"
#include "GestorEstudiante.h"

using namespace std;

int main() {

    // unica instancia del gestor, vive durante todo el programa
    // el vector de estudiantes esta adentro de esta clase
    GestorEstudiante gestor;

    int opcion;

    do {
        // menu principal tal como lo pide el enunciado
        cout << "\n=== GESTOR DE PERSONAS ===" << endl;
        cout << "1. Estudiantes" << endl;
        cout << "2. Registro de calificaciones" << endl;
        cout << "3. Determinar el promedio de notas de un estudiante" << endl;
        cout << "4. Determinar el promedio de notas del curso" << endl;
        cout << "0. Salir" << endl;
        cout << "Teclee su opcion (0-4): ";

        // lectura directa del entero (el gestor maneja su propia
        // lectura interna, aqui solo se necesita el numero del menu)
        cin >> opcion;
        cin.ignore();  // limpia el salto de linea que deja cin >>

        switch (opcion) {
            case 1:
                // submenu completo: listar, insertar, modificar, eliminar
                gestor.menuEstudiantes();
                break;

            case 2:
                // busca por cedula y permite gestionar las notas
                gestor.menuCalificaciones();
                break;

            case 3:
                // busca por cedula y muestra el promedio de ese estudiante
                gestor.promedioEstudiante();
                break;

            case 4:
                // calcula el promedio general de todo el curso
                gestor.promedioCurso();
                break;

            case 0:
                cout << "Hasta luego." << endl;
                break;

            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}
