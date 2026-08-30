#ifndef CURSO_CPP
#define CURSO_CPP

#include <iostream>
#include <string>
#include "../modelo/Estudiante.cpp"

class Curso {
private:
    Estudiante* estudiantes;
    int tope;
    int capacidad;

public:
    // Constructor con capacidad por defecto de 20 estudiantes
    Curso(int capacidadMaxima = 20) {
        this->capacidad = capacidadMaxima;
        this->estudiantes = new Estudiante[capacidad];
        this->tope = 0;
    }

    // Destructor
    ~Curso() {
        delete[] estudiantes;
    }

    // Constructor de copia
    Curso(const Curso& otro) {
        this->capacidad = otro.capacidad;
        this->tope = otro.tope;
        this->estudiantes = new Estudiante[this->capacidad];
        for (int i = 0; i < this->tope; i++) {
            this->estudiantes[i] = otro.estudiantes[i];
        }
    }

    // Operador de asignacion
    Curso& operator=(const Curso& otro) {
        if (this != &otro) {
            delete[] this->estudiantes;
            this->capacidad = otro.capacidad;
            this->tope = otro.tope;
            this->estudiantes = new Estudiante[this->capacidad];
            for (int i = 0; i < this->tope; i++) {
                this->estudiantes[i] = otro.estudiantes[i];
            }
        }
        return *this;
    }

    // Insertar un nuevo estudiante en el curso
    bool insertar(Estudiante estudiante) {
        if (tope < capacidad) {
            estudiante.setId(tope + 1);
            estudiantes[tope] = estudiante;
            tope++;
            return true;
        }
        return false;
    }

    // Metodo de busqueda por cedula
    int buscar(const std::string& cedula) const {
        for (int i = 0; i < tope; i++) {
            if (estudiantes[i].getCedula() == cedula) {
                return i;
            }
        }
        return -1;
    }

    // Metodo de busqueda por autonumerico/id
    int buscarPorId(int id) const {
        for (int i = 0; i < tope; i++) {
            if (estudiantes[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    // Obtener estudiante por indice
    Estudiante* obtener(int indice) {
        if (indice >= 0 && indice < tope) {
            return &estudiantes[indice];
        }
        return nullptr;
    }

    // Metodo para eliminar por indice
    bool eliminar(int indice) {
        if (indice >= 0 && indice < tope) {
            for (int i = indice; i < tope - 1; i++) {
                estudiantes[i] = estudiantes[i + 1];
            }
            tope--;
            return true;
        }
        return false;
    }

    // Metodo para eliminar por id
    bool eliminarPorId(int id) {
        int indice = buscarPorId(id);
        if (indice != -1) {
            return eliminar(indice);
        }
        return false;
    }

    // Metodo para modificar por indice
    bool modificar(int indice, const Estudiante& nuevosDatos) {
        if (indice >= 0 && indice < tope) {
            int idActual = estudiantes[indice].getId();
            estudiantes[indice] = nuevosDatos;
            estudiantes[indice].setId(idActual);
            return true;
        }
        return false;
    }

    // Metodo para modificar por id
    bool modificarPorId(int id, const Estudiante& nuevosDatos) {
        int indice = buscarPorId(id);
        if (indice != -1) {
            return modificar(indice, nuevosDatos);
        }
        return false;
    }

    // Listar: devuelve copia de los estudiantes actuales
    Estudiante* listar() const {
        if (tope == 0) return nullptr;
        Estudiante* listaActual = new Estudiante[tope];
        for (int i = 0; i < tope; i++) {
            listaActual[i] = estudiantes[i];
        }
        return listaActual;
    }

    // Calcular promedio general del curso
    double calcularPromedioGeneral() const {
        if (tope == 0) return 0.0;

        double sumaPromedios = 0.0;
        int estudiantesConNotas = 0;
        for (int i = 0; i < tope; i++) {
            if (estudiantes[i].getCantidadNotas() > 0) {
                sumaPromedios += estudiantes[i].calcularPromedio();
                estudiantesConNotas++;
            }
        }
        if (estudiantesConNotas == 0) return 0.0;
        return sumaPromedios / estudiantesConNotas;
    }

    int getTope() const { return tope; }
    int getCapacidad() const { return capacidad; }
};

#endif // CURSO_CPP
