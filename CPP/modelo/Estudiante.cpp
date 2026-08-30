#ifndef ESTUDIANTE_CPP
#define ESTUDIANTE_CPP

#include <iostream>
#include <string>
#include <ctime>

struct Fecha {
    int dia;
    int mes;
    int anio;
};

class Estudiante {
private:
    std::string nombres;
    std::string apellidos;
    std::string cedula;
    double notas[7]; // Vector[7] 
    Fecha fechaNacimiento;
    int Id;
    
    int cantidadNotas; // Control interno del vector

public:
    // Constructor por defecto 
    Estudiante() {
        this->cantidadNotas = 0;
        this->Id = 0;
        for(int i = 0; i < 7; i++) {
            this->notas[i] = 0.0;
        }
    }

    // Constructor principal
    Estudiante(std::string cedula, std::string nombres, std::string apellidos, Fecha fechaNacimiento) {
        this->cedula = cedula;
        this->nombres = nombres;
        this->apellidos = apellidos;
        this->fechaNacimiento = fechaNacimiento;
        this->cantidadNotas = 0;
        this->Id = 0;
        for(int i = 0; i < 7; i++) {
            this->notas[i] = 0.0;
        }
    }

    bool ingresarNota(double nota) {
        if (cantidadNotas < 7) {
            notas[cantidadNotas] = nota;
            cantidadNotas++;
            return true;
        }
        return false;
    }

    bool modificarNota(int indice, double nuevaNota) {
        if (indice >= 0 && indice < cantidadNotas) {
            notas[indice] = nuevaNota;
            return true;
        }
        return false;
    }

    bool eliminarNota(int indice) {
        if (indice >= 0 && indice < cantidadNotas) {
            // Desplazamiento a la izquierda
            for (int i = indice; i < cantidadNotas - 1; i++) {
                notas[i] = notas[i + 1];
            }
            notas[cantidadNotas - 1] = 0.0;
            cantidadNotas--;
            return true;
        }
        return false;
    }
    //Calcular promedio 
    double calcularPromedio() const {
        if (cantidadNotas == 0) return 0.0;
        double suma = 0;
        for (int i = 0; i < cantidadNotas; i++) {
            suma += notas[i];
        }
        return suma / cantidadNotas;
    }
    //Calcular edad
    int calcularEdad() const {
        // Obtenemos la fecha actual del sistema
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        int anioActual = now->tm_year + 1900;
        int mesActual = now->tm_mon + 1;
        int diaActual = now->tm_mday;

        int edad = anioActual - fechaNacimiento.anio;
        
        // Ajustamos si aun no ha cumplido anios en el anio actual
        if (mesActual < fechaNacimiento.mes || 
           (mesActual == fechaNacimiento.mes && diaActual < fechaNacimiento.dia)) {
            edad--;
        }
        return edad;
    }

    bool modificar(std::string nuevosNombres, std::string nuevosApellidos, Fecha nuevaFecha) {
        if (!nuevosNombres.empty()) {
            this->nombres = nuevosNombres;
        }
        if (!nuevosApellidos.empty()) {
            this->apellidos = nuevosApellidos;
        }
        this->fechaNacimiento = nuevaFecha;
        return true; 
    }

    std::string getCedula() const { return cedula; }
    std::string getNombres() const { return nombres; }
    std::string getApellidos() const { return apellidos; }
    Fecha getFechaNacimiento() const { return fechaNacimiento; }
    
    // Retorna un puntero al inicio del arreglo de notas
    const double* getNotas() const { return notas; }
    int getCantidadNotas() const { return cantidadNotas; }
    
    int getId() const { return Id; }
    void setId(int idAsignado) { this->Id = idAsignado; }
};

#endif // ESTUDIANTE_CPP


