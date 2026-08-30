#include <iostream>
#include <string>
#include "Estudiante.h"

namespace negocio {

    class Curso {
    private:
        Estudiante* estudiantes; // Puntero para el arreglo dinámico
        int tope;
        int capacidad; 

        // Método buscar con id solo para eliminar y modificar
        int buscarPorId(int id) {
            for (int i = 0; i < tope; i++) {
                if (estudiantes[i].getId() == id) {
                    return i;
                }
            }
            return -1;
        }

    public:
        // Constructor
        Curso(int capacidadMaxima) {
            this->capacidad = capacidadMaxima;
            this->estudiantes = new Estudiante[capacidad];
            this->tope = 0;
        }

        ~Curso() {
            delete[] estudiantes;
        }

        bool insertar(Estudiante estudiante) {
            if (tope < capacidad) {
                estudiantes[tope] = estudiante;
                tope++;
                return true;
            }
            return false;
        }

        // Método de búsqueda con cédula
        int buscar(std::string cedula) {
            for (int i = 0; i < tope; i++) {
               
                if (estudiantes[i].getCedula() == cedula) { 
                    return i;
                }
            }
            return -1;
        }

        // Método para eliminar
        bool eliminar(int id) {
            int indice = buscarPorId(id);
            if (indice != -1) {
                for (int i = indice; i < tope - 1; i++) {
                    estudiantes[i] = estudiantes[i + 1];
                }

                tope--;
                return true;
            }
            return false;
        }

        // Método modificar
        bool modificar(int id, Estudiante nuevosDatos) {
            int indice = buscarPorId(id);
            if (indice != -1) {
                estudiantes[indice] = nuevosDatos;
                return true;
            }
            return false;
        }

        // Listar
        Estudiante* listar() {
            Estudiante* listaActual = new Estudiante[tope];
            for (int i = 0; i < tope; i++) {
                listaActual[i] = estudiantes[i];
            }
            return listaActual; 
        }

        double calcularPromedioGeneral() {
            if (tope == 0) return 0.0;

            double sumarPromedio = 0.0;
            for (int i = 0; i < tope; i++) {
                
                sumarPromedio += estudiantes[i].getNota(); 
            }
            return sumarPromedio / tope;
        }
    };

} 