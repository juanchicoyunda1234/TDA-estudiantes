package modelo;

import java.time.LocalDate;
import java.time.Period;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

// Estudiante matriculado en el curso. Guarda sus datos personales y un vector
// estatico de calificaciones (maximo 7, una por cada actividad de evaluacion).
public class Estudiante {

    public static final int MAX_CALIFICACIONES = 7;
    private static final DateTimeFormatter FORMATO_FECHA = DateTimeFormatter.ofPattern("dd/MM/yyyy");

    private String cedula;
    private String nombres;
    private String apellidos;
    private LocalDate fechaNacimiento;

    private double[] calificaciones;
    private int tope;

    public Estudiante(String cedula, String nombres, String apellidos, String fechaNacimientoTexto) {
        setCedula(cedula);
        setNombres(nombres);
        setApellidos(apellidos);
        setFechaNacimiento(fechaNacimientoTexto);
        this.calificaciones = new double[MAX_CALIFICACIONES];
        this.tope = 0;
    }

    // --- Cedula: la valida por 10 digitos numericos,
    //se usa para buscar al estudiante en todo el sistema.
    public String getCedula() {
        return cedula;
    }

    public void setCedula(String cedula) {
        if (cedula == null || !cedula.matches("\\d{10}")) {
            throw new IllegalArgumentException("La cedula debe tener exactamente 10 digitos numericos");
        }
        this.cedula = cedula;
    }

    public String getNombres() {
        return nombres;
    }

    public void setNombres(String nombres) {
        if (nombres == null || nombres.isBlank()) {
            throw new IllegalArgumentException("Los nombres son obligatorios");
        }
        this.nombres = nombres;
    }

    public String getApellidos() {
        return apellidos;
    }

    public void setApellidos(String apellidos) {
        if (apellidos == null || apellidos.isBlank()) {
            throw new IllegalArgumentException("Los apellidos son obligatorios");
        }
        this.apellidos = apellidos;
    }

    public LocalDate getFechaNacimiento() {
        return fechaNacimiento;
    }

    // Recibo la fecha como texto (dd/MM/yyyy), pero se guarda como LocalDate para poder calcular
    // la edad con Period en vez de hacerlo a mano con restas de anios.
    public void setFechaNacimiento(String fechaNacimientoTexto) {
        LocalDate fecha;
        try {
            fecha = LocalDate.parse(fechaNacimientoTexto, FORMATO_FECHA);
        } catch (DateTimeParseException ex) {
            throw new IllegalArgumentException("Fecha invalida, formato esperado dd/MM/yyyy");
        }
        if (fecha.isAfter(LocalDate.now())) {
            throw new IllegalArgumentException("La fecha de nacimiento no puede ser futura");
        }
        this.fechaNacimiento = fecha;
    }

    public int getTope() {
        return tope;
    }

    public int calcularEdad() {
        return Period.between(fechaNacimiento, LocalDate.now()).getYears();
    }

    // --- Calificaciones ---
    // Aqui nota invalida o vector lleno son casos esperados del flujo
    // del menu, no errores excepcionales, asi que el Main decide que mensaje mostrar.
    public boolean registrarCalificacion(double nota) {
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

    public boolean modificarCalificacion(int indice, double nuevaNota) {
        if (indice < 0 || indice >= tope) {
            return false;
        }
        if (nuevaNota < 0 || nuevaNota > 10) {
            return false;
        }
        calificaciones[indice] = nuevaNota;
        return true;
    }

    // Al eliminar, desplazo todo lo que esta a la derecha del indice una
    // posicion a la izquierda (mismo patron que insertar al inicio de un
    // array, pero al reves), para no dejar huecos entre 0 y tope-1.
    public boolean eliminarCalificacion(int indice) {
        if (indice < 0 || indice >= tope) {
            return false;
        }
        for (int i = indice; i < tope - 1; i++) {
            calificaciones[i] = calificaciones[i + 1];
        }
        tope--;
        calificaciones[tope] = 0;
        return true;
    }

    public double[] getCalificaciones() {
        // Devuelvo una copia solo hasta tope: el resto del arreglo fisico
        // son casillas vacias que a Main no le interesan.
        double[] copia = new double[tope];
        System.arraycopy(calificaciones, 0, copia, 0, tope);
        return copia;
    }

    // NaN es el resultado real de 0.0/0, no lanza excepcion en Java
    public double calcularPromedio() {
        if (tope == 0) {
            return 0;
        }
        double suma = 0;
        for (int i = 0; i < tope; i++) {
            suma += calificaciones[i];
        }
        return suma / tope;
    }

    public boolean tieneCalificaciones() {
        return tope > 0;
    }

    @Override
    public String toString() {
        return String.format("| CEDULA: %-10s | NOMBRES: %-15s | APELLIDOS: %-15s | EDAD: %2d | NOTAS: %d/%d |",
                cedula, nombres, apellidos, calcularEdad(), tope, MAX_CALIFICACIONES);
    }
}