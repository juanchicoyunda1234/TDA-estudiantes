package modelo;

import java.time.LocalDate;
import java.time.Period;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.format.ResolverStyle;

public class Estudiante {

    public static final int MAX_CALIFICACIONES = 7;
    private static final DateTimeFormatter FORMATO_FECHA = DateTimeFormatter.ofPattern("dd/MM/uuuu")
            .withResolverStyle(ResolverStyle.STRICT);

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

    public String getFechaNacimientoTexto() {
        return fechaNacimiento.format(FORMATO_FECHA);
    }

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
        double[] copia = new double[tope];
        System.arraycopy(calificaciones, 0, copia, 0, tope);
        return copia;
    }

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
