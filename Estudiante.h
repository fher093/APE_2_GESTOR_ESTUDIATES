#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Clase: Estudiante
// Para que sirve: representa a un solo estudiante dentro del
// sistema. Guarda sus datos personales y sus calificaciones

class Estudiante {

private:
    // datos personales del estudiante
    string cedula;
    string nombres;
    string apellidos;
    string fechaNacimiento; 

    // vector de notas, maximo 7 entradas
    // se usa vector porque la cantidad de notas puede ir
    // creciendo de a poco (no siempre se ingresan todas de una)
    vector<float> notas;

    // constante que define cuantas notas se permiten como maximo
    static const int MAX_NOTAS = 7;

public:

    // Constructor por defecto
    // Se usa cuando se crea un objeto vacio antes de llenarlo
    Estudiante() {
        cedula        = "";
        nombres       = "";
        apellidos     = "";
        fechaNacimiento = "";
        // el vector empieza vacio, sin notas
    }

    // Constructor con parametros
    // Se usa cuando ya se tienen todos los datos del estudiante
    // y se quiere crear el objeto de una sola vez
    Estudiante(string ced, string nom, string ape, string fNac) {
        cedula          = ced;
        nombres         = nom;
        apellidos       = ape;
        fechaNacimiento = fNac;
        // el vector de notas empieza vacio igual
    }

    // Getters (accesores): permiten leer los atributos privados
    // desde fuera de la clase sin romper el encapsulamiento
    string getCedula()          { return cedula; }
    string getNombres()         { return nombres; }
    string getApellidos()       { return apellidos; }
    string getFechaNacimiento() { return fechaNacimiento; }

    // devuelve una copia del vector de notas completo
    // util para recorrerlo desde afuera sin modificar el original
    vector<float> getNotas() { return notas; }

    // Setters (mutadores): permiten modificar los datos del
    // estudiante desde fuera de la clase

    void setCedula(string ced)              { cedula = ced; }
    void setNombres(string nom)             { nombres = nom; }
    void setApellidos(string ape)           { apellidos = ape; }
    void setFechaNacimiento(string fNac)    { fechaNacimiento = fNac; }

    // agregarNota()
    // Agrega una calificacion al vector solo si no se llego al
    // maximo. Devuelve true si se agrego, false si ya esta lleno.
    bool agregarNota(float nota) {
        // size() devuelve cuantos elementos hay ahorita en el vector
        if ((int)notas.size() < MAX_NOTAS) {
            notas.push_back(nota);  // push_back agrega al final del vector
            return true;
        }
        return false;  // ya no caben mas notas
    }

    // modificarNota()
    // Cambia el valor de una nota segun su posicion (indice).
    // El indice viene desde fuera y puede ser invalido, por eso
    // se valida antes de hacer el cambio.
    
    bool modificarNota(int indice, float nuevaNota) {
        // se verifica que el indice este dentro del rango valido
        if (indice >= 0 && indice < (int)notas.size()) {
            notas[indice] = nuevaNota;  // acceso directo por posicion
            return true;
        }
        return false;
    }

    // eliminarNota()
    // Borra una nota segun su posicion usando el iterador del vector.
    // erase() necesita un iterador, por eso se usa begin() + indice
    // para apuntar a la posicion correcta.
    
	    bool eliminarNota(int indice) {
        if (indice >= 0 && indice < (int)notas.size()) {
            // begin() apunta al inicio del vector
            // sumandole el indice llegamos a la posicion exacta
            notas.erase(notas.begin() + indice);
            return true;
        }
        return false;
    }

    // calcularPromedio()
    // Recorre el vector de notas sumando todos los valores y
    // divide entre la cantidad de notas. Estructura tipica de
    // recorrido de vector con for clasico.
    // Si no hay notas devuelve 0.0.

    float calcularPromedio() {
        if (notas.empty()) return 0.0;  // empty() es true si no hay elementos

        float suma = 0.0;
        // recorrido clasico con indice, igual que arrays normales
        for (int i = 0; i < (int)notas.size(); i++) {
            suma += notas[i];
        }
        return suma / notas.size();
    }

    // notasLlenas()
    // Dice si ya se alcanzo el maximo de notas permitidas.
    // Se usa para bloquear el ingreso de mas calificaciones.

    bool notasLlenas() {
        return (int)notas.size() >= MAX_NOTAS;
    }

    // tieneNotas()
    // Dice si el estudiante tiene al menos una nota registrada.

    bool tieneNotas() {
        return !notas.empty();
    }

    // mostrarDatos()
    // Imprime en consola los datos del estudiante de forma
    // legible. Se llama desde GestorEstudiante para listar.
    
    void mostrarDatos() {
        cout << "Cedula         : " << cedula << endl;
        cout << "Nombres        : " << nombres << endl;
        cout << "Apellidos      : " << apellidos << endl;
        cout << "Fecha de nac.  : " << fechaNacimiento << endl;
    }

    // mostrarNotas()

    void mostrarNotas() {
        if (notas.empty()) {
            cout << "  (no hay notas registradas)" << endl;
            return;
        }
        for (int i = 0; i < (int)notas.size(); i++) {
            // i+1 para que el usuario vea desde 1 en lugar de 0
            cout << "  " << (i + 1) << ". " << notas[i] << endl;
        }
    }

};  

#endif 
