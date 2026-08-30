#ifndef CURSO_CPP
#define CURSO_CPP

#include <optional>
#include <string>
#include "../modelo/Estudiante.cpp"

class Curso {
public:
    static const int CAPACIDAD_MAXIMA = 20;

private:
    Estudiante* estudiantes;
    int tope;
    int capacidad;

public:
    Curso(int capacidadMaxima = CAPACIDAD_MAXIMA) {
        this->capacidad = capacidadMaxima;
        this->estudiantes = new Estudiante[capacidadMaxima];
        this->tope = 0;
    }

    ~Curso() {
        delete[] estudiantes;
    }

    Curso(const Curso& otro) {
        this->capacidad = otro.capacidad;
        this->tope = otro.tope;
        this->estudiantes = new Estudiante[this->capacidad];
        for (int i = 0; i < this->tope; i++) {
            this->estudiantes[i] = otro.estudiantes[i];
        }
    }

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

    bool insertar(const Estudiante& estudiante) {
        if (tope >= capacidad) {
            return false;
        }
        if (estudiante.getCedula().empty()) {
            return false;
        }
        if (buscar(estudiante.getCedula()) != -1) {
            return false;
        }
        estudiantes[tope] = estudiante;
        tope++;
        return true;
    }

    int buscar(const std::string& cedula) const {
        if (cedula.empty()) {
            return -1;
        }
        for (int i = 0; i < tope; i++) {
            if (estudiantes[i].getCedula() == cedula) {
                return i;
            }
        }
        return -1;
    }

    Estudiante* obtener(int indice) {
        if (indice < 0 || indice >= tope) {
            return nullptr;
        }
        return &estudiantes[indice];
    }

    bool eliminar(int indice) {
        if (indice < 0 || indice >= tope) {
            return false;
        }
        for (int i = indice; i < tope - 1; i++) {
            estudiantes[i] = estudiantes[i + 1];
        }
        tope--;
        estudiantes[tope] = Estudiante();
        return true;
    }

    bool modificar(int indice, const Estudiante& nuevosDatos) {
        if (indice < 0 || indice >= tope) {
            return false;
        }
        int existente = buscar(nuevosDatos.getCedula());
        if (existente != -1 && existente != indice) {
            return false;
        }
        estudiantes[indice].setCedula(nuevosDatos.getCedula());
        estudiantes[indice].setNombres(nuevosDatos.getNombres());
        estudiantes[indice].setApellidos(nuevosDatos.getApellidos());
        estudiantes[indice].setFechaNacimiento(nuevosDatos.getFechaNacimientoTexto());
        return true;
    }

    Estudiante* listar() {
        return estudiantes;
    }

    std::optional<double> calcularPromedioGeneral() const {
        if (tope == 0) {
            return std::nullopt;
        }
        double sumaPromedios = 0.0;
        int estudiantesConNotas = 0;
        for (int i = 0; i < tope; i++) {
            if (estudiantes[i].tieneCalificaciones()) {
                sumaPromedios += estudiantes[i].calcularPromedio();
                estudiantesConNotas++;
            }
        }
        if (estudiantesConNotas == 0) {
            return std::nullopt;
        }
        return sumaPromedios / estudiantesConNotas;
    }

    int getTope() const {
        return tope;
    }

    int getCapacidad() const {
        return capacidad;
    }
};

#endif
