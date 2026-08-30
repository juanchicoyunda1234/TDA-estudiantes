#ifndef ESTUDIANTE_CPP
#define ESTUDIANTE_CPP

#include <string>
#include <ctime>
#include <stdexcept>

struct Fecha {
    int dia;
    int mes;
    int anio;
};

class Estudiante {
public:
    static const int MAX_CALIFICACIONES = 7;

private:
    std::string cedula;
    std::string nombres;
    std::string apellidos;
    Fecha fechaNacimiento;
    double calificaciones[MAX_CALIFICACIONES];
    int tope;

    static bool esNumero(const std::string& valor) {
        if (valor.empty()) {
            return false;
        }
        for (size_t i = 0; i < valor.size(); i++) {
            if (valor[i] < '0' || valor[i] > '9') {
                return false;
            }
        }
        return true;
    }

    static bool esCedulaValida(const std::string& valor) {
        return valor.size() == 10 && esNumero(valor);
    }

    static bool esTextoObligatorio(const std::string& valor) {
        if (valor.empty()) {
            return false;
        }
        for (size_t i = 0; i < valor.size(); i++) {
            char c = valor[i];
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                return true;
            }
        }
        return false;
    }

    static bool esBisiesto(int anio) {
        return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    }

    static bool esFechaValida(int dia, int mes, int anio) {
        if (anio < 1 || mes < 1 || mes > 12 || dia < 1) {
            return false;
        }
        int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (esBisiesto(anio)) {
            diasMes[2] = 29;
        }
        return dia <= diasMes[mes];
    }

    static Fecha fechaActual() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        Fecha fecha;
        fecha.dia = now->tm_mday;
        fecha.mes = now->tm_mon + 1;
        fecha.anio = now->tm_year + 1900;
        return fecha;
    }

    static bool esFechaFutura(const Fecha& fecha) {
        Fecha actual = fechaActual();
        if (fecha.anio != actual.anio) {
            return fecha.anio > actual.anio;
        }
        if (fecha.mes != actual.mes) {
            return fecha.mes > actual.mes;
        }
        return fecha.dia > actual.dia;
    }

    static Fecha parsearFecha(const std::string& texto) {
        if (texto.size() != 10 || texto[2] != '/' || texto[5] != '/') {
            throw std::invalid_argument("Fecha invalida, formato esperado dd/MM/yyyy");
        }
        std::string sDia = texto.substr(0, 2);
        std::string sMes = texto.substr(3, 2);
        std::string sAnio = texto.substr(6, 4);
        if (!esNumero(sDia) || !esNumero(sMes) || !esNumero(sAnio)) {
            throw std::invalid_argument("Fecha invalida, formato esperado dd/MM/yyyy");
        }
        Fecha fecha;
        fecha.dia = std::stoi(sDia);
        fecha.mes = std::stoi(sMes);
        fecha.anio = std::stoi(sAnio);
        if (!esFechaValida(fecha.dia, fecha.mes, fecha.anio)) {
            throw std::invalid_argument("Fecha invalida, formato esperado dd/MM/yyyy");
        }
        if (esFechaFutura(fecha)) {
            throw std::invalid_argument("La fecha de nacimiento no puede ser futura");
        }
        return fecha;
    }

    static std::string formatearFecha(const Fecha& fecha) {
        std::string dia = std::to_string(fecha.dia);
        std::string mes = std::to_string(fecha.mes);
        std::string anio = std::to_string(fecha.anio);
        if (dia.size() < 2) {
            dia = "0" + dia;
        }
        if (mes.size() < 2) {
            mes = "0" + mes;
        }
        while (anio.size() < 4) {
            anio = "0" + anio;
        }
        return dia + "/" + mes + "/" + anio;
    }

    void inicializarCalificaciones() {
        tope = 0;
        for (int i = 0; i < MAX_CALIFICACIONES; i++) {
            calificaciones[i] = 0.0;
        }
    }

public:
    Estudiante() {
        fechaNacimiento.dia = 0;
        fechaNacimiento.mes = 0;
        fechaNacimiento.anio = 0;
        inicializarCalificaciones();
    }

    Estudiante(std::string cedula, std::string nombres, std::string apellidos, std::string fechaNacimientoTexto) {
        inicializarCalificaciones();
        setCedula(cedula);
        setNombres(nombres);
        setApellidos(apellidos);
        setFechaNacimiento(fechaNacimientoTexto);
    }

    std::string getCedula() const {
        return cedula;
    }

    void setCedula(const std::string& cedula) {
        if (!esCedulaValida(cedula)) {
            throw std::invalid_argument("La cedula debe tener exactamente 10 digitos numericos");
        }
        this->cedula = cedula;
    }

    std::string getNombres() const {
        return nombres;
    }

    void setNombres(const std::string& nombres) {
        if (!esTextoObligatorio(nombres)) {
            throw std::invalid_argument("Los nombres son obligatorios");
        }
        this->nombres = nombres;
    }

    std::string getApellidos() const {
        return apellidos;
    }

    void setApellidos(const std::string& apellidos) {
        if (!esTextoObligatorio(apellidos)) {
            throw std::invalid_argument("Los apellidos son obligatorios");
        }
        this->apellidos = apellidos;
    }

    Fecha getFechaNacimiento() const {
        return fechaNacimiento;
    }

    std::string getFechaNacimientoTexto() const {
        return formatearFecha(fechaNacimiento);
    }

    void setFechaNacimiento(const std::string& fechaNacimientoTexto) {
        this->fechaNacimiento = parsearFecha(fechaNacimientoTexto);
    }

    int getTope() const {
        return tope;
    }

    int calcularEdad() const {
        Fecha actual = fechaActual();
        int edad = actual.anio - fechaNacimiento.anio;
        if (actual.mes < fechaNacimiento.mes ||
            (actual.mes == fechaNacimiento.mes && actual.dia < fechaNacimiento.dia)) {
            edad--;
        }
        return edad;
    }

    bool registrarCalificacion(double nota) {
        if (nota < 0 || nota > 10) {
            return false;
        }
        if (tope >= MAX_CALIFICACIONES) {
            return false;
        }
        calificaciones[tope] = nota;
        tope++;
        return true;
    }

    bool modificarCalificacion(int indice, double nuevaNota) {
        if (indice < 0 || indice >= tope) {
            return false;
        }
        if (nuevaNota < 0 || nuevaNota > 10) {
            return false;
        }
        calificaciones[indice] = nuevaNota;
        return true;
    }

    bool eliminarCalificacion(int indice) {
        if (indice < 0 || indice >= tope) {
            return false;
        }
        for (int i = indice; i < tope - 1; i++) {
            calificaciones[i] = calificaciones[i + 1];
        }
        tope--;
        calificaciones[tope] = 0.0;
        return true;
    }

    const double* getCalificaciones() const {
        return calificaciones;
    }

    double calcularPromedio() const {
        if (tope == 0) {
            return 0.0;
        }
        double suma = 0.0;
        for (int i = 0; i < tope; i++) {
            suma += calificaciones[i];
        }
        return suma / tope;
    }

    bool tieneCalificaciones() const {
        return tope > 0;
    }
};

#endif
