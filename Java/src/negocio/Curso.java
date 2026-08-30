package negocio;

import modelo.Estudiante;

public class Curso {

    public static final int CAPACIDAD_MAXIMA = 20;

    private Estudiante[] estudiantes;
    private int tope;
    private int capacidad;

    public Curso() {
        this(CAPACIDAD_MAXIMA);
    }

    public Curso(int capacidadMaxima) {
        this.capacidad = capacidadMaxima;
        this.estudiantes = new Estudiante[capacidadMaxima];
        this.tope = 0;
    }

    public boolean insertar(Estudiante estudiante) {
        if (tope >= capacidad || estudiante == null) {
            return false;
        }
        estudiantes[tope] = estudiante;
        tope++;
        return true;
    }

    // Metodo de busqueda por cedula
    public int buscar(String cedula) {
        if (cedula == null) {
            return -1;
        }
        for (int i = 0; i < tope; i++) {
            if (estudiantes[i] != null && estudiantes[i].getCedula().equals(cedula)) {
                return i;
            }
        }
        return -1;
    }

    // Metodo para obtener estudiante por indice
    public Estudiante obtener(int indice) {
        if (indice < 0 || indice >= tope) {
            return null;
        }
        return estudiantes[indice];
    }

    // Metodo para eliminar estudiante por indice
    public boolean eliminar(int indice) {
        if (indice < 0 || indice >= tope) {
            return false;
        }
        for (int i = indice; i < tope - 1; i++) {
            estudiantes[i] = estudiantes[i + 1];
        }
        tope--;
        estudiantes[tope] = null;
        return true;
    }

    // Metodo para modificar estudiante por indice
    public boolean modificar(int indice, Estudiante nuevosDatos) {
        if (indice < 0 || indice >= tope || nuevosDatos == null) {
            return false;
        }
        estudiantes[indice] = nuevosDatos;
        return true;
    }

    // Listar todos los estudiantes registrados
    public Estudiante[] listar() {
        Estudiante[] listaActual = new Estudiante[tope];
        System.arraycopy(estudiantes, 0, listaActual, 0, tope);
        return listaActual;
    }

    // Calcular promedio general de las notas del curso
    public Double calcularPromedioGeneral() {
        if (tope == 0) {
            return null;
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
            return null;
        }
        return sumaPromedios / estudiantesConNotas;
    }

    public int getTope() {
        return tope;
    }

    public int getCapacidad() {
        return capacidad;
    }
}
